#include "transaction.h"
#include "transactionItem.h"
#include <vector>
#include <memory>
void addItem(const productRecord& product, double amount)
{
    transactionItem newItem(product.ID, amount, 0); // Assuming weight is 0 for non-weighted items
    // Add item to the transaction
    items.push_back(std::make_unique<transactionItem>(newItem.getID(), amount));
}
{
    // Implementation for processing transaction
}
void removeItem()
{
    // Remove item from the transaction
}
void calculateTotal()
{
    // Calculate total amount for the transaction
    total = item.calcPrice(...);
}

double getSubtotal() const
{
    // Return the subtotal for the transaction
    double subtotal = 0.0;
    for(const auto& item : items) {
        subtotal += item.calcPrice();
    }
    return subtotal;
}
double getTaxTotal() const
{
    // Return the total tax for the transaction
    double taxTotal = 0.0;
    for(const auto& item : items) {
        taxTotal += item.taxCalc();
    }
    return taxTotal;
}
double getTotal() const
{
    // Return the total amount for the transaction
    return getSubtotal() + getTaxTotal();
}

void cancel()
{
    // Cancel the transaction
    // clears items, releases inventory, and resets transaction state
}
void commit()
{
    // Commit the transaction
    // finalizes the transaction (inv + accounting)
}

// how transactionstores its items
// vector that has owernship of multiple transactionItems, each with a reference to an item in inventory
std::vector<std::unique_ptr<transactionItem>> items;

int transactionID;
int customerID;
int timeStamp;
bool paymentStatus;