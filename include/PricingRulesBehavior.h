#ifndef PRICING_RULES_BEHAVIOR_H
#define PRICING_RULES_BEHAVIOR_H

#include <vector>
#include <memory>

class PricingRule;

class PricingRulesBehavior
{
public:
    static std::vector<std::unique_ptr<PricingRule>> createDefaultRules();
};

#endif // PRICING_RULES_BEHAVIOR_H