#pragma once
#include <iostream>

class Room
{
    int roomNumber;

public:
    Room(int roomNumber = 0);
    void displayRoomDetails();
    void setRoomNumber(int);
    int getRoomNumber() const { return roomNumber; }
};
