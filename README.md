# Self-Checkout System

A C++ application implementing a self-checkout system.

## Requirements
- CMake 3.10+
- C++17 compatible compiler (g++, clang, or MSVC)

## Build Instructions

### On Linux/macOS:
```bash
cmake -B build
cmake --build build
```

### On Windows (with Visual Studio):
```bash
cmake -B build -G "Visual Studio 16 2019"
cmake --build build
```

## Run
```bash
./build/selfCheckout
```

## Project Structure
```
.
├── src/              # Source files
├── include/          # Header files
├── CMakeLists.txt    # Build configuration
└── README.md         # This file
```

## Development
- Add new source files in `src/`
- Add headers in `include/`
- Update `CMakeLists.txt` if adding new source files
- Hardcoded product list in main.cpp for testing
	- CSV loading infrastructure next
- Invalid actions in wrong states silently fail
	- Instead throw exceptions and return error codes
- Columns of the ledger CSV should have `entryID` `transactionID` `subtotal` `tax` `total` `timestamp`
- Override Class: Should track who (manager ID), when, what was overridden, and reason?
- Implement methods in transaction and transactionItem
- Flesh out productRecord
- Build skeleton of systemState as FSM


## Features (To be implemented)
- [ ] Room for Pricing Strategy to grow in transactionItems
- [ ] Fix naming convention for typical C++ program; transactionItem -> TransactionItem
- [ ] Weight validation based on expected weight of items
- [ ] Age validation for certain items
- [ ] Implement State System logic
- [ ] Implement Scale interface, for Amount
- [ ] Look into APIs for inventory, accounting, payment


# Self-Checkout
Project to simulate the real-world self-checkout system

## System Description:

Self-Checkout System is a transactional retail system for customers to scan, weigh, and buy items while integrating with external inventory, accounting systems, and employee oversight. Inventory accuracy is improved by reserving items locally for an open transaction and permanently altering inventory after payment. Waste is reduced by fraud detection with weight validation and employee intervention. The system balances security and throughput with usability by incorporating state-based control and human-in-the-loop escalation. 

Self-Checkout functional requirements are touch screen UI, bar code scanner, receipt printer, and scale that are integrated with a store inventory system, accounting and payment processing, and employee oversight. The inventory system and accounting are external software for systems of record. The conditions for success are a smooth flow of a customer experience considering voided transactions and anti-theft, the individual items are scanned and the transaction accounted for.
## Architecture Overview
```
┌─────────────────────────────────────────────────────────────┐
│                  MAIN / User Interface                      │
│            (Orchestrates the scanning workflow)             │
└─────────────────────────────────────────────────────────────┘
                              │
        ┌─────────────────────┼─────────────────────┐
        │                     │                     │
        ▼                     ▼                     ▼
   ┌─────────────┐   ┌──────────────────┐   ┌────────────┐
   │   System    │   │  Transaction     │   │  Payment   │
   │   State     │   │  Management      │   │ Processing │
   │ (FSM)       │   │  (cart)          │   │            │
   └─────────────┘   └──────────────────┘   └────────────┘
        │                     │                     │
        │          ┌──────────┴──────────┐          │
        │          ▼                     ▼          │
        │      ┌─────────────┐    ┌────────────┐   │
        │      │Transaction  │    │ Product    │   │
        │      │Item         │    │ Record     │   │
        │      └─────────────┘    └────────────┘   │
        │                                           │
        └───────────────────────┬───────────────────┘
                                ▼
                    ┌───────────────────────┐
                    │   Ledger & Logging    │
                    │   CSV Storage         │
                    │   Override Records    │
                    └───────────────────────┘
```
Transaction manager: maintain item list, calc totals, manage state, handle rollback, commit transaction

## Data Model

| Class            | Attributes                                                                                 | Methods                                                                                                                          |
| ---------------- | ------------------------------------------------------------------------------------------ | -------------------------------------------------------------------------------------------------------------------------------- |
| Transaction      | `transactionID` `customerID` <br>`timestamp`<br>`paymentStatus`                            | `addItem()` `removeItem()` `calculateTotal()` `cancel()` `commit()`                                                              |
| TransactionItem  | `itemID`<br>`name`<br>`price`<br>`weight (nullable)`<br>`qty` `taxRate`                    | `calcPrice(itemID, price, weight, taxRate)`                                                                                      |
| Inventory Record | `sku`<br>`onHand`<br>`reserved`<br>`lastUpdated`<br>                                       | `reserve(itemID, qty)` `release(transactionID)` `commit(transactionID)`                                                          |
| Payment          | `paymentID` `transactionID` `amount` `status` `method`                                     | `processPayment()`                                                                                                               |
| Ledger           | `entryID` `transactionID` `subtotal` `tax` `total` `timestamp`                             | `ledgerEntry(customerID, transactionID, total, tax, timestamp)`                                                                  |
| SystemState      | `currentStatus` `event`                                                                    | `transition(event)`                                                                                                              |
| Override         | `suspensionCount`<br>`employeeOverrideFlag` `overrideID` `employeeID` `timestamp` `reason` | `toleranceThreshold()` `flagEmployeeOverride()`  `commitTimestamp(timestamp)` `logOverride(employeeID, timestamp)` `authorize()` |
| Scale            | `deviceID` `status`                                                                        | `readWeight()`                                                                                                                   |

## Use Cases:
### Actors:
Customers, Self-Checkout Employee, Scale, Inventory System, Accounting, Payment Processor
### Use Cases:
Customer buys a packaged item (stick of gum)

Customer buys priced per weight (bag of apples)

Customer cancels a transaction

System detects too many suspensions

Self-Checkout Employee detects a potential attempt to steal

### Use Cases:

Customer buys a packaged item (stick of gum)

Customer buys priced per weight (bag of apples)

Customer cancels a transaction

System detects too many suspensions

Self-Checkout Employee detects a potential attempt to steal

### Use Case Descriptions:

**Customer Buys a Packaged Item UC-01**

**Actors:** Customers, Inventory System, Accounting, Payment Processor

**Goal:** Complete a transaction for the customer’s grocery items

**Precondition:** The item has a scannable bar code. The self-checkout is in a ready state

**Main Flow:**

1. Customer scans packaged item (gum)
    
2. Inventory system retrieves item record
    
3. Inventory system adds the item to the local transaction
    
4. System updates running total with price of gum
    
5. Customer selects “Finish and Pay”
    
6. The system displays the total with tax included
    
7. System sends the total to the payment processor
    
8. Customer pays with cash/card/mobile
    
9. Payment is authorized
    
10. System commits the transaction to the store records, inventory and accounting entry updated
    
11. System prints a receipt of the transaction
    

**Alternative Flow:**

Scanned item in Step 1 is unreadable: system prompts “Please re-scan or enter the item code” and after three failures alert the self-checkout employee. Suspension counter increments per incident

Payment is declined in Step 9: system prompts a retry, after three attempts cancel the transaction. Suspension counter increments per incident

**Post-conditions:** The payment is authorized, the inventory permanently decreased, and accounting records the transaction. Also, a receipt is generated. System returns to ready.

  
  

**Customer Buys a Priced-per-Weight Item UC-02**

**Actors:** Customers, Scale, Inventory System, Accounting, Payment Processor

**Goal:** Complete a transaction for the customer’s grocery items

**Precondition:** The item has a scannable bar code. The self-checkout is in a ready state

**Main Flow:**

1. Customer scans produce bar code OR selects “Produce” then “Apples”
    
2. System prompts “Place the item on the scale”
    
3. Scale returns weight
    
4. Inventory system retrieves item record
    
5. System calculates the price: unit price per pound x measured weight
    
6. Inventory system adds the item to the local transaction
    
7. System updates running total with items
    
8. Customer selects “Finish and Pay”
    
9. The system displays the total with tax included
    
10. System sends the total to the payment processor
    
11. Customer pays with cash/card/mobile
    
12. Payment is authorized
    
13. System commits the transaction to the store records, inventory and accounting entry updated
    
14. System prints a receipt of the transaction
    
    **Alternative Flow:**
    

Scanned item in Step 1 is unreadable: system prompts “Please re-scan or enter the item code” and after three failures alert the self-checkout employee. Suspension counter increments per incident

Item removed or exceeds limit during weighing in Step 3: system prompts “Please re-weigh the item” and after three attempts call over the self-checkout employee. Suspension counter increments per incident

Payment is declined in Step 12: system prompts a retry, after three attempts cancel the transaction. Suspension counter increments per incident

**Post-conditions:** The payment is authorized, the inventory permanently decreased, and accounting records the transaction. Also, a receipt is generated. System returns to ready.

  
  

**Customer Cancels a Transaction UC-03**

**Actors:** Customers, Self-Checkout Employee, Inventory System, Accounting

**Goal:** Cancel a transaction for the customer’s grocery items

**Precondition:** The self-checkout is in a open transaction state

**Main Flow:**

1. Customer selects “Cancel transaction”
    
2. System prompts confirmation “Are you sure you want to cancel the transaction”
    
3. Customer confirms
    
4. System releases local transaction inventory and running total
    

**Alternative Flow:**

Customer declines canceling the transaction in Step 3: the state of the transaction is resumes

**Post-conditions:** System returns to ready.

  
  

**System Detects Too Many Suspensions UC-04**

**Actors:** Customers, Inventory System, Accounting, Self-Checkout Employee

**Goal:** Protect the system from repeated suspensions and ensure throughput

**Precondition:** The self-checkout is in a open transaction state and has been flagged for suspending the transaction five times (threshold configurable)

**Main Flow:**

1. Self-checkout employee is alerted
    
2. Employee provides customer service by inquiring if the customer wants to continue
    
3. Employee cancels the transaction
    
4. System releases local transaction inventory and running total
    

**Alternative Flow:**

Customer indicates they would like to continue in Step 2: system resumes the transaction

**Post-conditions:** System returns to ready state

  
  

**Detecting a Potential Attempt To Steal UC-05**

**Actors:** Customers, Self-Checkout Employee, Inventory System, Accounting

**Goal:** Suspend a transaction for the customer’s selected grocery item

**Precondition:** The self-checkout is in a ready or open transaction state

**Main Flow:**

1. Self-checkout employee observes the customer
    
2. Customer moves an item to the bagging area without scanning or entering the item’s code
    
3. Employee inquires into the item with the information the system displays of the transaction
    
4. Customer scans the missing item
    

**Alternative Flow:**

Employee and customer interaction in Step 3 could result in different scenarios depending on what is decided: the employee makes a mistake and does not pursue re-scanning or the customer abandons the transaction in favor of re-scanning the item.

Automatic bagging area weight validation compares expected weight from the scale in Step 2: if mismatch exceeds threshold then suspend system for employee intervention. Suspension counter increments

**Post-conditions:** System returns to open transaction and the transaction continues.

# Requirements
## Non-functional Requirements
### Performance

- Scan-to-response < 300ms
- Payment processing < 3 seconds

### Availability

- 99.9% uptime during store hours

### Security

- Encrypted payment processing
- Employee authentication required for overrides
- Audit logs retained

###  Usability

- Max five touches to complete payment
- Clear error messages 

1. **Requirement ID:** Inventory API REQ-01
    
    **Description:** Reserve, release, and permanently decrease inventory stock records
	1. Decrease available inventory when `reserve(itemID, qty)` is called **if sufficient stock exists**
	2. Reject the reservation with an error if `qty > available stock`
	3. Associate reserved inventory with a `transactionID`
	4. Restore reserved inventory when `release(transactionID)` is called
	5. Permanently decrease inventory when `commit(transactionID)` is called
	
	**Acceptance Criteria (Tests):**
	
	- Reserving valid quantity reduces available stock
	- Reserving excessive quantity returns error
	- Releasing restores stock to original level
	- Commit permanently reduces stock
    
    **Priority:** High
    
    **Notes:** reserve (itemID, qty), release (transactionID), commit (transactionID)
    
2. **Requirement ID:** Accounting API REQ-02
    
    **Description:** Reserve, release, and log entries of accounting records.
    1. Create a ledger entry when a transaction is committed
	2. Include `customerID`, `transactionID`, `subtotal`, `tax`, `total`, and `timestamp`
	3. Ensure ledger entries are immutable after creation
	
	**Acceptance Criteria:**
	
	- Ledger entry is created on commit
	- Entry contains all required fields
	- Entry cannot be modified after creation
    
    **Priority:** High
    
    **Notes:** ledgerEntry (customerID, transactionID, total, tax, timestamp)
    
3. **Requirement ID:** Payment API REQ-03
    
    **Description:** Process customer payment
    1. Send payment requests including transaction total and payment method
	2. Receive success or failure response from payment processor
	3. Transition system state to:
	    - `Payment Processing` during request
	    - `Completed` on success
	    - `Failed` on error
	
	**Acceptance Criteria:**
	
	- Successful payment transitions to `Completed`
	- Failed payment transitions to `Failed`
	- Payment request includes correct total
	
    **Priority:** High
    
    **Notes:**
    
4. **Requirement ID:** Scale Interface REQ-04
    
    **Description:** Software for customer’s use of scale and process price-per-weight items.
    1. Capture weight input for price-per-weight items
	2. Calculate item price using `price × weight`
	3. Trigger an alert if measured weight deviates beyond `toleranceThreshold`
	4. Allow employee override when flagged
	
	**Acceptance Criteria:**
	
	- Correct price is calculated from weight
	- Out-of-threshold weights trigger alert
	- Override allows continuation
    
    **Priority:** Medium
    
    **Notes:** toleranceThreshold (), flagEmployeeOverride ()
    
5. **Requirement ID:** Maintain Item List REQ-05
    
    **Description:** Maintain temporary customer’s inventory list.
    1. Maintain a temporary transaction record containing:
    - `transactionID`
    - Item IDs
    - Item names
    - Quantities
    - Weights (if applicable)
	1. Update the list when items are added or removed
	2. Delete the record when the transaction is canceled or completed
	
	**Acceptance Criteria:**
	
	- Items appear correctly after scan
	- Items are removed correctly
	- Record is cleared after cancel/commit
	
    **Priority:** High
    
    **Notes:** Includes the transactionID, item ids, name, weight, and quantity.
    
6. **Requirement ID:** Calculate Totals REQ-06
    
    **Description:** Algorithm to accurately maintain customers running total and temporary record.
    1. Calculate `subtotal` as the sum of all item prices
	2. Calculate `tax` as `subtotal × tax_rate`
	3. Calculate `total = subtotal + tax`
	4. Update totals immediately after any item change
	
	**Acceptance Criteria:**
	
	- Totals match expected values
	- Tax is applied correctly
	- Totals update in real time
    
    **Priority:** High
    
    **Notes:** Includes items name, id, total, and tax
    
7. **Requirement ID:** Manage System State REQ-07
    
    **Description:** Software to maintain the state and subsequent events
	The system shall maintain the following states:
	
	`Idle`, `Scanning`, `Awaiting Weight`, `Awaiting Payment`, `Payment Processing`, `Suspended`, `Canceled`, `Completed`
	
	The system shall:
	
	1. Transition from `Idle → Scanning` when a transaction begins
	2. Transition to `Awaiting Weight` for weight-based items
	3. Transition to `Awaiting Payment` when scanning is complete
	4. Prevent invalid state transitions
	5. Transition to `Suspended` when override is required
	
	**Acceptance Criteria:**
	
	- Valid transitions succeed
	- Invalid transitions are rejected
	- Override triggers `Suspended`
    
    **Priority:** High
    
    **Notes:** Includes employee override flag and the statuses are: Idle, Scanning, Awaiting Weight, Awaiting Payment, Payment Processing, Suspended (Awaiting Assistance), Canceled
    
8. **Requirement ID:** Handle Rollback REQ-08
    
    **Description:** Software to handle events of canceled transaction, clearing the reserved inventory and transaction records.
    When a transaction is canceled, the system shall:

	1. Release all reserved inventory
	2. Delete the transaction record
	3. Reset system state to `Idle`
	
	**Acceptance Criteria:**
	
	- Inventory is restored after cancel
	- Transaction data is removed
	- System returns to `Idle`
    
    **Priority:** High
    
    **Notes:**
    
9. **Requirement ID:** Commit Transaction REQ-09
    
    **Description:** Software to handle the events of a transaction completed.
    When a transaction is successfully completed, the system shall:
	
	1. Commit inventory changes
	2. Record a ledger entry
	3. Store a transaction completion timestamp
	4. Transition system state to `Completed`
	
	**Acceptance Criteria:**
	
	- Inventory is permanently reduced
	- Ledger entry is created
	- Timestamp is recorded
    
    **Priority:** High
    
    **Notes:** Includes the commit timestamp
    
10. **Requirement ID:** Security REQ-10
    
    **Description:** Encrypted payment processing, employee authentication required for overrides and audit logs retained
	The system shall:
	
	1. Require employee authentication for all override actions
	2. Log all override actions with `employeeID` and timestamp
	3. Ensure payment data is transmitted securely
	
	**Acceptance Criteria:**
	
	- Unauthorized override attempts are rejected
	- Override actions are logged
	- Payment requests are encrypted (verified via configuration)
    
    **Priority:** Low
    
11. **Requirement ID:** Performance REQ-11
    
    **Description:** Transaction Completion in < 2s, Scale Response in < 1s
	The system shall:
	
	1. Complete transactions within **2 seconds** under normal load
	2. Process scale input within **1 second**
	
	**Acceptance Criteria:**
	
	- Transaction timing ≤ 2 seconds
	- Scale response ≤ 1 second
    
    **Priority:** Low
    
12. **Requirement ID:** Reliability REQ-12
    
    **Description:** Operating 99.9% of the time
	The system shall maintain **99.9% uptime measured over a 30-day period**
	
	**Acceptance Criteria:**
	
	- Downtime does not exceed 0.1% over measurement window
    
    **Priority:** Low
    

### **Traceability to Use Cases**

REQ-01 to UC-01, UC-02, UC-03, UC-04, UC-05

REQ-02 to UC-01, UC-02

REQ-03 to UC-01, UC-02

REQ-04 to UC-02

REQ-05 to UC-01, UC-02, UC-03, UC-05

REQ-06 to UC-01, UC-02

REQ-07 to UC-01, UC-02, UC-03, UC-04, UC-05

REQ-08 to UC-03, UC-04

REQ-09 to UC-01, UC-02

REQ-10 to UC-04, UC-05

REQ-11 to UC-01, UC-02

REQ-12 to UC-01, UC-02, UC-03, UC-04, UC-05
   
|Traceability|UC-01|UC-02|UC-03|UC-04|UC-05|
| --- | --- | --- | --- | --- | --- |
|REQ-01|X|X|X|X|X|
|REQ-02|X|X||||
|REQ-03|X|X||||
|REQ-04||X||||
|REQ-05|X|X|X||X|
|REQ-06|X|X||||
|REQ-07|X|X|X|X|X|
|REQ-08|||X|X||
|REQ-09|X|X||||
|REQ-10||||X|X|
|REQ-11|X|X||||
|REQ-12|X|X|X|X|X|
# State Transition Model
## System States
System is a machine of states, defining a set of states:

    - Idle
    - Scanning
    - Awaiting Weight
	- Awaiting Payment 
	- Payment Processing
	- Suspended (Assistance Required)
	- Cancelled
	- Completed
Transitions between states:

`Idle → Scanning → Payment → Completed`

`Scanning → Suspended → Scanning`

`Scanning → Cancelled → Idle `

| Current State      | Event                | Next State         |
| ------------------ | -------------------- | ------------------ |
| Idle               | First Scan           | Scanning           |
| Scanning           | Produce Selected     | Awaiting Weight    |
| Awaiting Weight    | Weight Received      | Scanning           |
| Scanning           | Finish & Pay         | Awaiting Payment   |
| Awaiting Payment   | Payment Submitted    | Payment Processing |
| Payment Processing | Authorized           | Commit + Idle      |
| Payment Processing | Declined (3x)        | Canceled           |
| Any                | Cancel               | Canceled           |
| Any                | Suspension Threshold | Suspended          |
| Suspended          | Employee Override    | Scanning           |
| Suspended          | Employee Cancel      | Canceled           |
