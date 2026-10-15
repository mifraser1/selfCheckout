#ifndef PaymentProcessingState_h
#define PaymentProcessingState_h
#include <cstdint>
#include "TransactionState.h"

class PaymentProcessingState : public TransactionState {
public:
    Result addItem(Transaction&, const ProductRecord&, std::int64_t, double) override;
    Result removeItem(Transaction&, int index) override;
    Result finishScanning(Transaction&) override;
    Result processPayment(Transaction&, Ledger&) override;
    Result cancel(Transaction&) override;   
};
#endif // PaymentProcessingState_h