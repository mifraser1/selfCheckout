#ifndef transactionItem_H
#define transactionItem_H
#include <string>

class transactionItem
{

public:
    transactionItem(const productRecord &product, double amount) : product(product), amount(amount) {}
    double calcPrice() const
    {
    }
    double taxCalc() const
    {
    }

private:
    const productRecord &product;

    double amount;
};
#endif // transactionItem_H