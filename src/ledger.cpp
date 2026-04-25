#include "ledger.h"
// for accounting entry, permanant record, immutable, created after transaction commit

struct ledger
{

    int entryID;
    int transactionID;
    float subtotal;
    float tax;
    float total;
    int timestamp;
};