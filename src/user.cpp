#include "../include/user.h"
#include <iostream>
#include<limits>

using namespace std;

User::User(ParkingLot& parkingLot): parkingLot(parkingLot){}

    void User::start(){
        string vehicleNumber;

        cout<<endl<<"--- view Your Parking Details ---\n"<<"Enter your vehicle number: ";

        if(!(cin>> vehicleNumber)){
            cout<<"Invalid input. \n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            return;
        }

        parkingLot.displayVehicleDetails(vehicleNumber);
    }

