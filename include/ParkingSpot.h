#pragma once

#include "Vehicle.h"
#include<bits/stdc++.h>

class ParkingSpot {
    protected:
        int spotNumber;
        unique_ptr<Vehicle> vehicle;

    public:
        explicit ParkingSpot(int spot);

        int getSpotNumber();
        bool isOccupied();
        Vehicle* getVehicle();

        bool assignVehicle(unique_ptr<Vehicle> newvehicle);
        bool clearVehicle(string& vehicleNumber);
};