#include "transactionItem.h"
#include <string>
// customer picked 1.3 lbs of bananas

// has access to all data for calculating price + tax
class transactionItem
{
    transactionItem(const productRecord &product, double amount) : product(product), amount(amount) {}
    double calcPrice() const
    {
        return product.price * amount;
    }
    double taxCalc() const
    {
        return calcPrice() * product.taxRate;
    }

    const productRecord &product;

    double amount;
};