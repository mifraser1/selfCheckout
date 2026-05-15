#include <iostream>
#include "Transaction.h"
#include "TransactionItem.h"
#include "Ledger.h"
#include "ProductRecord.h"
#include "Scale.h"
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

     //     New transaction
     Transaction tx;
     std::unique_ptr<Scale> scale;

     // Hardcoded product catalog for testing
     ProductRecord gum{1, "Gum", 1.50f, 0.0f, 0.07f, 100};
     ProductRecord apples{2, "Apples", 2.99f, 1.0f, 0.07f, 50};
     ProductRecord salad{3, "Salad", 5.99f, 0.0f, 0.14f, 20};

     // Add items to Transaction
     cout << "Scanning Items..." << endl;
     tx.addItem(gum, 2.0, 0.0);    // 2 units of gum
     tx.addItem(apples, 0.0, 1.5); // 1.5 lbs of apples
     tx.addItem(salad, 2.0, 0.0);  // 2 units of salad

     cout << "Remove Item Scanned" << endl << endl;
     tx.removeItem(2);

     tx.finishScanning();
     cout << "Finished Scanning" << endl;
     cout << "Processing Payment..." << endl;

     // Placeholder for display, should be real-time instead
     cout << "Subtotal: $"
          << fixed << setprecision(2)
          << tx.getSubtotal()
          << endl;
     cout << "Tax: $" << tx.getTaxTotal() << endl;
     cout << "Total: $" << tx.getTotal() << endl;

     // Payment and commit Transaction
     tx.processPayment(ledger);
     // Replace with new transaction
     tx = Transaction();

     cout << "Transaction Complete (System Ready)" << endl;

     return 0;
}
