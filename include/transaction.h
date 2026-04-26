#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <vector>
#include <memory>
#include "productRecord.h"
#include "transactionItem.h"
#include "ledger.h"

class Transaction
{
public:
    Transaction(int transactionID, int customerID = 0);

    // Item management
    void addItem(const ProductRecord &product, double amount);
    void removeItem(size_t index);

    // Calculations
    void calculateTotal();
    double getSubtotal() const;
    double getTaxTotal() const;
    double getTotal() const;

    // Transaction lifecycle
    Ledger createLedgerEntry(int entryID) const;
    void cancel();
    Ledger commit(int entryID);

    // Accessors
    int getTransactionID() const { return transactionID; }
    int getCustomerID() const { return customerID; }
    size_t getItemCount() const { return items.size(); }
    bool isPaymentComplete() const { return paymentStatus; }

private:
    // How transaction stores its items
    // Vector that has ownership of multiple transactionItems,
    // Each with a reference to an item in inventory
    std::vector<std::unique_ptr<TransactionItem>> items;
    int transactionID;
    int customerID;
    int timestamp;
    bool paymentStatus;
};

#endif // TRANSACTION_H