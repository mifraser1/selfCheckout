#ifndef Transaction_H
#define Transaction_H

#include <vector>
#include <memory>
#include "productRecord.h"
#include "TransactionItem.h"
#include "ledger.h"
#include "TransactionState.h"
#include "PaymentStrategy.h"
#include "PricingEngine.h"
#include "PricingRule.h"

// Owns data and executes changes, stable

class Transaction
{
public:
    Transaction(int id);
    // Transaction(int TransactionID, int customerID = 0);

    // Calculations
    PricingResult getPricing() const;
    double getSubtotal() const;
    double getTaxTotal() const;
    double getTotal() const;
    const std::vector<std::unique_ptr<TransactionItem>> &getItems() const { return items; };
    const PaymentStrategy* getPaymentStrategy() const { return paymentStrategy.get(); };

    // Transaction lifecycle
    Ledger createLedgerEntry(int entryID) const;
    Ledger commit(int entryID);

    // Accessors
    // int getTransactionID() const { return TransactionID; }
    // int getCustomerID() const { return customerID; }
    // size_t getItemCount() const { return items.size(); }
    // bool isPaymentComplete() const { return paymentStatus; }

    void setState(std::unique_ptr<TransactionState> newState);

    // Public API for state transitions, delegates to current state
    Result addItem(const ProductRecord &, double);
    Result removeItem(int index);
    Result finishScanning();
    Result processPayment();
    Result cancel();

    // State implementations access internal methods
    friend class ScanningState;
    friend class AwaitingPaymentState;
    friend class PaymentProcessingState;
    friend class CompletedState;

private:
    // How Transaction stores its items
    // Vector that has ownership of multiple TransactionItems,
    // Each with a reference to an item in inventory
    std::vector<std::unique_ptr<TransactionItem>> items;
    std::unique_ptr<TransactionState> state; // Current state pointer
    std::unique_ptr<PaymentStrategy> paymentStrategy; // Payment handling strategy
    std::unique_ptr<PricingEngine> pricingEngine; // Pricing strategy for totals
    int TransactionID;
    bool paymentStatus = false;

    // Internal methods for state actions
    void applyAddItem(const ProductRecord &, double);
    void applyRemoveItem(int index);
    void applyCancel();
    Ledger applyCommit(int entryID);
};

#endif // Transaction_H