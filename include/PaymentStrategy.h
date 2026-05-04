#include <string>
#ifndef PAYMENTSTRATEGY_H
#define PAYMENTSTRATEGY_H
class PaymentStrategy {
public:
    virtual ~PaymentStrategy() = default;
    virtual bool processPayment(float amount) = 0;
};
#endif // PAYMENTSTRATEGY_H
    // int paymentID;
    // int TransactionID;
    // float amount;
    // bool status;
    // std::string method;
