#include "Transaction.h"
#include "TransactionItem.h"
#include "Ledger.h"
#include "ProductRecord.h"
#include "TransactionState.h"
#include "ScanningState.h"
#include "AwaitingPaymentState.h"
#include "PaymentProcessingState.h"
#include "CompletedState.h"
#include "OverrideState.h"
#include "PricingEngine.h"
#include "BasePricingRule.h"
#include "DiscountPricingRule.h"
#include "TaxRule.h"
#include "PaymentStrategy.h"
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
}

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
    // if (index < 0 || index >= static_cast<int>(items.size()))
    // {
    //     throw std::out_of_range("Invalid item index");
    // }
    items.erase(items.begin() + index);
    std::cout << "Item removed from transaction." << std::endl;
}

void Transaction::applyProcessPayment(Ledger &ledger)
{
    auto result = getPricing();

    if (!paymentStrategy)
    {
        throw std::runtime_error("No payment strategy set");
    }

    // bool success = paymentStrategy->processPayment(*this, result.total, paymentType);
    bool success = true;

    // Double check then finalize Transaction
    if (success)
    {
        applyCommit(ledger);

    }
}

void Transaction::applyCancel()
{
    items.clear();
    // Replace with fresh transaction
    *this = Transaction();
    setState(std::make_unique<ScanningState>());

}

void Transaction::applyCommit(Ledger &ledger)
{
    // Commit the Transaction
    // Create ledger entry to assign IDs and store snapshot
    ledger.createLedgerEntry(*this);

    setState(std::make_unique<CompletedState>());

    // Stored in Ledger not returned
    // return entry;
}

bool Transaction::isAgeVerified() const
{
    static bool run = false;
    if (run) {
        return true;
    }
    run = true;
    return false;
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