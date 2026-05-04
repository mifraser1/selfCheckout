#include "CompletedState.h"
#include "Transaction.h"

// Terminal state
Result CompletedState::addItem(Transaction& Transaction, const ProductRecord& product, double amount) {
    return Result::InvalidState;
}
Result CompletedState::removeItem(Transaction& Transaction, int index) {
    return Result::InvalidState;
}
Result CompletedState::finishScanning(Transaction& Transaction) {
    return Result::InvalidState;
}
Result CompletedState::processPayment(Transaction& Transaction) {
    return Result::InvalidState;
}
Result CompletedState::cancel(Transaction& Transaction) {
    return Result::InvalidState;
}
