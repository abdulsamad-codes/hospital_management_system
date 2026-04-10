#include "patientClass.h"
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

int Patient::totalPatients = 0;

Patient::Patient() : patientName("Unknown"), patientDisease("Unknown"), patientID(0), patientAge(0), isAdmitted(false) {}

void Patient::displayDetails()
{
    cout << "Patient Name: " << patientName << "\n";
    cout << "Patient ID: " << patientID << "\n";
    cout << "Patient Disease: " << patientDisease << "\n";
    cout << "Patient Age: " << patientAge << "\n";
    cout << "Admission Status: " << (isAdmitted ? "Admitted" : "Not Admitted") << "\n";
}

void Patient::inputFromFile(ifstream &file)
{
    string label;
    file >> label >> label;
    getline(file >> ws, patientName);
    file >> label >> label;
    file >> patientID;
    file >> label >> label;
    getline(file >> ws, patientDisease);
    file >> label >> label;
    file >> patientAge;
    file >> label >> label >> label;
    string status;
    getline(file >> ws, status);
    isAdmitted = (status == "Admitted");
}

void Patient::saveToFile(ofstream &file) const
{
    file << "Patient Name: " << patientName << endl
         << "Patient ID: " << patientID << endl
         << "Patient Disease: " << patientDisease << endl
         << "Patient Age: " << patientAge << endl
         << "Patient Admission Status: " << (isAdmitted ? "Admitted" : "Not Admitted") << "\n\n";
}

void Patient::setPatientName(string name) { patientName = name; }
void Patient::setPatientDisease(string disease) { patientDisease = disease; }
void Patient::setPatientID(int id) { patientID = id; }
void Patient::setPatientAge(int age) { patientAge = age; }
void Patient::setPatientAdmissionStatus(bool status) { isAdmitted = status; }

int patientMain(vector<Patient> &patient)
{
    patient.clear();
    Patient::totalPatients = 0;
    ifstream file("patient_records.txt");
    if (!file.is_open())
        return 1;
    while (patient.size() < NumberOfPatients)
    {
        if (file.eof())
            break;
        char peek = file.peek();
        if (peek == ifstream::traits_type::eof())
            break;
        Patient p;
        p.inputFromFile(file);
        if (file.fail())
        {
            if (file.eof())
                break;
            file.clear();
            file.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        patient.push_back(p);
        Patient::totalPatients++;
    }
    file.close();
    return 0;
}

void patientManagement(vector<Patient> &patient)
{
    patientMain(patient);
    int choice;
    do
    {
        cout << "\n\t\t------> Patient Management <------\n";
        cout << "\t\t 1. Display All Patients\n";
        cout << "\t\t 2. Specific Patient Details\n";
        cout << "\t\t 3. Add Patient\n";
        cout << "\t\t 4. Admit Patient\n";
        cout << "\t\t 5. Discharge Patient\n";
        cout << "\t\t 6. Go Back\n";
        cout << "Enter choice: ";
        cin >> choice;
        if (choice == 6)
            return;
        switch (choice)
        {
        case 1:
            displayAllPatients();
            break;
        case 2:
            displaySpecificPatientDetails(patient);
            break;
        case 3:
            addPatient(patient);
            break;
        case 4:
            admitPatient(patient);
            break;
        case 5:
            dischargePatient(patient);
            break;
        }
    } while (true);
}

void displayAllPatients()
{
    ifstream file("patient_records.txt");
    if (!file)
    {
        cout << "No patient records.\n";
        return;
    }
    string line;
    while (getline(file, line))
        cout << line << endl;
    file.close();
}

void displaySpecificPatientDetails(vector<Patient> &patient)
{
    int id;
    cout << "Enter ID: ";
    if (!(cin >> id))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid ID format.\n";
        return;
    }
    for (auto &p : patient)
        if (p.getPatientID() == id)
        {
            p.displayDetails();
            return;
        }
    cout << "Patient not found.\n";
}

void addPatient(vector<Patient> &patient)
{
    Patient p;
    string name, disease;
    int id, age;
    bool adm;
    cout << "Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);
    cout << "Disease: ";
    getline(cin, disease);
    cout << "ID: ";
    while (!(cin >> id))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid ID. Enter a number: ";
    }
    cout << "Age: ";
    while (!(cin >> age))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid age. Enter a number: ";
    }
    cout << "Admitted (1 for Yes, 0 for No): ";
    while (!(cin >> adm))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter 1 or 0: ";
    }
    p.setPatientName(name);
    p.setPatientDisease(disease);
    p.setPatientID(id);
    p.setPatientAge(age);
    p.setPatientAdmissionStatus(adm);
    patient.push_back(p);
    Patient::totalPatients++;
    appendPatientToFile(p);
}

void admitPatient(vector<Patient> &patient)
{
    int id;
    cout << "ID: ";
    cin >> id;
    for (auto &p : patient)
        if (p.getPatientID() == id)
        {
            p.setPatientAdmissionStatus(true);
            updatePatientInFile(p);
            return;
        }
}

void dischargePatient(vector<Patient> &patient)
{
    int id;
    cout << "ID: ";
    cin >> id;
    for (auto &p : patient)
        if (p.getPatientID() == id)
        {
            p.setPatientAdmissionStatus(false);
            updatePatientInFile(p);
            return;
        }
}

void appendPatientToFile(Patient &p)
{
    ofstream file("patient_records.txt", ios::app);
    if (file)
    {
        p.saveToFile(file);
        file.close();
    }
}

void updatePatientInFile(const Patient &p)
{
    vector<Patient> patients;
    ifstream inFile("patient_records.txt");
    while (!inFile.eof())
    {
        Patient temp;
        temp.inputFromFile(inFile);
        if (!inFile.fail())
            patients.push_back(temp);
    }
    inFile.close();
    for (auto &pat : patients)
        if (pat.getPatientID() == p.getPatientID())
        {
            pat = p;
            break;
        }
    ofstream outFile("patient_records.txt");
    for (const auto &pat : patients)
        pat.saveToFile(outFile);
    outFile.close();
}
