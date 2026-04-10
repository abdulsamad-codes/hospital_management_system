#pragma once
#include "doctorClass.h"

/**
 * @class Surgeon
 * @brief Specialized Doctor class representing a surgeon.
 *
 * This class demonstrates Multilevel Inheritance or Hierarchical Inheritance
 * (Display -> Doctor -> Surgeon). It overrides the duty() method to provide
 * specialized behavior.
 */
class Surgeon : public Doctor
{
private:
    static int totalSurgeons;

public:
    Surgeon();

    /**
     * @brief Specialized duty implementation for Surgeons.
     * Demonstrates Polmorphism via method overriding.
     */
    void displayDetails() override;

    static int getTotalSurgeons() { return totalSurgeons; }
};
