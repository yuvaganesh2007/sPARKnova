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

    if(vehicle->getHourlyRate()<=0.0) {
        cout<<"Invalid bike type or car seat count.\n";
        return false;
    }

    for (ParkingSpot& spot : spots) {
        Vehicle* parked = spot.getVehicle();

        if (parked != nullptr && parked->getNumber() == vehicle->getNumber()) {
            cout << "That vehicle is already parked.\n";
            return false;
        }
    }

    for (ParkingSpot& spot : spots) {
        if (!spot.isOccupied()) {
             int assignedSpot = spot.getSpotNumber();

            if (spot.assignVehicle(move(vehicle))) {
                cout << "Vehicle parked in spot "<< assignedSpot << ".\n";
                return true;
            }
        }
    }

    cout << "No available parking spots.\n";
    return false;
}


bool ParkingLot::createCheckoutQuote(
    string& vehicleNumber,
    int parkedHours,
    int parkedMinutes,
    CheckoutQuote& quote)  {

    if (parkedHours < 0 || parkedMinutes < 0 || parkedMinutes > 59) {
        return false;
    }

    for (ParkingSpot& spot : spots) {
        Vehicle* vehicle = spot.getVehicle();

        if (vehicle != nullptr &&
            vehicle->getNumber() == vehicleNumber) {

            const double totalHours =
                parkedHours + parkedMinutes / 60.0;
            const double hourlyRate = vehicle->getHourlyRate();

            quote.vehicleNumber = vehicleNumber;
            quote.spotNumber = spot.getSpotNumber();
            quote.parkedHours = parkedHours;
            quote.parkedMinutes = parkedMinutes;
            quote.hourlyRate = hourlyRate;
            quote.totalAmount = hourlyRate * totalHours;

            return true;
        }
    }

    return false;
}

bool ParkingLot::completeCheckout( CheckoutQuote& quote) {
    for (ParkingSpot& spot : spots) {
        Vehicle* vehicle = spot.getVehicle();

        if (vehicle != nullptr &&
            vehicle->getNumber() == quote.vehicleNumber &&
            spot.getSpotNumber() == quote.spotNumber) {

            paymentRecords.push_back({
                quote.vehicleNumber,
                quote.spotNumber,
                quote.parkedHours,
                quote.parkedMinutes,
                quote.hourlyRate,
                quote.totalAmount,
                true
            });

            spot.clearVehicle(string vehicle->getNumber());

            cout << "Payment completed.\n"
                      << "Vehicle checked out from spot "
                      << quote.spotNumber << ".\n";
            return true;
        }
    }

    std::cout << "Checkout failed: vehicle was not found in that spot.\n";
    return false;
}

void ParkingLot::recordPaymentFailure(CheckoutQuote& quote) {
    paymentRecords.push_back({
        quote.vehicleNumber,
        quote.spotNumber,
        quote.parkedHours,
        quote.parkedMinutes,
        quote.hourlyRate,
        quote.totalAmount,
        false
    });

    std::cout << "Payment not completed. Vehicle remains parked.\n";
}

void ParkingLot::displayStatus() {
    cout << "\n--- Parking Lot Status ---\n";

    for (ParkingSpot& spot : spots) {
        cout << "Spot " << spot.getSpotNumber() << ": ";

        Vehicle* vehicle = spot.getVehicle();

        if (vehicle == nullptr) {
            cout << "Available\n";
        } else {
            cout << "Occupied\n"
                      << "Vehicle number: "
                      << vehicle->getNumber() << '\n';
            vehicle->displayDetails();
        }
    }
}

void ParkingLot::displayPaymentHistory() {
    cout << "\n--- Checkout and Payment History ---\n";

    if (paymentRecords.empty()) {
        cout << "No checkout attempts recorded.\n";
        return;
    }

    for ( ParkingRecord& record : paymentRecords) {
        cout << "\nVehicle: " << record.vehicleNumber
                  << "\nSpot: " << record.spotNumber
                  << "\nParked duration: " << record.parkedHours
                  << " hour(s), " << record.parkedMinutes << " minute(s)"
                  << "\nRate per hour: Rs. " << record.hourlyRate
                  << "\nAmount: Rs. " << fixed << setprecision(2)
                  << record.amount
                  << "\nPayment status: "
                  << (record.paymentCompleted
                          ? "Completed"
                          : "Not completed")
                  << '\n';
    }
}