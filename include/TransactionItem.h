#ifndef TRANSACTION_ITEM_H
#define TRANSACTION_ITEM_H
#include <string>
#include "ProductRecord.h"

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