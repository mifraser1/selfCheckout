#ifndef TRANSACTION_ITEM_H
#define TRANSACTION_ITEM_H
#include <string>
#include "productRecord.h"

class TransactionItem
{
public:
    TransactionItem(const ProductRecord &product, double amount);

    // Price calculations
    double calcPrice() const;
    double taxCalc() const;
    
    // Accessors
    const ProductRecord &getProduct() const { return product; }
    double getAmount() const { return amount; }

private:
    const ProductRecord &product;
    double amount;  // quantity for packaged items, weight for produce
};
#endif // TRANSACTION_ITEM_H