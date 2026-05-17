#include <iostream>
#include "Transaction.h"
#include "TransactionItem.h"
#include "Ledger.h"
#include "ProductRecord.h"
#include "MockScale.h"
#include "CashPayment.h"
#include "PricingEngine.h"
#include "PricingTypes.h"

#include <iomanip>

using namespace std;

// UI and main interaction layer

int main()
{

     cout << "Self-Checkout System Simulation\n"
          << endl;

     // Create objects for this lifecycle
     Ledger ledger;
     MockScale scale;
     // Connect and calibrate scale, change to be real hardware
     scale.connect();
     scale.calibrate();

     // New transaction
     Transaction tx;

     // Hardcoded product catalog for testing: {index, name, price, weight, tax, quantity, pricing type, age restriction}
     ProductRecord gum{1, "Gum", 1.50f, 0.0f, 0.07f, 100, PricingType::PerUnit, false};
     ProductRecord apples{2, "Apples", 2.99f, 1.0f, 0.07f, 50, PricingType::PerUnit, false};
     ProductRecord salad{3, "Salad", 5.99f, 0.0f, 0.14f, 20, PricingType::PerWeight, false};
     ProductRecord beer{4, "Beer", 12.99f, 0.0f, 0.07f, 12, PricingType::PerUnit, true};

     // Add items to Transaction
     cout << "Scanning Items..." << endl; // ScanningState
     tx.addItem(gum, 2.0, 0.0);    // 2 units of gum
     tx.addItem(apples, 0.0, 1.5); // 1.5 lbs of apples
     tx.addItem(salad, 2.0, 0.0);  // 2 units of prepackaged taxed item
     tx.addItem(beer, 1.0, 0.0);   // 1 unit of age restricted item

     // Simulate customer taking item off after scanning
     tx.removeItem(2);

     // Customer finalizes scanning
     tx.finishScanning();

     // Placeholder for display, change to be real-time interface
     cout << "Subtotal: $"
          << fixed << setprecision(2)
          << tx.getSubtotal()
          << endl;
     cout << "Tax: $" << tx.getTaxTotal() << endl;
     cout << "Total: $" << tx.getTotal() << endl;

     // Simulate customer payment
     tx.setPaymentStrategy(std::make_unique<CashPayment>());

     // Payment and commit Transaction
     tx.processPayment(ledger);

     return 0;
}
