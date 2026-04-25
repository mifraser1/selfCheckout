#include "inventoryRecord.h"
#include <string>

//the store has 100 lbs of apples on hand
inventoryRecord()
{
    // Constructor implementation
}
void reserve(int itemID, int qty)
{
    // Method to update inventory records
}

void release(int transactionItem)
{
    // Method to release reserved inventory
}

void commit(int transactionItem)
{
    // Method to commit inventory changes
}
  
int sku;
std::string name;
// float price;
int onHand;
bool reserved;
int lastUpdated;
// float taxRate;