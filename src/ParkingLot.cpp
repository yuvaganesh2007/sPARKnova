#include "../include/ParkingLot.h"
#include <bits/stdc++.h>
using namespace std;

ParkingLot::ParkingLot(int numberOfSpots) {
    for (int i = 1; i <= numberOfSpots; ++i) {
        spots.emplace_back(i);
    }
}

bool ParkingLot::parkVehicle(
    unique_ptr<Vehicle> vehicle,
    int checkInHour,
    int checkInMinute
) {
    if (vehicle == nullptr) {
        return false;
    }

    if (vehicle->getHourlyRate() <= 0.0) {
        cout << "Invalid bike type or car seat count.\n";
        return false;
    }

    for (ParkingSpot& spot : spots) {
        Vehicle* parked = spot.getVehicle();

        if (parked != nullptr &&
            parked->getNumber() == vehicle->getNumber()) {
            cout << "That vehicle is already parked.\n";
            return false;
        }
    }

    for (ParkingSpot& spot : spots) {
        if (!spot.isOccupied()) {
            int assignedSpot = spot.getSpotNumber();
            const string vehicleNumber = vehicle->getNumber();

            if (spot.assignVehicle(move(vehicle))) {
                checkInTimes[vehicleNumber] = {
                    checkInHour,
                    checkInMinute
                };

                cout << "Vehicle parked in spot "
                     << assignedSpot << ".\n";
                return true;
            }
        }
    }

    cout << "No available parking spots.\n";
    return false;
}

bool ParkingLot::createCheckoutQuote(
    string& vehicleNumber,
    int checkoutHour,
    int checkoutMinute,
    CheckoutQuote& quote
) {
    if (checkoutHour < 0 || checkoutHour > 23 ||
        checkoutMinute < 0 || checkoutMinute > 59) {
        return false;
    }

    for (ParkingSpot& spot : spots) {
        Vehicle* vehicle = spot.getVehicle();

        if (vehicle != nullptr &&
            vehicle->getNumber() == vehicleNumber) {
            const auto checkIn = checkInTimes.find(vehicleNumber);

            if (checkIn == checkInTimes.end()) {
                return false;
            }

            int elapsedMinutes =
                checkoutHour * 60 + checkoutMinute -
                (checkIn->second.hour * 60 +
                 checkIn->second.minute);

            // Allows checkout after midnight.
            if (elapsedMinutes < 0) {
                elapsedMinutes += 24 * 60;
            }

            const int parkedHours = elapsedMinutes / 60;
            const int parkedMinutes = elapsedMinutes % 60;
            const double totalHours = elapsedMinutes / 60.0;
            const double hourlyRate = vehicle->getHourlyRate();

            quote.vehicleNumber = vehicleNumber;
            quote.spotNumber = spot.getSpotNumber();
            quote.parkedHours = parkedHours;
            quote.parkedMinutes = parkedMinutes;
            quote.checkInHour = checkIn->second.hour;
            quote.checkInMinute = checkIn->second.minute;
            quote.checkOutHour = checkoutHour;
            quote.checkOutMinute = checkoutMinute;
            quote.hourlyRate = hourlyRate;
            quote.totalAmount = hourlyRate * totalHours;

            return true;
        }
    }

    return false;
}

bool ParkingLot::completeCheckout(CheckoutQuote& quote) {
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
                quote.checkInHour,
                quote.checkInMinute,
                quote.checkOutHour,
                quote.checkOutMinute,
                quote.hourlyRate,
                quote.totalAmount,
                true
            });

            spot.clearVehicle(vehicle->getNumber());
            checkInTimes.erase(quote.vehicleNumber);

            cout << "Payment completed.\n"
                 << "Vehicle checked out from spot "
                 << quote.spotNumber << ".\n";
            return true;
        }
    }

    cout << "Checkout failed: vehicle was not found in that spot.\n";
    return false;
}

void ParkingLot::recordPaymentFailure(CheckoutQuote& quote) {
    paymentRecords.push_back({
        quote.vehicleNumber,
        quote.spotNumber,
        quote.parkedHours,
        quote.parkedMinutes,
        quote.checkInHour,
        quote.checkInMinute,
        quote.checkOutHour,
        quote.checkOutMinute,
        quote.hourlyRate,
        quote.totalAmount,
        false
    });

    cout << "Payment not completed. Vehicle remains parked.\n";
}

void ParkingLot::displayStatus() {
    cout << "\n--- Parking Lot Status ---\n";

    int availableSpots = 0;

    for (ParkingSpot& spot : spots) {
        Vehicle* vehicle = spot.getVehicle();

        if (vehicle == nullptr) {
            ++availableSpots;
            continue;
        }

        cout << "\n========================================\n"
             << "PARKED VEHICLE\n"
             << "Spot number: " << spot.getSpotNumber() << '\n'
             << "Status: Occupied\n";

        vehicle->displayDetails();

        cout << "========================================\n";
    }

    cout << "Available spots: " << availableSpots << '\n';
}

void ParkingLot::displayVehicleDetails(const string& vehicleNumber){
    for(ParkingSpot& spot: spots){
        Vehicle* vehicle = spot.getVehicle();

        if(vehicle != nullptr&& vehicle->getNumber()== vehicleNumber){
            const auto checkIn=checkInTimes.find(vehicleNumber);
            
            if(checkIn==checkInTimes.end()){
                cout<<"Check-in time is unavailable.\n";
                return;
            }
            
            cout << "\n========================================\n"
                 << "YOUR PARKING DETAILS\n"
                 << "Spot number: " << spot.getSpotNumber() << '\n'
                 << "Check-in time: "
                 << setfill('0') << setw(2) << checkIn->second.hour
                 << ':' << setw(2) << checkIn->second.minute
                 << setfill(' ') << '\n'
                 << "Vehicle details:\n";
            vehicle->displayDetails();

            cout << "========================================\n";
            return;
        }

    }
    cout << "No currently parked vehicle found with that number.\n";
}



void ParkingLot::displayPaymentHistory() {
    cout << "\n--- Checkout and Payment History ---\n";

    if (paymentRecords.empty()) {
        cout << "No checkout attempts recorded.\n";
        return;
    }

    for (ParkingRecord& record : paymentRecords) {
        cout << "\nVehicle: " << record.vehicleNumber
             << "\nSpot: " << record.spotNumber
             << "\nCheck-in time: "
             << setfill('0') << setw(2) << record.checkInHour
             << ':' << setw(2) << record.checkInMinute
             << "\nCheck-out time: "
             << setw(2) << record.checkOutHour
             << ':' << setw(2) << record.checkOutMinute
             << setfill(' ')
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