class Scale
{
    // Skeleton for scale class, will be used to read weights
    // An abstraction of a real-world device
public:
    Scale();
    virtual double readWeight() = 0;
    virtual ~Scale() = default;
    int getDeviceID() const
    {
        return deviceID;
    }

private:
    double weight;
    int deviceID;
};