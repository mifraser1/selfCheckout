#include "Transaction.h"
#include "TransactionItem.h"
#include "ledger.h"
#include "productRecord.h"
#include "ScanningState.h"
#include "AwaitingPaymentState.h"
#include "PaymentProcessingState.h"
#include "CompletedState.h"
#include <string>
#include <stdexcept>
#include <vector>
#include <memory>
#include <ctime>

Transaction::Transaction(int id) {
    state = std::make_unique<ScanningState>();
}

Transaction::Transaction(int TransactionID, int customerID)
    : TransactionID(TransactionID), customerID(customerID), 
      timestamp(static_cast<int>(std::time(nullptr))), paymentStatus(false) {}

void Transaction::setState(std::unique_ptr<TransactionState> newState) {
    state = std::move(newState);
}

Result Transaction::addItem(const ProductRecord& product, double amount) {
    return state->addItem(*this, product, amount);
}

Result Transaction::removeItem(int index) {
    return state->removeItem(*this, index);
}

Result Transaction::finishScanning() {
    return state->finishScanning(*this);
}

Result Transaction::processPayment() {
    return state->processPayment(*this);
}

Result Transaction::cancel() {
    return state->cancel(*this);
}

void Transaction::applyAddItem(const ProductRecord& product, double amount) {
    items.push_back(std::make_unique<TransactionItem>(product, amount));
}

void Transaction::applyRemoveItem(int index) {
    if (index < 0 || index >= static_cast<int>(items.size())) {
        throw std::out_of_range("Invalid item index");
    }
    items.erase(items.begin() + index);
}

void Transaction::applyCancel() {
    items.clear();
    paymentStatus = false;
}

Ledger Transaction::applyCommit(int entryID) {
    // Commit the Transaction
    Ledger entry = createLedgerEntry(entryID);
    
    items.clear();          // Transaction is complete, clear items
    paymentStatus = true;   // mark as paid
    
    return entry;
    
}

double Transaction::getSubtotal() const
{
    // Return the subtotal for the Transaction (sum of item prices)
    double subtotal = 0.0;
    for (const auto &item : items)
    {
        subtotal += item->calcPrice();
    }
    return subtotal;
}

double Transaction::getTaxTotal() const
{
    // Return the total tax for the Transaction
    double taxTotal = 0.0;
    for (const auto &item : items)
    {
        taxTotal += item->taxCalc();
    }
        // Can change rounding here, but for now just return the total tax
    return taxTotal;
}

double Transaction::getTotal() const
{
    // Return the total amount for the Transaction
    return getSubtotal() + getTaxTotal();
}

Ledger Transaction::createLedgerEntry(int entryID) const
{
    // Create a ledger entry for the Transaction
    Ledger entry;
    entry.entryID = entryID;
    entry.TransactionID = this->TransactionID;
    entry.subtotal = getSubtotal();
    entry.tax = getTaxTotal();
    entry.total = getTotal();
    entry.timestamp = std::to_string(std::time(nullptr));

    return entry;
}

