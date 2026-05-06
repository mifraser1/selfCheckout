#ifndef Transaction_H
#define Transaction_H

#include <vector>
#include <memory>
#include "ProductRecord.h"
#include "TransactionItem.h"
#include "Ledger.h"
#include "TransactionState.h"
#include "PaymentStrategy.h"
#include "PricingEngine.h"
#include "PricingRule.h"
#include "PricingTypes.h"

// Owns data and executes changes, stable

class Transaction
{
public:
    Transaction();
    // Transaction(int TransactionID, int customerID = 0);

    // Calculations
    PricingResult getPricing() const;
    double getSubtotal() const;
    double getTaxTotal() const;
    double getTotal() const;
    const std::vector<std::unique_ptr<TransactionItem>> &getItems() const { return items; };
    const PaymentType& getPaymentType() const { return paymentType; };

    // Transaction lifecycle
    // All handled by ledger
    // Ledger createLedgerEntry(int entryID) const;
    // Ledger commit(int entryID);

    // Accessors
    PaymentType getpaymentType() {return paymentType;}
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

    PaymentType paymentType;
    bool paymentStatus = false; // temp for payemnt processing

    // Internal methods for state actions
    void applyAddItem(const ProductRecord &, double);
    void applyRemoveItem(int index);
    void applyCancel();
    void applyCommit(Ledger& ledger);
};
enum PaymentType { Cash, Card } ;

#endif // Transaction_H