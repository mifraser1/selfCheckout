#ifndef LEDGER_H
#define LEDGER_H

#include <string>
#include <ctime>
#include <vector>

struct LedgerEntry
{
    int entryID;
    int TransactionID;

    std::vector<LedgerItem> items;

    double subtotal;
    double tax;
    double total;

    std::string timestamp;

    LedgerEntry() : entryID(0), TransactionID(0), subtotal(0.0),
                    tax(0.0), total(0.0), timestamp("") {}
};

struct LedgerItem
{
    int itemID;
    double quantity;
    double total;
};

class Transaction;

// For accounting entry, perm record, immutable, created after Transaction commit
class Ledger
{
private:
    int nextEntryID = 1;
    int nextTransactionID = 1;

    std::vector<LedgerEntry> entries;

public:
    LedgerEntry createLedgerEntry(const Transaction &tx) {}
    void refund(LedgerEntry& entry);
};

#endif // LEDGER_H