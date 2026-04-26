#ifndef SYSTEMSTATE_H
#define SYSTEMSTATE_H

#include <string>
#include <unordered_map>
#include <unordered_set>

// Skeleton of Finite State Machine
// Defines the various states and valid transitions between them

enum class SystemStatus
{
    Idle,
    Scanning,
    AwaitingWeight,
    AwaitingPayment,
    PaymentProcessing,
    Suspended,
    Canceled,
    Completed
};

class SystemState
{
public:
    SystemState();

    // State management
    SystemStatus getCurrentState() const;
    void transition(const std::string &event);
    bool canTransition(const std::string &event) const;

    // State query helpers

    // Get state as string for debugging/display

    // Reset to Idle
    void reset();

private:
    SystemStatus currentState;

    // Valid transitions map: current state -> set of valid events
    std::unordered_map<int, std::unordered_set<std::string>> validTransitions;

    // Initialize state machine transitions
    void initializeTransitions();
};

#endif // SYSTEMSTATE_H