#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>
#include <vector>

/**
 * @class Display
 * @brief Abstract base class for all entities that can be displayed.
 *
 * This class serves as an interface for the Hospital Management System,
 * enforcing a consistent display structure across Doctors, Patients, and Rooms.
 * Demonstrates the concept of Abstraction and Interface design in C++.
 */
class Display
{
public:
    /**
     * @brief Pure virtual function to be implemented by derived classes.
     */
    virtual void displayDetails() = 0;

    /**
     * @brief Virtual destructor to ensure proper cleanup of derived objects.
     */
    virtual ~Display() {}
};
