#ifndef COMPLETEDSTATE_H
#define COMPLETEDSTATE_H

#include "TransactionState.h"

class CompletedState : public TransactionState {
public:
    Result addItem(Transaction& Transaction, const ProductRecord& product, double amount) override;
    Result removeItem(Transaction& Transaction, int index) override;
    Result finishScanning(Transaction& Transaction) override;
    Result processPayment(Transaction& Transaction) override;
    Result cancel(Transaction& Transaction) override;
};

#endif // COMPLETEDSTATE_H