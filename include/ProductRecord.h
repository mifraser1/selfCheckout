#ifndef PRODUCT_RECORD_H
#define PRODUCT_RECORD_H
#include <string>

struct ProductRecord
{
    int itemID;
    std::string name;
    double price;              // price per unit (or per lb if weight-based)
    double weight;             // expected weight for weight-based items (0 if not applicable)
    double taxRate;            // tax rate as decimal (e.g., 0.08 for 8%)
    // bool isWeightBased;       // true if priced per pound, false if fixed price
    // bool isAgeRestricted;     // true if requires age verification
    int quantity;             // current quantity on hand (for inventory)
};
#endif // PRODUCT_RECORD_H