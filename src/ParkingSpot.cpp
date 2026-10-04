#include "../include/ParkingSpot.h"
#include<bits/stdc++.h>
using namespace std;

ParkingSpot::ParkingSpot(int spot): spotNumber(spot), vehicle(nullptr) {}

int ParkingSpot::getSpotNumber() { return spotNumber; }

bool ParkingSpot::isOccupied() { return vehicle!=nullptr; }

Vehicle* ParkingSpot::getVehicle() { return vehicle.get(); }

bool ParkingSpot::assignVehicle(unique_ptr<Vehicle> newvehicle) {
    if(isOccupied()||newvehicle==nullptr) return false;

    vehicle=move(newvehicle);
    return true;
}

bool ParkingSpot::clearVehicle(string& vehicleNumber) {
    if(!isOccupied()||vehicle->getNumber()!=vehicleNumber) {
        return false;
    }

    vehicle.reset();
    return true;
}