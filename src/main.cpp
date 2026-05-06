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
     cout << "Self-Checkout System Simulation\n"
          << endl;

     // create ledger object for  program lifetime
     Ledger ledger;

     while (true)
     {
          //     New transaction
          Transaction tx;

          // Hardcoded product catalog for testing
          ProductRecord gum{1, "Gum", 1.50f, 0.0f, 0.07f, 100};
          ProductRecord apples{2, "Apples", 2.99f, 1.0f, 0.07f, 50};

          // Add items to Transaction
          Transaction1.addItem(gum, 2.0);    // 2 units of gum
          Transaction1.addItem(apples, 1.5); // 1.5 lbs of apples

          // Placeholder for display, should be real-time
          cout << "Subtotal: $"
               << fixed << setprecision(2)
               << Transaction1.getSubtotal()
               << endl;
          cout << "Tax: $" << Transaction1.getTaxTotal() << endl;
          cout << "Total: $" << Transaction1.getTotal() << endl;

          // Payment and commit Transaction
          tx.processPayment(ledger);
          // Replace with new transaction
          tx = Transaction();
     }
     return 0;
}
