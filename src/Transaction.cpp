#include "Transaction.h"
#include "TransactionItem.h"
#include "Ledger.h"
#include "ProductRecord.h"
#include "ScanningState.h"
#include "AwaitingPaymentState.h"
#include "PaymentProcessingState.h"
#include "CompletedState.h"
#include "PricingEngine.h"
#include "BasePricingRule.h"
#include "DiscountPricingRule.h"
#include "TaxRule.h"
#include <string>
#include <stdexcept>
#include <vector>
#include <memory>
#include <ctime>
#include <iostream>

Transaction::Transaction()
{
    state = std::make_unique<ScanningState>();

    pricingEngine.addPricingRule(std::make_unique<BasePricingRule>());
    pricingEngine.addPricingRule(std::make_unique<DiscountPricingRule>());
    pricingEngine.addPricingRule(std::make_unique<TaxRule>());
}

void Transaction::setState(std::unique_ptr<TransactionState> newState)
{
    state = std::move(newState);
}

void Transaction::setPaymentStrategy(std::unique_ptr<PaymentStrategy> strategy)
{
    paymentStrategy = std::move(strategy);
};

Result Transaction::addItem(const ProductRecord &product, double amount = 0, double weight = 0.0)
{
    return state->addItem(*this, product, amount, weight);
}

Result Transaction::removeItem(int index)
{
    return state->removeItem(*this, index);
}

Result Transaction::finishScanning()
{
    return state->finishScanning(*this);
}

Result Transaction::processPayment(Ledger &ledger)
{
    return state->processPayment(*this, ledger);
}

Result Transaction::cancel()
{
    return state->cancel(*this);
}

void Transaction::applyAddItem(const ProductRecord &product, double amount, double weight)
{
    items.push_back(std::make_unique<TransactionItem>(product, amount, weight));
}

void Transaction::applyRemoveItem(int index)
{
    if (index < 0 || index >= static_cast<int>(items.size()))
    {
        throw std::out_of_range("Invalid item index");
    }
    items.erase(items.begin() + index);
}

void Transaction::applyProcessPayment(Ledger &ledger)
{
    auto result = getPricing();

    if (!paymentStrategy)
    {
        throw std::runtime_error("No payment strategy set");
    }

    bool success = paymentStrategy->processPayment(result.total);

    // Double check then commit Transaction
    if (success)
    {
        applyCommit(ledger);
    }
}

void Transaction::applyCancel()
{
    items.clear();
    paymentStatus = false;
}

void Transaction::applyCommit(Ledger &ledger)
{
    // Commit the Transaction
    // Create ledger entry to assign IDs and store snapshot
    ledger.createLedgerEntry(*this);

    items.clear(); // Transaction is complete, clear items
                   // paymentStatus = true; // mark as paid

    // Move state
    setState(std::make_unique<CompletedState>());

    // Stored in Ledger not returned
    // return entry;
}

PricingResult Transaction::getPricing() const
{
    return const_cast<PricingEngine &>(pricingEngine).calculate(*this);
}

double Transaction::getSubtotal() const
{
    return getPricing().subtotal;
}

double Transaction::getTaxTotal() const
{
    return getPricing().tax;
}

double Transaction::getTotal() const
{
    return getPricing().total;
}