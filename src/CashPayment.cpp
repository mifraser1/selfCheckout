#include "CashPayment.h"
#include <iostream>
#include "Transaction.h"
#include "PricingTypes.h"

bool CashPayment::processPayment(Transaction & tx, std::int64_t amountCents, PaymentType paymentType)
{
    tx.setPaymentType(PaymentType::Cash);
    // Placeholder for cash processing
    std::cout << "Processing cash payment of " << amountCents << " cents" << std::endl;
    return true;
}
