#ifndef INVENTORYRECORD_H
#define INVENTORYRECORD_H
#include <string>
class item
{
public:
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

private:
    int sku;
    std::string name;
    float price;
    int onHand;
    bool reserved;
    int lastUpdated;
    float taxRate;
};
#endif // INVENTORYRECORD_H