#ifndef OverrideState_H
#define OverrideState_H
#include "TransactionState.h"

enum class OverrideType {
    AgeRestriction,
    HardwareFailure,
    StaleTransaction
};

// State for system verification
class OverrideState : public TransactionState {
public:
    Result addItem(Transaction&, const ProductRecord&, double, double) override;
    Result removeItem(Transaction& , int index) override;
    Result finishScanning(Transaction&) override;
    Result processPayment(Transaction&, Ledger&) override;
    Result cancel(Transaction&) override;
};
#endif // OverrideState_H