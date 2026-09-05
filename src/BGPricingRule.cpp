#include "BGPricingRule.h"

void BGPricingRule::apply(PricingContext &context)
{
    // Example rule for collecting item IDs or other metadata.
    context.itemIDs.clear();
    for (const auto &item : context.items) {
        context.itemIDs.insert(item->getProduct().itemID);
    }
    // Then, implement rule based on IDs
    // For example, apply a discount to a specific item, like apples (itemID 2)
    if (context.itemIDs.find(2) != context.itemIDs.end()) {
        for (const auto &item : context.items) {
            if (item->getProduct().itemID == 2) {
                double discount = item->getBasePrice() * 0.1; // 10% discount
                context.subtotal -= discount;
            }
        }
    }
}
