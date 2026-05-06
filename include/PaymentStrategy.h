#include <string>
#ifndef PAYMENTSTRATEGY_H
#define PAYMENTSTRATEGY_H

// How payment is processed
class PaymentStrategy
{
public:
    virtual ~PaymentStrategy() = default;
    virtual bool processPayment(float amount) = 0;
    virtual std::string getMethodName() const = 0;
private:
    
};
#endif // PAYMENTSTRATEGY_H
// int paymentID;
// int TransactionID;
// float amount;
// bool status;
// std::string method;
