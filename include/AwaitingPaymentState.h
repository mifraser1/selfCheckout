#ifndef AwaitingPaymentState_h
#define AwaitingPaymentState_h
#include "TransactionState.h"
#include "Transaction.h"

class AwaitingPaymentState : public TransactionState {
public:
    Result addItem(Transaction&, const ProductRecord&, double, double) override;
    Result removeItem(Transaction&, int index) override;
    Result finishScanning(Transaction&) override;
    Result processPayment(Transaction&, Ledger&) override;
    Result cancel(Transaction&) override;
};  
#endif // AwaitingPaymentState_h