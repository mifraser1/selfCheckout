#include "BasePricingRule.h"

void BasePricingRule::apply(PricingContext &context)
{
    for (const auto &item : context.items)
    {
        context.subtotal += item->getBasePrice();
    }
}

