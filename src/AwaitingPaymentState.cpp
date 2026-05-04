#include "AwaitingPaymentState.h"
#include "Transaction.h"
#include "TransactionState.h"
#include "PaymentProcessingState.h"

Result AwaitingPaymentState::addItem(Transaction& Transaction, const ProductRecord& product, double amount) {
    return Result::InvalidState;
}
Result AwaitingPaymentState::removeItem(Transaction& Transaction, int index) {
    return Result::InvalidState;
}
Result AwaitingPaymentState::finishScanning(Transaction& Transaction) {
    return Result::InvalidState;
}
Result AwaitingPaymentState::processPayment(Transaction& Transaction) {
    Transaction.setState(std::make_unique<PaymentProcessingState>());
    return Result::Success;
}
Result AwaitingPaymentState::cancel(Transaction& Transaction) {
    Transaction.applyCancel();
    return Result::Success;
}