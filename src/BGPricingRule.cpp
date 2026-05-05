#include "BGPricingRule.h"

void BGPricingRule::apply(PricingContext &context)
{
    // Example rule for collecting item IDs or other metadata.
    context.itemIDs.clear();
    for (const auto &item : context.items) {
        context.itemIDs.insert(item->getProduct().itemID);
    }
}
