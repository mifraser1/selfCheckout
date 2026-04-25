#ifndef SYSTEMSTATE_H
#define SYSTEMSTATE_H
#include <string>

class systemState {
public:
    systemState() {
        // Constructor implementation
    };
    void transition(std::string event) {
        // Method to update system state
    };
private:
    std::string currentStatus;
    std::string event;
};
#endif // SYSTEMSTATE_H