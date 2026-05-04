#include "PaymentProcessingState.h"
#include "Transaction.h"
#include "CompletedState.h"
#include "AwaitingPaymentState.h"
#include "TransactionState.h"
#include <thread>
#include <chrono>

Result PaymentProcessingState::addItem(Transaction& transaction, const ProductRecord& product, double amount) {
    return Result::InvalidState;
}
Result PaymentProcessingState::removeItem(Transaction& transaction, int index) {
    return Result::InvalidState;
}
Result PaymentProcessingState::finishScanning(Transaction& transaction) {
    return Result::InvalidState;
}
Result PaymentProcessingState::processPayment(Transaction& transaction) {
    // Simulate delay  
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate processing delay

    // Simulate payment success
    bool paymentSuccess = true; // This would be determined by actual payment processing logic

    if(paymentSuccess) {
        transaction.applyCommit(transaction.getTransactionID()); // Finalize transaction
        transaction.setState(std::make_unique<CompletedState>());
        return Result::Success;
    } else {
        // optional to rollback to awaiting state
        // transaction.setState(std::make_unique<AwaitingPaymentState>()); // Revert to awaiting payment state
        return Result::PaymentFailed;
    }
}
Result PaymentProcessingState::cancel(Transaction& transaction) {
    return Result::InvalidState;
}