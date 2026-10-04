#include "../include/admin.h"
#include <bits/stdc++.h>

using namespace std;

Admin::Admin(const string& password, ParkingLot& parkingLot)
    : password(password), parkingLot(parkingLot) {}

bool Admin::login() {
    string enteredPassword;

    cout << "Enter admin password: ";
    std:cin >> enteredPassword;

    if (enteredPassword != password) {
        cout << "Incorrect password.\n";
        return false;
    }

    cout << "Login successful.\n";
    return true;
}

void Admin::start() {
    if (!login()) {
        return;
    }

    int choice = 0;

    do {
        cout << "\n--- Admin Menu ---\n"
            << "1. Park a car\n"
            << "2. Park a bike\n"
            << "3. Remove a vehicle\n"
            << "4. View parking status\n"
            << "5. Exit\n"
            << "Choose an option: ";

        if (!(cin >> choice)) {
            cout << "Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1) {
            auto car = make_unique<Car>();
            car->inputDetails();
            parkingLot.parkVehicle(move(car));
        } 
        else if (choice == 2) {
            auto bike = make_unique<Bike>();
            bike->inputDetails();
            parkingLot.parkVehicle(move(bike));
        }
        else if (choice == 3) {
            string number;
            cout << "Enter vehicle number to remove: ";
            cin >> number;
            parkingLot.removeVehicle(number);
        } 
        else if (choice == 4) {
            parkingLot.displayStatus();
        } 
        else if (choice != 5) {
            cout << "Invalid option.\n";
        }

    } while (choice != 5);
}