#ifndef CashPayment_H
#define CashPayment_H
#include "PaymentStrategy.h"

class CashPayment : public PaymentStrategy {
public:
    bool processPayment(double amount) override;
};

#endif // CashPayment_H