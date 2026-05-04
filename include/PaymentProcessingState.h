#ifndef PaymentProcessingState_h
#define PaymentProcessingState_h
#include "TransactionState.h"

class PaymentProcessingState : public TransactionState {
public:
    Result addItem(Transaction&, const ProductRecord&, double) override;
    Result removeItem(Transaction&, int index) override;
    Result finishScanning(Transaction&) override;
    Result processPayment(Transaction&) override;
    Result cancel(Transaction&) override;   
};
#endif // PaymentProcessingState_h