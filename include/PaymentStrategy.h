#include <string>
#ifndef PAYMENTSTRATEGY_H
#define PAYMENTSTRATEGY_H
#include "PricingTypes.h"
#include "Transaction.h"

// How payment is processed
class PaymentStrategy
{
public:
    virtual ~PaymentStrategy() = default;
    virtual bool processPayment(Transaction & transaction, double amount, PaymentType paymentType) = 0;
private:


};
#endif // PAYMENTSTRATEGY_H

