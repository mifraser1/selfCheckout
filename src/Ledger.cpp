#include "Ledger.h"
#include "Transaction.h"
#include "Scale.h"
#include <string>
#include <ctime>
#include <vector>

LedgerEntry Ledger::createLedgerEntry(const Transaction &tx)
    {
        LedgerEntry entry;
        PricingResult pricing = tx.getPricing();

        // Potential security concern if ID is guessable
        entry.entryID = nextEntryID++;
        entry.TransactionID = nextTransactionID++;

        entry.subtotal = pricing.subtotal;
        entry.tax = pricing.tax;
        entry.total = pricing.total;
        entry.timestamp = std::to_string(std::time(nullptr));

        // Copy items (snapshot)
        for (const auto &item : tx.getItems())
        {
            LedgerItem li;
            li.itemID = (item->getProduct()).itemID;
            if (item->getPricingType() == PricingType::PerUnit) {
                li.quantity = item->getAmount();
            } else if (item->getPricingType() == PricingType::PerWeight) {
                li.quantity = item->getWeight();
            }
            li.total = item->getBasePrice();

            // Store items
            entry.items.push_back(li);
        }

        // Store entry
        entries.push_back(entry);
    };

    void Ledger::refund(LedgerEntry& entry){
        // To be implemented for negative or reversal
        new LedgerEntry;
    }

