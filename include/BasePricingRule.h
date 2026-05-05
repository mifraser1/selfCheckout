#ifndef BasicPricingRule_H
#define BasicPricingRule_H
#include "PricingRule.h"

class BasicPricingRule : public PricingRule
{
public:
    void apply(PricingContext &context) override;
};
#endif // BasicPricingRule_H
