#include "Scale.h"

Scale::Scale() : weight(2.0), deviceID(12345) {}


 double Scale::readWeight()
{
    // Method to read weight from the scale
    return weight;
    
}


int Scale::getDeviceID() const
{
    return deviceID;
}
