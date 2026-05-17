#ifndef Transaction_H
#define Transaction_H

#include <vector>
#include <memory>
#include "ProductRecord.h"
#include "TransactionItem.h"
#include "Ledger.h"
#include "TransactionState.h"
#include "PricingEngine.h"
#include "PricingRule.h"
#include "PricingTypes.h"

class PaymentStrategy;

// Owns data and executes changes, stable

class Transaction
{
public:
    Transaction();

    // Calculations
    bool isAgeVerified() const;
    PricingResult getPricing() const;
    PaymentType getPaymentType() const { return paymentType; };
    double getSubtotal() const;
    double getTaxTotal() const;
    double getTotal() const;
    // const std::unique_ptr<PaymentStrategy> &getPaymentStrategy() const { return this->paymentStrategy; };
    const std::vector<std::unique_ptr<TransactionItem>> &getItems() const { return items; };

    void setState(std::unique_ptr<TransactionState> newState);
    void setPaymentStrategy(std::unique_ptr<PaymentStrategy> paymentStrategy);
    void setPaymentType(PaymentType type) { paymentType = type; }

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
    friend class OverrideState;

    friend class CashPayment;

private:
    // How Transaction stores its items
    // Vector that has ownership of multiple TransactionItems,
    // Each with a reference to an item in inventory
    std::vector<std::unique_ptr<TransactionItem>> items;
    std::unique_ptr<TransactionState> state;          // Current state pointer
    std::unique_ptr<PaymentStrategy> paymentStrategy; // Payment handling strategy
    PaymentType paymentType; // To simulate customer payment
    PricingEngine pricingEngine; // For calculating totals

    bool paymentStatus = false; // Temp for payment processing

    // Internal methods for state actions
    void applyAddItem(const ProductRecord &, double, double);
    void applyRemoveItem(int index);
    void applyProcessPayment(Ledger &ledger);
    void applyCancel();
    void applyCommit(Ledger &ledger);
};


#endif // Transaction_H