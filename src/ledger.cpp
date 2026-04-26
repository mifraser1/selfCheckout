#include "ledger.h"
#include <string>

// For accounting entry, perm record, immutable, created after transaction commit

struct ledger
{

    int entryID;
    int transactionID;
    double subtotal;
    double tax;
    double total;
    std::string timestamp;

    std::string getCurrentTimestamp() const {
        // placeholder for timestamp generation logic
        return "2024-06-01T12:00:00Z";
    }
};

