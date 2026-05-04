#include "ScanningState.h"
#include "Transaction.h"
#include "AwaitingPaymentState.h"

Result ScanningState::addItem(Transaction& transaction, 
    const ProductRecord& product, double amount) {
    transaction.applyAddItem(product, amount);
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

Result ScanningState::processPayment(Transaction& Transaction) {
    return Result::InvalidState; // Can't process payment while scanning
}

Result ScanningState::cancel(Transaction& Transaction) {
    Transaction.applyCancel();
    return Result::Success;
}