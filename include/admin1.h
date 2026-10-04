#ifndef ADMIN_H
#define ADMIN_H

#include "ParkingLot.h"
#include <bits/stdc++.h>
using namespace std;

class Admin {
private:
    string password;
    ParkingLot& parkingLot;

    bool login();

public:
    Admin(const string& password, ParkingLot& parkingLot);
    void start();
};

#endif