#pragma once
#include "displayClass.h"
#include "roomClass.h"
#include <vector>
#include <string>

#define NumberOfDoctors 30

/**
 * @class Doctor
 * @brief Represents a medical professional in the hospital.
 *
 * Inherits from Display to provide unified output handling.
 * Includes association with the Room class to track workplace location.
 */
class Doctor : public Display
{
    std::string doctorName;
    std::string doctorSpecialization;
    int doctorID;
    int yearsOfExperience;
    bool isDoctorAvailable;

public:
    Room room;               ///< Association: A doctor is assigned to a room
    static int totalDoctors; ///< Encapsulated static count of all doctors

    Doctor();

    /**
     * @brief Implementation of virtual display from Display class.
     */
    void displayDetails() override;

    /**
     * @brief Deserialization from file stream.
     */
    void inputFromFile(std::ifstream &file);

    /**
     * @brief Serialization to file stream.
     */
    void saveToFile(std::ofstream &file) const;

    // Getters and Setters (Encapsulation)
    void setDoctorName(std::string name);
    void setDoctorSpecialization(std::string spec);
    void setDoctorID(int id);
    void setYearsOfExperience(int exp);
    void setDoctorAvailabilityStatus(bool status);

    std::string getDoctorName() const { return doctorName; }
    std::string getDoctorSpecialization() const { return doctorSpecialization; }
    int getDoctorID() const { return doctorID; }
    int getYearsOfExperience() const { return yearsOfExperience; }
    bool getDoctorAvailabilityStatus() const { return isDoctorAvailable; }
    static int getTotalDoctors() { return totalDoctors; }
};

int doctorMain(std::vector<Doctor> &doctor);
void doctorManagement(std::vector<Doctor> &doctor);
void displayAllDoctors();
void displaySpecificDoctorDetails(std::vector<Doctor> &doctor);
void addDoctor(std::vector<Doctor> &doctor);
void assignDoctor(std::vector<Doctor> &doctor);
void appendDoctorToFile(Doctor &newDoc);
void updateDoctorInFile(const Doctor &d);
