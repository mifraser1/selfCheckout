#include "InventoryRecord.h"
#include <string>

void reserve(int itemID, int qty)
{
    // Method to update inventory records
}

void release(int TransactionItem)
{
    // Method to release reserved inventory
}

void commit(int TransactionItem)
{
    // Method to commit inventory changes
}
  
int sku;
std::string name;
double price;
int onHand;
bool reserved;
int lastUpdated;
double taxRate;