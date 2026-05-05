#ifndef DiscountPricingRule_H
#define DiscountPricingRule_H
#include "PricingRule.h"

// Modifies subtotal with discounts
class DiscountPricingRule : public PricingRule  
{
public:
    void apply(PricingContext &context) override;
};
#endif // DiscountPricingRule_H