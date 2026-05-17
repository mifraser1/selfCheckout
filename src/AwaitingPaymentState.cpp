#include "AwaitingPaymentState.h"
#include "Transaction.h"
#include "PaymentProcessingState.h"

Result AwaitingPaymentState::addItem(Transaction& transaction, const ProductRecord& product, double amount, double weight) {
    return Result::InvalidState;
}
Result AwaitingPaymentState::removeItem(Transaction& transaction, int index) {
    return Result::InvalidState;
}
Result AwaitingPaymentState::finishScanning(Transaction& transaction) {
    return Result::InvalidState;
}
Result AwaitingPaymentState::processPayment(Transaction& transaction, Ledger& ledger) {
    transaction.setState(std::make_unique<PaymentProcessingState>());
    return Result::Success;
}
Result AwaitingPaymentState::cancel(Transaction& transaction) {
    transaction.applyCancel();
    return Result::Success;
}