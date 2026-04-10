#pragma once
#include "displayClass.h"
#include <vector>
#include <string>

#define NumberOfPatients 50

/**
 * @class Patient
 * @brief Represents a patient in the hospital.
 *
 * Demonstrates encapsulation by keeping patient data private and
 * providing public accessors. Tracks admission status and medical history.
 */
class Patient : public Display
{
    std::string patientName;
    std::string patientDisease;
    int patientID;
    int patientAge;
    bool isAdmitted;

public:
    static int totalPatients;

    Patient();

    /**
     * @brief Implementation of virtual display from Display class.
     */
    void displayDetails() override;
    void inputFromFile(std::ifstream &file);
    void saveToFile(std::ofstream &file) const;
    void setPatientName(std::string name);
    void setPatientDisease(std::string disease);
    void setPatientID(int id);
    void setPatientAge(int age);
    void setPatientAdmissionStatus(bool status);
    std::string getPatientName() const { return patientName; }
    std::string getPatientDisease() const { return patientDisease; }
    int getPatientID() const { return patientID; }
    int getPatientAge() const { return patientAge; }
    bool getPatientAdmissionStatus() const { return isAdmitted; }
};

int patientMain(std::vector<Patient> &patient);
void patientManagement(std::vector<Patient> &patient);
void displayAllPatients();
void displaySpecificPatientDetails(std::vector<Patient> &patient);
void addPatient(std::vector<Patient> &patient);
void admitPatient(std::vector<Patient> &patient);
void dischargePatient(std::vector<Patient> &patient);
void appendPatientToFile(Patient &p);
void updatePatientInFile(const Patient &p);
