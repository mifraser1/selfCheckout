#include <string>
#ifndef PAYMENT_H
#define PAYMENT_H
class payment {
public:
    payment() {
        // Constructor implementation
    }   
    void processPayment() {
        // Method to process payment
    }
private:
    int paymentID;
    int transactionID;
    float amount;
    bool status;
    std::string method;
};
#endif // PAYMENT_H