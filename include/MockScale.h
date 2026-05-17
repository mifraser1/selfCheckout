#ifndef MockScale_H
#define MockScale_H
#include "Scale.h"

// Hardware implementation of the Scale interface
class MockScale : public Scale
{
public:
    MockScale() = default;
    void connect() override;
    void disconnect() override;
    void calibrate() override;    double readWeight() override
    {
        // Hardcoded to simluate real world reading
        return 1.25;
    }
};
#endif // MockScale_H