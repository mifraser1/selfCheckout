#include "BasePricingRule.h"

void BasicPricingRule::apply(PricingContext &context)
{
    for (const auto &item : context.items)
    {
        context.subtotal += item->getBasePrice();
    }
}

