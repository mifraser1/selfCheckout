#include "transactionItem.h"
#include "productRecord.h"

TransactionItem::TransactionItem(const ProductRecord &product, double amount)
    : product(product), amount(amount) {}

double TransactionItem::calcPrice() const
{
    return product.price * amount;
}

double TransactionItem::taxCalc() const
{
    return calcPrice() * product.taxRate;
}