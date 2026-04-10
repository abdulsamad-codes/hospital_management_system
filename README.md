# Hospital Management System (HMS)

A robust, Object-Oriented C++ application designed to manage hospital workflows, including doctor assignments, patient records, and room allocations.

## 🚀 Key Features

- **Doctor Management**: Track details, specialization, experience, and availability.
- **Patient Management**: Manage admissions, discharges, and medical history.
- **Room Allocation**: Associate doctors with specific hospital rooms.
- **File Persistence**: Automatic saving and loading of records from text files.
- **Polymorphic Design**: Utilizes abstract base classes and inheritance for scalable entities.

## 🛠️ Concepts Demonstrated (Portfolio Highlights)

- **Object-Oriented Programming (OOP)**: Real-world modeling using Classes and Objects.
- **Encapsulation**: Private data members with public getters/setters.
- **Inheritance**: Specialized classes (e.g., `Surgeon` inheriting from `Doctor`).
- **Polymorphism**: Dynamic method overriding for specialized display logic.
- **Abstraction**: Interface design using pure virtual functions in `Display` class.
- **File I/O**: Persistent storage using `std::ifstream` and `std::ofstream`.

## 📂 Project Structure

- `1/`: Modular version . Highlights clean code and dependency management.
- `2/`: Monolithic version. All-in-one file implementation.

## ⚙️ Compilation & Setup

To compile the modular version using G++:

```bash
g++ -o hms main.cpp doctorClass.cpp patientClass.cpp roomClass.cpp surgeonClass.cpp
./hms
```

## 👤 Author

Developed as part of the 2nd Semester OOP Theory curriculum at Institute Of Management Sciences Peshawar.
