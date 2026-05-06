#ifndef PricingTypes_H
#define PricingTypes_H

#include <vector>
#include <memory>
#include <unordered_set>

// Forward declarations
class Transaction;

// Returned for visibility into calculations

struct PricingContext
{
    double tax = 0.0;
    double subtotal = 0.0;

    const std::vector<std::unique_ptr<TransactionItem>> &items;
    PaymentType paymentType; // For rules that need payment input

    std::unordered_set<int> itemIDs; // For rules that need to check specific items
};

// Returned for visibility into calculations
struct PricingResult
{
    double total;
    double tax;
    double subtotal;
};

#endif // PricingTypes_H