#ifndef AwaitingPaymentState_h
#define AwaitingPaymentState_h
#include <cstdint>
#include "TransactionState.h"
#include "Transaction.h"

class AwaitingPaymentState : public TransactionState {
public:
    Result addItem(Transaction&, const ProductRecord&, std::int64_t, double) override;
    Result removeItem(Transaction&, int index) override;
    Result finishScanning(Transaction&) override;
    Result processPayment(Transaction&, Ledger&) override;
    Result cancel(Transaction&) override;
};  
#endif // AwaitingPaymentState_h