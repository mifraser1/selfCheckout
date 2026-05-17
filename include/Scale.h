#ifndef Scale_H
#define Scale_H
#include "ProductRecord.h"

// Self Checkout system interface of the operations it needs - dependency injection/encapsulation

class Scale
{
public:
    Scale();
    virtual void connect() = 0;
    virtual void disconnect() = 0;
    virtual void calibrate() = 0;
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
#endif // Scale_H