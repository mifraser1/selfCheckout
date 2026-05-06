#ifndef BasePricingRule_H
#define BasePricingRule_H
#include "PricingRule.h"

class BasePricingRule : public PricingRule
{
public:
    BasePricingRule();

    void apply(PricingContext &context) override;
};
#endif // BasePricingRule_H
