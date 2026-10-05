#include "../include/Admin.h"
#include <bits/stdc++.h>

using namespace std;

Admin::Admin(const string& password, ParkingLot& parkingLot)
    : password(password), parkingLot(parkingLot) {}

bool Admin::login() {
    string enteredPassword;

    cout << "Enter admin password: ";
    cin >> enteredPassword;

    if (enteredPassword != password) {
        cout << "Incorrect password.\n";
        return false;
    }

    cout << "Login successful.\n";
    return true;
}

void Admin::checkInVehicle() {
    int vehicleChoice;

    cout << "\n1. Car\n"
         << "2. Bike\n"
         << "Choose vehicle type: ";

    if (!(cin >> vehicleChoice)) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    unique_ptr<Vehicle> vehicle;

    if (vehicleChoice == 1) {
        vehicle = make_unique<Car>();
    } else if (vehicleChoice == 2) {
        vehicle = make_unique<Bike>();
    } else {
        cout << "Invalid vehicle type.\n";
        return;
    }

    vehicle->inputDetails();
    parkingLot.parkVehicle(move(vehicle));
}

void Admin::checkOutVehicle() {
    string vehicleNumber;
    int parkedHours;
    int parkedMinutes;

    cout << "Enter vehicle number: ";
    cin >> vehicleNumber;

    cout << "Enter parked hours: ";
    if (!(cin >> parkedHours)) {
        cout << "Invalid hours.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "Enter additional parked minutes (0-59): ";
    if (!(cin >> parkedMinutes)) {
        cout << "Invalid minutes.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (parkedHours < 0 || parkedMinutes < 0 || parkedMinutes > 59) {
        cout << "Hours must be non-negative and minutes must be "
             << "between 0 and 59.\n";
        return;
    }

    CheckoutQuote quote;

    if (!parkingLot.createCheckoutQuote(
            vehicleNumber, parkedHours, parkedMinutes, quote)) {
        cout << "Vehicle not found, or parking duration is invalid.\n";
        return;
    }

    cout << fixed << setprecision(2);
    cout << "\n--- Checkout Bill ---\n"
         << "Vehicle: " << quote.vehicleNumber << '\n'
         << "Spot: " << quote.spotNumber << '\n'
         << "Parked duration: " << quote.parkedHours
         << " hour(s), " << quote.parkedMinutes << " minute(s)\n"
         << "Rate per hour: Rs. " << quote.hourlyRate << '\n'
         << "Total amount: Rs. " << quote.totalAmount << '\n';

    int paymentChoice = 0;

    do {
        cout << "\nPayment completed?\n"
             << "1. Yes - complete checkout\n"
             << "2. No - payment not completed\n"
             << "Choose: ";

        if (!(cin >> paymentChoice)) {
            cout << "Enter 1 or 2.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            paymentChoice = 0;
        }
    } while (paymentChoice != 1 && paymentChoice != 2);

    if (paymentChoice == 1) {
        parkingLot.completeCheckout(quote);
    } else {
        parkingLot.recordPaymentFailure(quote);
    }
}

void Admin::start() {
    if (!login()) {
        return;
    }

    int choice = 0;

    do {
        cout << "\n--- Admin Menu ---\n"
             << "1. Check in vehicle\n"
             << "2. Check out vehicle and collect payment\n"
             << "3. View parking status\n"
             << "4. View payment history\n"
             << "5. Exit\n"
             << "Choose an option: ";

        if (!(cin >> choice)) {
            cout << "Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                checkInVehicle();
                break;
            case 2:
                checkOutVehicle();
                break;
            case 3:
                parkingLot.displayStatus();
                break;
            case 4:
                parkingLot.displayPaymentHistory();
                break;
            case 5:
                cout << "Logging out.\n";
                break;
            default:
                cout << "Invalid option.\n";
        }
    } while (choice != 5);
}