#ifndef SCANNINGSTATE_H
#define SCANNINGSTATE_H
#include "TransactionState.h"

class ScanningState : public TransactionState {
public:
    Result addItem(Transaction&, const ProductRecord&, double) override;
    Result removeItem(Transaction& , int index) override;
    Result finishScanning(Transaction&) override;
    Result processPayment(Transaction&, Ledger&) override;
    Result cancel(Transaction&) override;
};
#endif // SCANNINGSTATE_H