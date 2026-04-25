#include <iostream>
#include "transaction.h"
#include "transactionItem.h"
#include "systemState.h"
#include "ledger.h"
#include "override.h"
#include "scale.h"
#include "inventoryRecord.h"
#include "payment.h"

int main() {
    std::cout << "Self-Checkout System" << std::endl;
    std::cout << "Welcome!" << std::endl;

    transaction transaction1;
    // transaction creates its own transactionItems
    transaction1.addItem(itemID);
    
    transactionItem transactionItem1(12345);
    std::cout << "Transaction ID: " << transactionItem1.getID() << std::endl;
    
    inventoryRecord inventoryRecord1;
    inventoryRecord1.updateInventory();

    payment payment1;
    payment1.processPayment();

    ledger ledger1;
    ledger1.recordTransaction(transaction1);

    systemState systemState1;
    systemState1.updateSystemState();

    override override1;

    scale scale1;


    
    return 0;
}
