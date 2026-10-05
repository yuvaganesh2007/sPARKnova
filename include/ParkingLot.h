#ifndef PARKING_LOT_H
#define PARKING_LOT_H

#include "ParkingSpot.h"
#include <bits/stdc++.h>
using namespace std;
struct CheckInTime {
    int hour;
    int minute;
};
struct CheckoutQuote {
    std::string vehicleNumber;
    int spotNumber;
    int parkedHours;
    int parkedMinutes;
    int checkInHour;
    int checkInMinute;
    int checkOutHour;
    int checkOutMinute;
    double hourlyRate;
    double totalAmount;
};

struct ParkingRecord {
    std::string vehicleNumber;
    int spotNumber;
    int parkedHours;
    int parkedMinutes;
    int checkInHour;
    int checkInMinute;
    int checkOutHour;
    int checkOutMinute;
    double hourlyRate;
    double amount;
    bool paymentCompleted;
};


class ParkingLot {
private:
    vector<ParkingSpot> spots;
    vector<ParkingRecord> paymentRecords;
    unordered_map<string, CheckInTime> checkInTimes;

public:
    explicit ParkingLot(int numberOfSpots);
    bool parkVehicle(std::unique_ptr<Vehicle> vehicle, int checkInHour, int checkInMinute);
     bool createCheckoutQuote(
        string& vehicleNumber,
        int checkoutHour,
        int checkoutMinute,
        CheckoutQuote& quote);

    bool completeCheckout(CheckoutQuote& quote);
    void recordPaymentFailure(CheckoutQuote& quote);

    void displayVehicleDetails(const string& vehicleNumber);
    void displayStatus();
    void displayPaymentHistory() ;
};

#endif