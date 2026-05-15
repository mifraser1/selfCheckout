#include "CriticalState.h"
#include "Transaction.h"
#include "TransactionState.h"


Result CriticalState::addItem(Transaction& Transaction, const ProductRecord& product, double amount, double weight) {
    return Result::Failure;
}
Result CriticalState::removeItem(Transaction& Transaction, int index) {
    return Result::InvalidState;
}
Result CriticalState::finishScanning(Transaction& Transaction) {
    return Result::Failure;
}
Result CriticalState::processPayment(Transaction& Transaction, Ledger& ledger) {
    return Result::Failure;
}
Result CriticalState::cancel(Transaction& Transaction) {
    return Result::InvalidState;
}