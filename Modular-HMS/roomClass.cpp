#include "roomClass.h"
#include <iostream>

Room::Room(int roomNumber) : roomNumber(roomNumber) {}

void Room::displayRoomDetails()
{
    std::cout << "Room Number: " << roomNumber << std::endl;
}

void Room::setRoomNumber(int roomNumber)
{
    this->roomNumber = roomNumber;
}
