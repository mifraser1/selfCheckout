#ifndef Transaction_ITEM_H
#define Transaction_ITEM_H
#include <string>
#include "productRecord.h"

// Exposes base price and tax rate
class TransactionItem
{
public:
    TransactionItem(const ProductRecord &product, double amount);

    // Price calculations
    double getBasePrice() const;
    double getTax() const;
    
    // Accessors
    const ProductRecord &getProduct() const { return product; }
    double getAmount() const { return amount; }

private:
    const ProductRecord &product;
    double amount;  // quantity for packaged items, weight for produce
};
#endif // Transaction_ITEM_H