#ifndef BGPricingRule_H
#define BGPricingRule_H
#include "PricingRule.h"

// Example rule used to populate item metadata or preconditions.
class BGPricingRule : public PricingRule
{
public:
    void apply(PricingContext &context) override;
};
#endif // BGPricingRule_H