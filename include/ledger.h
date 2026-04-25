#ifndef LEDGER_H
#define LEDGER_H
struct ledger {
public:
    ledger() {
        // Constructor implementation
   
    int entryID;
    int transactionID;
    float subtotal;
    float tax;
    float total;
    int timestamp;
    }
};
#endif // LEDGER_H