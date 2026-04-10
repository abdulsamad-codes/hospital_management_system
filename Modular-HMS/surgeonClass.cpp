#include "surgeonClass.h"
#include <iostream>

using namespace std;

int Surgeon::totalSurgeons = 0;

Surgeon::Surgeon() : Doctor()
{
    totalSurgeons++;
}

void Surgeon::displayDetails()
{
    cout << "[Specialist: Surgeon]\n";
    Doctor::displayDetails();
    cout << "Duty Description: Performs specialized surgical procedures.\n";
}
