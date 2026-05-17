#include "OverrideState.h"
#include "Transaction.h"
#include "ScanningState.h"
#include <iostream>

Result OverrideState::addItem(Transaction & transaction, const ProductRecord &product, double amount, double  weight)
{
    // Alert human in the loop
    std::cout << "Waiting for employee approval...\n";

    return Result::OverrideRequired;
}

Result OverrideState::removeItem(Transaction &transaction, int index)
{
    // return Result::InvalidState;
    transaction.applyRemoveItem(index);
    transaction.setState(std::make_unique<ScanningState>());
        return Result::Success;

}

Result OverrideState::finishScanning(Transaction &transaction)
{
    return Result::InvalidState;
}

Result OverrideState::processPayment(Transaction &transaction, Ledger & ledger)
{
    return Result::InvalidState;
}

Result OverrideState::cancel(Transaction &transaction)
{
    return Result::InvalidState;
}
