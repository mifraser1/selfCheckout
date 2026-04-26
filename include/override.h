#ifndef OVERRIDE_H
#define OVERRIDE_H
#include <string>
#include <ctime>

class override {
    // Skeleton for override class, will be used for employee interventions

public:
    override() {    
        // Constructor implementation
    }

    bool toleranceCheck() {
        // Method to check if the number of overrides has exceeded the tolerance threshold
    }

    void setToleranceThreshold(int toleranceThreshold) {
        // Method to set the tolerance threshold for overrides
    }

    bool flagEmployeeOverride() {
        // Method to flag an override for review based on employee ID
    }

    void commitTimeStamp(time_t timestamp) {
        // Method to commit the timestamp of the override
    }

    void logOverride(int employeeID, std::string reason, time_t timestamp) {
        // Method to log the override details for auditing purposes
    }

    void authorize() {
        // Method to authorize the override 
    }

private:
    int suspensionCount;
    int toleranceThreshold;
    bool employeeOverrideFlag;
    int overrideID;
    int employeeID;
    time_t timestamp;
    std::string reason;

};
#endif // OVERRIDE_H