#ifndef TransactionSTATE_H
#define TransactionSTATE_H
class Transaction; // Forward declaration
class ProductRecord; // Forward declaration
enum class Result{
    Success,
    InvalidState,
    PaymentFailed
}; 

// Rules and transitions
// What's allowed and when to change state

class TransactionState {
public:
    virtual Result addItem(Transaction&, const
    ProductRecord&, double) = 0;
    virtual Result removeItem(Transaction&, int index) = 0;
    virtual Result finishScanning(Transaction&) = 0;
    virtual Result processPayment(Transaction&, Ledger&) = 0;
    virtual Result cancel(Transaction&) = 0;

    virtual ~TransactionState() = default;
};
#endif // TransactionSTATE_H