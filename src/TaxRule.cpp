#include "TaxRule.h"

void TaxRule::apply(PricingContext &context)
{
    for (const auto &item : context.items)
    {
        context.tax += item->getTax();
    }
}
