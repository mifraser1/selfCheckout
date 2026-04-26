#include <iostream>
#include "transaction.h"
#include "transactionItem.h"
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
    cout << "Self-Checkout System Simulation\n" << endl;

    int transactionID = 1;
    Transaction transaction1(transactionID++);

    // Hardcoded product catalog for testing
    ProductRecord gum{1, "Gum", 1.50f, 0.0f, 0.07f, 100};
    ProductRecord apples{2, "Apples", 2.99f, 1.0f, 0.07f, 50};

    // Add items to transaction
    transaction1.addItem(gum, 2.0);      // 2 units of gum
    transaction1.addItem(apples, 1.5);   // 1.5 lbs of apples

    cout << "Subtotal: $"
          << fixed << setprecision(2)
          << transaction1.getSubtotal()
          << endl;
    cout << "Tax: $" << transaction1.getTaxTotal() << endl;
    cout << "Total: $" << transaction1.getTotal() << endl;

    // SystemState tests - skeleton to be implemented later
    // SystemState systemState1;
    // cout << "\nInitial State: " << systemState1.getStateString() << endl;
    // systemState1.transition("FirstScan");
    // cout << "After FirstScan: " << systemState1.getStateString() << endl;
    // systemState1.transition("FinishAndPay");
    // cout << "After FinishAndPay: " << systemState1.getStateString() << endl;
    // systemState1.transition("PaymentSubmitted");
    // cout << "After PaymentSubmitted: " << systemState1.getStateString() << endl;
    // systemState1.transition("PaymentAuthorized");
    // cout << "After PaymentAuthorized: " << systemState1.getStateString() << endl;

    // Commit transaction
    int entryID = 1;
    Ledger ledger1 = transaction1.commit(entryID);
    cout << "\nTransaction committed with entry ID: " << ledger1.entryID << endl;
    cout << "Ledger Total: $" << ledger1.total << endl;

    return 0;
}
