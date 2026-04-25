class transaction
{
public:
    transaction()
    {
        // Constructor implementation
    }

    void transaction::addItem(const productRecord& product, double amount)
    {
        // Add item to the transaction
    }
    void removeItem()
    {
        // Remove item from the transaction
    }
    void calculateTotal()
    {
        // Calculate total amount for the transaction
    }
    double getSubtotal() const
    {
        // Return the subtotal for the transaction
    }
    double getTaxTotal() const
    {
        // Return the total tax for the transaction
    }
    double getTotal() const
    {
        // Return the total amount for the transaction
    }
    void cancel()
    {
        // Cancel the transaction
    }
    void commit()
    {
        // Commit the transaction
    }
    std::vector<std::unique_ptr<transactionItem>> items;

private:
    int transactionID;
    int customerID;
    int timeStamp;
    bool paymentStatus;
};