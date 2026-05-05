#ifndef TaxRule_H
#define TaxRule_H
#include "PricingRule.h"

// Checks exemptions
class TaxRule : public PricingRule
{
public:
    void apply(PricingContext &context) override;
};
#endif // TaxRule_H