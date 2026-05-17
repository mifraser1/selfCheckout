#include "CompletedState.h"
#include "Transaction.h"
#include "TransactionState.h"

// Terminal state
Result CompletedState::addItem(Transaction& transaction, const ProductRecord& product, double amount, double weight) {
    return Result::InvalidState;
}
Result CompletedState::removeItem(Transaction& transaction, int index) {
    return Result::InvalidState;
}
Result CompletedState::finishScanning(Transaction& transaction) {
    return Result::InvalidState;
}
Result CompletedState::processPayment(Transaction& transaction, Ledger& ledger) {
    return Result::InvalidState;
}
Result CompletedState::cancel(Transaction& transaction) {
    return Result::Success;
}
