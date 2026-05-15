#include "CashPayment.h"
#include <iostream>

class CashPayment : public PaymentStrategy {

    bool processPayment(double amount)  {
        // Placeholder for cash processing
        std::cout << "Processing cash payment of $" << amount << std::endl;
        return true; 
    }
};