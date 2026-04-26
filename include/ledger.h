#ifndef LEDGER_H
#define LEDGER_H

#include <string>
#include <ctime>

struct Ledger
{
    int entryID;
    int transactionID;
    double subtotal;
    double tax;
    double total;
    std::string timestamp;

    Ledger() : entryID(0), transactionID(0), subtotal(0.0), 
               tax(0.0), total(0.0), timestamp("") {}
};

#endif // LEDGER_H