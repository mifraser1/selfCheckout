#ifndef CashPayment_H
#define CashPayment_H
#include "PaymentStrategy.h"
#include "Transaction.h"
#include "PricingTypes.h"

class CashPayment : public PaymentStrategy {
public:
    bool processPayment(Transaction & transaction, double amount, PaymentType paymentType) override;
};

#endif // CashPayment_H