#ifndef PARKING_LOT_H
#define PARKING_LOT_H

#include "ParkingSpot.h"
#include <bits/stdc++.h>
using namespace std;
struct CheckoutQuote {
    std::string vehicleNumber;
    int spotNumber;
    int parkedHours;
    int parkedMinutes;
    double hourlyRate;
    double totalAmount;
};

struct ParkingRecord {
    std::string vehicleNumber;
    int spotNumber;
    int parkedHours;
    int parkedMinutes;
    double hourlyRate;
    double amount;
    bool paymentCompleted;
};


class ParkingLot {
private:
    vector<ParkingSpot> spots;
    vector<ParkingRecord> paymentRecords;

public:
    explicit ParkingLot(int numberOfSpots);
    bool parkVehicle(std::unique_ptr<Vehicle> vehicle);
     bool createCheckoutQuote(
        string& vehicleNumber,
        int parkedHours,
        int parkedMinutes,
        CheckoutQuote& quote);

    bool completeCheckout(CheckoutQuote& quote);
    void recordPaymentFailure(CheckoutQuote& quote);

    void displayStatus();
    void displayPaymentHistory() ;
};

#endif