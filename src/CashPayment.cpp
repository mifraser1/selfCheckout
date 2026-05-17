#include "CashPayment.h"
#include <iostream>
#include "Transaction.h"
#include "PricingTypes.h"

bool CashPayment::processPayment(Transaction & tx, double amount, PaymentType paymentType)
{
    tx.setPaymentType(PaymentType::Cash);
    // Placeholder for cash processing
    std::cout << "Processing cash payment of $" << amount << std::endl;
    return true;
}
