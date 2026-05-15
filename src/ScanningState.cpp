#include "ScanningState.h"
#include "Transaction.h"
#include "AwaitingPaymentState.h"

Result ScanningState::addItem(Transaction& transaction, 
    const ProductRecord& product, double amount, double weight) {
    transaction.applyAddItem(product, amount, weight);
    return Result::Success;
}
Result ScanningState::removeItem(Transaction& Transaction, 
    int index) {
    Transaction.applyRemoveItem(index);
    return Result::Success;
}

Result ScanningState::finishScanning(Transaction& Transaction) {
    Transaction.setState(std::make_unique<AwaitingPaymentState>());
    return Result::Success;
}

Result ScanningState::processPayment(Transaction& Transaction, Ledger& ledger) {
    return Result::InvalidState; // Can't process payment while scanning
}

Result ScanningState::cancel(Transaction& Transaction) {
    Transaction.applyCancel();
    return Result::Success;
}