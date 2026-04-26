#include "transaction.h"
#include "transactionItem.h"
#include "ledger.h"
#include "productRecord.h"
#include <string>
#include <stdexcept>
#include <vector>
#include <memory>
#include <ctime>

Transaction::Transaction(int transactionID, int customerID)
    : transactionID(transactionID), customerID(customerID), 
      timestamp(static_cast<int>(std::time(nullptr))), paymentStatus(false) {}

void Transaction::addItem(const ProductRecord &product, double amount)
{
    // Add new item to the transaction
    items.emplace_back(std::make_unique<TransactionItem>(product, amount));
}

void Transaction::removeItem(size_t index)
{
    // Remove item from the transaction
    if (index >= items.size())
    {
        throw std::out_of_range("Invalid item index");
    }
    items.erase(items.begin() + index);
}

void Transaction::calculateTotal()
{
    // Calculate total is done on demand via getTotal()
}

double Transaction::getSubtotal() const
{
    // Return the subtotal for the transaction (sum of item prices)
    double subtotal = 0.0;
    for (const auto &item : items)
    {
        subtotal += item->calcPrice();
    }
    return subtotal;
}

double Transaction::getTaxTotal() const
{
    // Return the total tax for the transaction
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
    // Return the total amount for the transaction
    return getSubtotal() + getTaxTotal();
}

Ledger Transaction::createLedgerEntry(int entryID) const
{
    // Create a ledger entry for the transaction
    Ledger entry;
    entry.entryID = entryID;
    entry.transactionID = this->transactionID;
    entry.subtotal = getSubtotal();
    entry.tax = getTaxTotal();
    entry.total = getTotal();
    entry.timestamp = std::to_string(std::time(nullptr));

    return entry;
}

void Transaction::cancel()
{
    // Cancel the transaction: clear items and reset payment status
    items.clear();
    paymentStatus = false;
}

Ledger Transaction::commit(int entryID)
{
    // Commit the transaction
    Ledger entry = createLedgerEntry(entryID);
    
    items.clear();          // transaction is complete, clear items
    paymentStatus = true;   // mark as paid
    
    return entry;
}