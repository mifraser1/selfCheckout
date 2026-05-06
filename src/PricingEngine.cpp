#include "PricingEngine.h"
#include "Transaction.h"
#include "PricingRule.h"
#include "PricingTypes.h"

PricingResult PricingEngine::calculate(const Transaction &transaction)
{
PricingContext context{
        0.0,
        0.0,
        transaction.getItems(),
        transaction.getPaymentType()
    };

    for (const auto &rule : pricingRules)
    {
        rule->apply(context);
    }

    PricingResult result;
    result.subtotal = context.subtotal;
    result.tax = context.tax;
    result.total = context.subtotal + context.tax;

    return result;
}

void PricingEngine::addPricingRule(std::unique_ptr<PricingRule> rule)
{
    pricingRules.push_back(std::move(rule));
}
