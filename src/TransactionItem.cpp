#include "TransactionItem.h"
#include "ProductRecord.h"
#include "Scale.h"

TransactionItem::TransactionItem(const ProductRecord &product, double amount, double weight)
    : product(product), amount(amount), weight(weight) {}

double TransactionItem::getBasePrice() const
{
    if (product.pricingType == PricingType::PerUnit)
    {
        return product.price * amount;
    }
    else if (product.pricingType == PricingType::PerWeight)
    {
        return product.price * weight;
    }
    return 0.0;
}

void TransactionItem::setWeight(Scale& scale)  {
    weight = scale.readWeight();
}

double TransactionItem::getTax() const
{
    return getBasePrice() * product.taxRate;
}