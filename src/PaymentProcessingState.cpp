#include "PaymentProcessingState.h"
#include "Transaction.h"
#include "TransactionState.h"
#include "AwaitingPaymentState.h"
#include "CompletedState.h"
#include "Ledger.h"
#include "PaymentStrategy.h"
#include <thread>
#include <chrono>
#include <iostream>

Result PaymentProcessingState::addItem(Transaction &transaction, const ProductRecord &product, double amount, double weight)
{
    return Result::InvalidState;
}
Result PaymentProcessingState::removeItem(Transaction &transaction, int index)
{
    return Result::InvalidState;
}
Result PaymentProcessingState::finishScanning(Transaction &transaction)
{
    return Result::InvalidState;
}
Result PaymentProcessingState::processPayment(Transaction &transaction, Ledger &ledger)
{
    // Simulate delay of payment
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate processing delay

    // Simulate customer payment
    // bool paymentSuccess = transaction.paymentStrategy->processPayment(transaction, transaction.getTotal(), transaction.getPaymentType()); // This would be determined by actual payment processing logic
    bool paymentSuccess = true;

    if (paymentSuccess)
    {
        // Commit transaction and transition to completed
        transaction.applyProcessPayment(ledger);
        std::cout << "Thank you for your purchase! Printing receipt...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate

        // Transition to ready after completion
        transaction.cancel();
        
        return Result::Success;
    }
    else
    {
        // optional to rollback to awaiting state
        // transaction.setState(std::make_unique<AwaitingPaymentState>()); // Revert to awaiting payment state

        return Result::PaymentFailed;
    }
}
Result PaymentProcessingState::cancel(Transaction &transaction)
{
    return Result::InvalidState;
}