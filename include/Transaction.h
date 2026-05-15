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

    // Calculations
    PricingResult getPricing() const;
    double getSubtotal() const;
    double getTaxTotal() const;
    double getTotal() const;
    const PaymentType &getPaymentType() const { return paymentType; };
    const std::vector<std::unique_ptr<TransactionItem>> &getItems() const { return items; };

    void setState(std::unique_ptr<TransactionState> newState);
    void setPaymentStrategy(std::unique_ptr<PaymentStrategy> paymentStratey);

    // Accessors
    // int getTransactionID() const { return TransactionID; }
    // int getCustomerID() const { return customerID; }
    // size_t getItemCount() const { return items.size(); }
    // bool isPaymentComplete() const { return paymentStatus; }

    // Public API for state transitions, delegates to current state
    Result addItem(const ProductRecord &, double, double);
    Result removeItem(int index);
    Result finishScanning();
    Result processPayment(Ledger &ledger);
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
    std::unique_ptr<TransactionState> state;          // Current state pointer
    std::unique_ptr<PaymentStrategy> paymentStrategy; // Payment handling strategy
    PricingEngine pricingEngine;

    PaymentType paymentType;
    bool paymentStatus = false; // Temp for payment processing

    // Internal methods for state actions
    void applyAddItem(const ProductRecord &, double, double);
    void applyRemoveItem(int index);
    void applyProcessPayment(Ledger &ledger);
    void applyCancel();
    void applyCommit(Ledger &ledger);
};
enum PaymentType
{
    Cash,
    Card
};

#endif // Transaction_H