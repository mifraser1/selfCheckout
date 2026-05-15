#ifndef MockScale_H
#define MockScale_H
#include "Scale.h"

class MockScale : public Scale {
public:
    double readWeight() override {
        return 1.25;
    }
};
#endif // MockScale_H