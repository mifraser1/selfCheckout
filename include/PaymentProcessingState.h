#ifndef PaymentProcessingState_h
#define PaymentProcessingState_h
#include "TransactionState.h"

class PaymentProcessingState : public TransactionState {
public:
    Result addItem(Transaction&, const ProductRecord&, double) override;
    Result removeItem(Transaction&, int index) override;
    Result finishScanning(Transaction&) override;
    Result processPayment(Transaction&, Ledger&) = 0;
    Result cancel(Transaction&) override;   
};
#endif // PaymentProcessingState_h