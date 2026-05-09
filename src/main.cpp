#include <iostream>
#include "Transaction.h"
#include "TransactionItem.h"
#include "Ledger.h"
#include "ProductRecord.h"
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
          tx.addItem(gum, 2.0);    // 2 units of gum
          tx.addItem(apples, 1.5); // 1.5 lbs of apples

          // Placeholder for display, should be real-time
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

          char choice;
          cout << "Finished Scanning: Y/N" << endl;
          cin >> choice;
          if (choice == 'N')
               return false;
     }
     return 0;
}
