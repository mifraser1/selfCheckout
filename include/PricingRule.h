#ifndef PricingRule_H
#define PricingRule_H

#include "PricingTypes.h"

class Transaction; // Forward declaration

// How pricing/discount is derived step-by-step
// Each rule transforms the shared pricing context.
class PricingRule
{
public:
    virtual ~PricingRule() = default;
    virtual void apply(PricingContext &context) = 0;
};
#endif // PricingRule_H