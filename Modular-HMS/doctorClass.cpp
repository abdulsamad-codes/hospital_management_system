#include "doctorClass.h"
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

int Doctor::totalDoctors = 0;

Doctor::Doctor()
    : doctorID(0), doctorName("Unknown"), doctorSpecialization("Unknown"), yearsOfExperience(0),
      isDoctorAvailable(false), room(0) {}

void Doctor::displayDetails()
{
    cout << "Doctor Name: " << doctorName << "\n";
    cout << "Doctor Specialization: " << doctorSpecialization << "\n";
    cout << "Doctor ID: " << doctorID << "\n";
    cout << "Years of Experience: " << yearsOfExperience << "\n";
    cout << "Room Number: " << room.getRoomNumber() << endl;
    cout << "Doctor Availability Status: " << (isDoctorAvailable ? "Available" : "Not Available") << "\n";
}

void Doctor::inputFromFile(ifstream &file)
{
    string label;
    file >> label >> label;
    getline(file >> ws, doctorName);
    file >> label;
    getline(file >> ws, doctorSpecialization);
    file >> label >> label;
    file >> doctorID;
    file >> label >> label >> label;
    file >> yearsOfExperience;
    file >> label >> label;
    int roomNum;
    file >> roomNum;
    room.setRoomNumber(roomNum);
    file >> label >> label >> label;
    string status;
    getline(file >> ws, status);
    isDoctorAvailable = (status == "Available");
}

void Doctor::saveToFile(ofstream &file) const
{
    file << "Doctor Name: " << doctorName << endl
         << "Doctor Specialization: " << doctorSpecialization << endl
         << "Doctor ID: " << doctorID << endl
         << "Years of Experience: " << yearsOfExperience << endl
         << "Room Number: " << room.getRoomNumber() << endl
         << "Doctor Availability Status: " << (isDoctorAvailable ? "Available" : "Not Available")
         << "\n\n";
}

void Doctor::setDoctorName(string name) { doctorName = name; }
void Doctor::setDoctorSpecialization(string spec) { doctorSpecialization = spec; }
void Doctor::setDoctorID(int id) { doctorID = id; }
void Doctor::setYearsOfExperience(int exp) { yearsOfExperience = exp; }
void Doctor::setDoctorAvailabilityStatus(bool status) { isDoctorAvailable = status; }

int doctorMain(vector<Doctor> &doctor)
{
    doctor.clear();
    Doctor::totalDoctors = 0;
    ifstream file("doctor_records.txt");
    if (!file.is_open())
        return 1;
    doctor.reserve(NumberOfDoctors);
    while (doctor.size() < NumberOfDoctors)
    {
        if (file.eof())
            break;
        char peek = file.peek();
        if (peek == ifstream::traits_type::eof())
            break;
        Doctor d;
        d.inputFromFile(file);
        if (file.fail())
        {
            if (file.eof())
                break;
            file.clear();
            file.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        doctor.push_back(d);
        Doctor::totalDoctors++;
    }
    file.close();
    return 0;
}

void doctorManagement(vector<Doctor> &doctor)
{
    doctorMain(doctor);
    int userChoice;
    do
    {
        cout << "\n\t\t------> Doctor Management <------" << endl;
        cout << "\t\t 1. Display All Doctors Details " << endl;
        cout << "\t\t 2. Display Details Of specific Doctor " << endl;
        cout << "\t\t 3. Add a Doctor " << endl;
        cout << "\t\t 4. Assign a Doctor " << endl;
        cout << "\t\t 5. Go Back To The Main Menu " << endl;
        cout << "\nEnter your choice: ";
        while (!(cin >> userChoice) || userChoice < 1 || userChoice > 5)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Invalid Choice. Enter (1-5): ";
        }
        if (userChoice == 5)
            return;
        switch (userChoice)
        {
        case 1:
            displayAllDoctors();
            break;
        case 2:
            displaySpecificDoctorDetails(doctor);
            break;
        case 3:
            addDoctor(doctor);
            break;
        case 4:
            assignDoctor(doctor);
            break;
        }
    } while (true);
}

void displayAllDoctors()
{
    ifstream file("doctor_records.txt");
    if (!file)
    {
        cout << "No doctor records found." << endl;
        return;
    }
    cout << "\n\t\tAll Doctors:\n--------------------------\n";
    string line;
    while (getline(file, line))
        cout << line << endl;
    cout << "--------------------------\n";
    file.close();
}

void displaySpecificDoctorDetails(vector<Doctor> &doctor)
{
    if (doctor.empty())
    {
        cout << "No doctors in the system!\n";
        return;
    }
    int id;
    cout << "Enter Doctor ID: ";
    if (!(cin >> id))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid ID format.\n";
        return;
    }
    for (auto &d : doctor)
    {
        if (d.getDoctorID() == id)
        {
            d.displayDetails();
            return;
        }
    }
    cout << "Doctor not found.\n";
}

void addDoctor(vector<Doctor> &doctor)
{
    Doctor d;
    string name, spec;
    int id, exp, rnum;
    bool avail;
    cout << "Enter Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);
    cout << "Enter Specialization: ";
    getline(cin, spec);
    cout << "Enter ID: ";
    while (!(cin >> id))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid ID. Enter a number: ";
    }
    cout << "Enter Experience: ";
    while (!(cin >> exp))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid experience. Enter a number: ";
    }
    cout << "Enter Room: ";
    while (!(cin >> rnum))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid room. Enter a number: ";
    }
    cout << "Available (1 for Yes, 0 for No): ";
    while (!(cin >> avail))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter 1 or 0: ";
    }
    d.setDoctorName(name);
    d.setDoctorSpecialization(spec);
    d.setDoctorID(id);
    d.setYearsOfExperience(exp);
    d.room.setRoomNumber(rnum);
    d.setDoctorAvailabilityStatus(avail);
    doctor.push_back(d);
    Doctor::totalDoctors++;
    appendDoctorToFile(d);
}

void assignDoctor(vector<Doctor> &doctor)
{
    int id;
    cout << "Enter Doctor ID to assign: ";
    cin >> id;
    for (auto &doc : doctor)
    {
        if (doc.getDoctorID() == id)
        {
            if (doc.getDoctorAvailabilityStatus())
            {
                doc.setDoctorAvailabilityStatus(false);
                updateDoctorInFile(doc);
                cout << "Doctor assigned.\n";
            }
            else
                cout << "Doctor not available.\n";
            return;
        }
    }
    cout << "Doctor not found.\n";
}

void appendDoctorToFile(Doctor &newDoc)
{
    ofstream file("doctor_records.txt", ios::app);
    if (file)
    {
        newDoc.saveToFile(file);
        file.close();
    }
}

void updateDoctorInFile(const Doctor &d)
{
    vector<Doctor> doctors;
    ifstream inFile("doctor_records.txt");
    while (!inFile.eof())
    {
        Doctor temp;
        temp.inputFromFile(inFile);
        if (!inFile.fail())
            doctors.push_back(temp);
    }
    inFile.close();
    for (auto &doc : doctors)
        if (doc.getDoctorID() == d.getDoctorID())
        {
            doc = d;
            break;
        }
    ofstream outFile("doctor_records.txt");
    for (const auto &doc : doctors)
        doc.saveToFile(outFile);
    outFile.close();
}
