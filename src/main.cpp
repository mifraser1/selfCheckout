#include <iostream>
#include "Transaction.h"
#include "TransactionItem.h"
// #include "systemState.h"
#include "ledger.h"
// #include "override.h"
// #include "scale.h"
// #include "inventoryRecord.h"
// #include "payment.h"
#include "productRecord.h"
#include <iomanip> 

using namespace std;

int main()
{
    // UI and main interaction layer
    // prints messages, handles results
    cout << "Self-Checkout System Simulation\n" << endl;

    int TransactionID = 1;
    Transaction Transaction1(TransactionID++);

    // Hardcoded product catalog for testing
    ProductRecord gum{1, "Gum", 1.50f, 0.0f, 0.07f, 100};
    ProductRecord apples{2, "Apples", 2.99f, 1.0f, 0.07f, 50};

    // Add items to Transaction
    Transaction1.addItem(gum, 2.0);      // 2 units of gum
    Transaction1.addItem(apples, 1.5);   // 1.5 lbs of apples

    cout << "Subtotal: $"
          << fixed << setprecision(2)
          << Transaction1.getSubtotal()
          << endl;
    cout << "Tax: $" << Transaction1.getTaxTotal() << endl;
    cout << "Total: $" << Transaction1.getTotal() << endl;

   
    // Commit Transaction
    int entryID = 1;
    Ledger ledger1 = Transaction1.commit(entryID);
    cout << "\nTransaction committed with entry ID: " << ledger1.entryID << endl;
    cout << "Ledger Total: $" << ledger1.total << endl;

    return 0;
}
