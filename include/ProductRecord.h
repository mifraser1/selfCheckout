#ifndef PRODUCT_RECORD_H
#define PRODUCT_RECORD_H
#include <string>

enum class PricingType {
    PerUnit,
    PerWeight
};


struct ProductRecord
{
    int itemID;
    std::string name;
    double price;              // price per unit (or per lb if weight-based)
    double weight;             // expected weight for weight-based items (0 if not applicable)
    double taxRate;            // tax rate as decimal (e.g., 0.08 for 8%)
    bool isAgeRestricted;     // true if requires age verification
    int quantity;             // current quantity on hand (for inventory)
    PricingType pricingType;  // weighed or unit price
};
#endif // PRODUCT_RECORD_H