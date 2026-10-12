#include "../include/Admin.h"
#include <bits/stdc++.h>
#include<conio.h>

using namespace std;

Admin::Admin(const string& password, ParkingLot& parkingLot)
    : password(password), parkingLot(parkingLot) {}

string Admin::getMaskedPassword() {
    string password="";
    char ch;

    while ((ch = _getch()) != '\r') { 
        if (ch == '\b') { // Handle Backspace
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b"; // Erase the last asterisk from the screen
            }
        } 
        else {
            password.push_back(ch);
            cout << '*'; // Print asterisk instead of the actual character
        }
    }
    cout << endl;
    return password;
}

bool Admin::login() {
    string enteredPassword;

    cout << "Enter admin password: ";
    enteredPassword=getMaskedPassword();
    
    //exception handling password
    try {
        if(enteredPassword!=password) throw false;
        cout << "Login successful.\n";
        return true;
    }
    catch( bool e) {
        cout << "Incorrect password.\n";
        return false;
    }
    
}

void Admin::checkInVehicle() {
    int vehicleChoice;
    int checkInHour, checkInMinute;

    cout << "\n1. Car\n"
         << "2. Bike\n"
         << "Choose vehicle type: ";
    //exception handling
    try {
        if (!(cin >> vehicleChoice)) throw 0;
    }
    
    catch(...) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    unique_ptr<Vehicle> vehicle;
    //exception handling vehicle choice
    try{
        if (vehicleChoice == 1) {
            vehicle = make_unique<Car>();
        } 
        else if (vehicleChoice == 2) {
            vehicle = make_unique<Bike>();
        }

        else throw 0;
    }

    catch(...) {
        cout << "Invalid vehicle type.\n";
        return;
    }

    vehicle->inputDetails();
    
    //exception handling time input
    try{
        cout << "Enter check-in time (24-hour format, HH MM): ";
        cin >> checkInHour >> checkInMinute;
        if (checkInHour < 0 || checkInHour > 23 || checkInMinute < 0 || checkInMinute > 59) throw 0;
    }
    catch(...) {
        cout << "Invalid time. Enter hours 0-23 and minutes 0-59.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    parkingLot.parkVehicle(move(vehicle), checkInHour, checkInMinute);
}

void Admin::checkOutVehicle() {
    string vehicleNumber;
    int checkoutHour;
    int checkoutMinute;

    cout << "Enter vehicle number: ";
    cin >> vehicleNumber;
    //exception handling checkout time
    try {
        cout << "Enter checkout time (24-hour format, HH MM): ";
        cin >> checkoutHour >> checkoutMinute;
        if (checkoutHour < 0 || checkoutHour > 23 ||
        checkoutMinute < 0 || checkoutMinute > 59) throw 0;
    }
    catch(...) {
        cout << "Invalid time. Enter hours 0-23 and minutes 0-59.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    CheckoutQuote quote;
    //exception handling vehicle not found
    try{
        if (!parkingLot.createCheckoutQuote(vehicleNumber, checkoutHour, checkoutMinute, quote)) 
            throw 0;
    }
    catch(...) {
        cout << "Vehicle not found, or parking time is unavailable.\n";
        return;
    }

    cout << fixed << setprecision(2);
    cout << "\n--- Checkout Bill ---\n"
         << "Vehicle: " << quote.vehicleNumber << '\n'
         << "Spot: " << quote.spotNumber << '\n'
         << "Check-in time: " << setfill('0') << setw(2) << quote.checkInHour
         << ':' << setw(2) << quote.checkInMinute << setfill(' ') << '\n'
         << "Check-out time: " << setfill('0') << setw(2) << quote.checkOutHour
         << ':' << setw(2) << quote.checkOutMinute << setfill(' ') << '\n'
         << "Rate per hour: Rs. " << quote.hourlyRate << '\n'
         << "Total amount: Rs. " << quote.totalAmount << '\n';

    int paymentChoice = 0;

    do {
        cout << "\nPayment completed?\n"
             << "1. Yes - complete checkout\n"
             << "2. No - payment not completed\n"
             << "Choose: ";

        try {
            if (!(cin >> paymentChoice)) throw 0;
        }
        catch(...) {
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
             
        try {
            if (!(cin >> choice)) throw 0;
        }
        catch(...) {
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