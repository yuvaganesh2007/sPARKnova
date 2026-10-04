#ifndef PARKING_LOT_H
#define PARKING_LOT_H

#include "ParkingSpot.h"
#include <memory>
#include <string>
#include <vector>

class ParkingLot {
private:
    std::vector<ParkingSpot> spots;

public:
    explicit ParkingLot(int numberOfSpots);

    bool parkVehicle(std::unique_ptr<Vehicle> vehicle);
    bool removeVehicle(const std::string& vehicleNumber);
    void displayStatus() ;
};

#endif