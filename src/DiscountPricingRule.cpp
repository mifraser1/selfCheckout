#include "DiscountPricingRule.h"

void DiscountPricingRule::apply(PricingContext &context)
{
    context.subtotal *= 0.9; // Apply a 10% discount to the subtotal
}
