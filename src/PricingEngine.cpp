#include "PricingEngine.h"
#include "Transaction.h"
#include "PricingRule.h"

PricingResult PricingEngine::calculate(const Transaction &transaction)
{
    PricingContext context{0.0, 0.0, 0.0, transaction.getPaymentStrategy(), transaction.getItems(), {}};

    for (const auto &rule : pricingRules) {
        rule->apply(context);
    }

    context.total = context.subtotal + context.tax;
    return context;
}

void PricingEngine::addPricingRule(std::unique_ptr<PricingRule> rule)
{
    pricingRules.push_back(std::move(rule));
}
