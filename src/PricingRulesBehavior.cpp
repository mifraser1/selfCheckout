#include "PricingRulesBehavior.h"
#include "BasePricingRule.h"
#include "BGPricingRule.h"
#include "DiscountPricingRule.h"
#include "TaxRule.h"

std::vector<std::unique_ptr<PricingRule>> PricingRulesBehavior::createDefaultRules()
{
    std::vector<std::unique_ptr<PricingRule>> rules;
    rules.push_back(std::make_unique<BasePricingRule>());
    rules.push_back(std::make_unique<BGPricingRule>());
    rules.push_back(std::make_unique<DiscountPricingRule>());
    rules.push_back(std::make_unique<TaxRule>());
    return rules;
}
