#include "ScanningState.h"
#include "Transaction.h"
#include "TransactionState.h"
#include "AwaitingPaymentState.h"
#include "OverrideState.h"
#include <iostream>

Result ScanningState::addItem(Transaction &transaction, const ProductRecord &product, double amount, double weight)
{
    if (product.isAgeRestricted &&
        !transaction.isAgeVerified())
    {
        transaction.setState(std::make_unique<OverrideState>());
        return Result::OverrideRequired;
    }
    transaction.applyAddItem(product, amount, weight);
    return Result::Success;
}
Result ScanningState::removeItem(Transaction &transaction, int index)
{
    transaction.applyRemoveItem(index);
    return Result::Success;
}

Result ScanningState::finishScanning(Transaction &transaction)
{
    transaction.setState(std::make_unique<AwaitingPaymentState>());
    std::cout << "Processing Payment..." << std::endl;

    return Result::Success;
}

Result ScanningState::processPayment(Transaction &transaction, Ledger &ledger)
{
    return Result::InvalidState; // Can't process payment while scanning
}

Result ScanningState::cancel(Transaction &transaction)
{
    transaction.applyCancel();
    return Result::Success;
}