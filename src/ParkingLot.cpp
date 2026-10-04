#include "../include/ParkingLot.h"
#include <bits/stdc++.h>
using namespace std;

ParkingLot::ParkingLot(int numberOfSpots) {
    for (int i = 1; i <= numberOfSpots; ++i) {
        spots.emplace_back(i);
    }
}

bool ParkingLot::parkVehicle(unique_ptr<Vehicle> vehicle) {
    if (vehicle == nullptr) {
        return false;
    }

    for (const ParkingSpot& spot : spots) {
        Vehicle* parked = spot.getVehicle();

        if (parked != nullptr &&
            parked->getNumber() == vehicle->getNumber()) {
            std::cout << "That vehicle is already parked.\n";
            return false;
        }
    }

    for (ParkingSpot& spot : spots) {
        if (!spot.isOccupied()) {
            const int assignedSpot = spot.getSpotNumber();

            if (spot.assignVehicle(move(vehicle))) {
                cout << "Vehicle parked in spot "
                          << assignedSpot << ".\n";
                return true;
            }
        }
    }

    cout << "No available parking spots.\n";
    return false;
}

bool ParkingLot::removeVehicle(const string& vehicleNumber) {
    for (ParkingSpot& spot : spots) {
        if (spot.releaseVehicle(vehicleNumber)) {
            cout << "Vehicle removed from spot "
                      << spot.getSpotNumber() << ".\n";
            return true;
        }
    }

    cout << "Vehicle was not found in the parking lot.\n";
    return false;
}

void ParkingLot::displayStatus() const {
    cout << "\n--- Parking Lot Status ---\n";

    for (const ParkingSpot& spot : spots) {
        cout << "Spot " << spot.getSpotNumber() << ": ";

        Vehicle* vehicle = spot.getVehicle();

        if (vehicle == nullptr) {
            cout << "Available\n";
        } else {
            cout << "Occupied by " << vehicle->getNumber() << '\n';
            vehicle->displayDetails();
        }
    }
}