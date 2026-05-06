#include "Transaction.h"
#include "TransactionItem.h"
#include "Ledger.h"
#include "ProductRecord.h"
#include "ScanningState.h"
#include "AwaitingPaymentState.h"
#include "PaymentProcessingState.h"
#include "CompletedState.h"
#include "PricingEngine.h"
#include "PricingRulesBehavior.h"
#include <string>
#include <stdexcept>
#include <vector>
#include <memory>
#include <ctime>

Transaction::Transaction()
{
    state = std::make_unique<ScanningState>();
    pricingEngine = std::make_unique<PricingEngine>();

    for (auto rule : PricingRulesBehavior::createDefaultRules())
    {
        pricingEngine->addPricingRule(std::move(rule));
    }
}

void Transaction::setState(std::unique_ptr<TransactionState> newState)
{
    state = std::move(newState);
}

Result Transaction::addItem(const ProductRecord &product, double amount)
{
    return state->addItem(*this, product, amount);
}

Result Transaction::removeItem(int index)
{
    return state->removeItem(*this, index);
}

Result Transaction::finishScanning()
{
    return state->finishScanning(*this);
}

Result Transaction::processPayment()
{
    return state->processPayment(*this);
}

Result Transaction::cancel()
{
    return state->cancel(*this);
}

void Transaction::applyAddItem(const ProductRecord &product, double amount)
{
    items.push_back(std::make_unique<TransactionItem>(product, amount));
}

void Transaction::applyRemoveItem(int index)
{
    if (index < 0 || index >= static_cast<int>(items.size()))
    {
        throw std::out_of_range("Invalid item index");
    }
    items.erase(items.begin() + index);
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
    return pricingEngine->calculate(*this);
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