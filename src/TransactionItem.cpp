#include "TransactionItem.h"
#include "productRecord.h"

TransactionItem::TransactionItem(const ProductRecord &product, double amount)
    : product(product), amount(amount) {}

double TransactionItem::getBasePrice() const
{
    return product.price * amount;
}

double TransactionItem::getTax() const
{
    return getBasePrice() * product.taxRate;
}