#ifndef PricingEngine_H
#define PricingEngine_H
#include <vector>
#include <memory>
#include "PricingTypes.h"

// Forward declarations
class PricingRule;
class Transaction;

// Recomputed at any time, dynamic and stateless
class PricingEngine
{
private:
    std::vector<std::unique_ptr<PricingRule>> pricingRules;

public:
    PricingResult calculate(const Transaction &transaction);
    void addPricingRule(std::unique_ptr<PricingRule> rule);
};
#endif // PricingEngine_H