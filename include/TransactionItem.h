#ifndef TRANSACTION_ITEM_H
#define TRANSACTION_ITEM_H
#include <string>
#include "ProductRecord.h"
#include "Scale.h"

// Exposes base price and tax rate
class TransactionItem
{
public:
    TransactionItem(const ProductRecord &product, double amount, double weight);

    // Price calculations
    double getBasePrice() const;
    double getTax() const;

    // Accessors
    const ProductRecord &getProduct() const { return product; }
    PricingType getPricingType() const { return product.pricingType; }
    double getAmount() const { return amount; }
    void setWeight(Scale & scale);
    double getWeight() const { return weight; }

private:
    const ProductRecord &product;
    double tax;    // tax amount
    double amount; // quantity for packaged items, weight for produce
    double weight; // only used for produce, can be set by scale reading
};
#endif // Transaction_ITEM_H