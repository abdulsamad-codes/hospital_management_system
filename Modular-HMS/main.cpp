#include "doctorClass.h"
#include "patientClass.h"
#include <iostream>
#include <vector>

void displayMenu(std::vector<Doctor> &doctor, std::vector<Patient> &patient)
{
    int choice;
    do
    {
        std::cout << "\t\t------> Hospital Management System <------\n";
        std::cout << "\t\t 1. Doctor Management\n";
        std::cout << "\t\t 2. Patient Management\n";
        std::cout << "\t\t 3. Exit\n";
        std::cout << "Choice: ";
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }
        if (choice == 3)
            break;
        if (choice == 1)
            doctorManagement(doctor);
        else if (choice == 2)
            patientManagement(patient);
    } while (true);
}

int main()
{
    std::vector<Patient> patient;
    std::vector<Doctor> doctor;
    displayMenu(doctor, patient);
    return 0;
}
