#ifndef PricingTypes_H
#define PricingTypes_H

#include <vector>
#include <memory>
#include <unordered_set>
#include "PaymentStrategy.h"
#include "TransactionItem.h"

// Forward declarations
class Transaction;

// Returned for visibility into calculations

struct PricingContext
{
    double total = 0.0;
    double tax = 0.0;
    double subtotal = 0.0;
    PaymentStrategy* strategy; // For rules that need to check strategy

    const std::vector<std::unique_ptr<TransactionItem>> &items;
    std::unordered_set<int> itemIDs; // For rules that need to check specific items
};

// Returned for visibility into calculations
struct PricingResult {
        double total;
        double tax;
        double subtotal;
    };

#endif // PricingTypes_H