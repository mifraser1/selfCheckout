#include "systemState.h"
#include <stdexcept>

SystemState::SystemState() : currentState(SystemStatus::Idle)
{
    initializeTransitions();
}

void SystemState::initializeTransitions()
{
    // Define valid transitions for each state
    // Format: currentState -> set of valid events

    // From Idle


    // From Scanning
 
    // From AwaitingWeight
 
    // From AwaitingPayment

    // From PaymentProcessing

    // From Suspended

    // From Canceled


    // From Completed
    
}

SystemStatus SystemState::getCurrentState() const
{
    return currentState;
}

std::string SystemState::getStateString() const
{
    switch (currentState)
    {
    case SystemStatus::Idle:
        return "Idle";
    case SystemStatus::Scanning:
        return "Scanning";
    case SystemStatus::AwaitingWeight:
        return "AwaitingWeight";
    case SystemStatus::AwaitingPayment:
        return "AwaitingPayment";
    case SystemStatus::PaymentProcessing:
        return "PaymentProcessing";
    case SystemStatus::Suspended:
        return "Suspended";
    case SystemStatus::Canceled:
        return "Canceled";
    case SystemStatus::Completed:
        return "Completed";
    default:
        return "Unknown";
    }
}

void SystemState::transition(const std::string &event)
{

    // Perform state transition based on event
    if (event == "FirstScan" && currentState == SystemStatus::Idle)
    {
        currentState = SystemStatus::Scanning;
    }
    else if (event == "ProduceSelected" && currentState == SystemStatus::Scanning)
    {
        currentState = SystemStatus::AwaitingWeight;
    }
    else if (event == "WeightReceived" && currentState == SystemStatus::AwaitingWeight)
    {
        currentState = SystemStatus::Scanning;
    }
    else if (event == "FinishAndPay" && currentState == SystemStatus::Scanning)
    {
        currentState = SystemStatus::AwaitingPayment;
    }
    else if (event == "PaymentSubmitted" && currentState == SystemStatus::AwaitingPayment)
    {
        currentState = SystemStatus::PaymentProcessing;
    }
    else if (event == "PaymentAuthorized" && currentState == SystemStatus::PaymentProcessing)
    {
        currentState = SystemStatus::Completed;
    }
    else if (event == "PaymentDeclined" && currentState == SystemStatus::PaymentProcessing)
    {
        currentState = SystemStatus::Canceled;
    }
    else if (event == "SuspensionThreshold" && currentState == SystemStatus::Scanning)
    {
        currentState = SystemStatus::Suspended;
    }
    else if (event == "EmployeeOverride" && currentState == SystemStatus::Suspended)
    {
        currentState = SystemStatus::Scanning;
    }
    else if (event == "EmployeeCancel" && currentState == SystemStatus::Suspended)
    {
        currentState = SystemStatus::Canceled;
    }
    else if (event == "Cancel")
    {
        currentState = SystemStatus::Canceled;
    }
    else if (event == "Reset" && (currentState == SystemStatus::Canceled || currentState == SystemStatus::Completed))
    {
        currentState = SystemStatus::Idle;
    }
}

void SystemState::reset()
{
    currentState = SystemStatus::Idle;
}