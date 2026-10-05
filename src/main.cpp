#include "../include/admin.h"
#include "../include/user.h"
#include<iostream>
#include<limits>

using namespace std;

int main() {
    ParkingLot parkingLot(10);
    Admin admin("admin123", parkingLot);
    User user(parkingLot);

    int choice=0;
    do{
        cout<<"\n--- sPARKnova---\n"
        <<"1. Admin\n"
        <<"2. User - view parking details\n"
        <<"3. Exit\n"
        << "Choose an option: ";

        if(!(cin>>choice)){
            cout<<"Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
        }

        switch(choice){
            case 1:
            admin.start();
            break;
            case 2:
            user.start();
            break;
            case 3:
            cout<<"Goodbye.\n";
            break;
            default:
            cout<<"Invalid option."<<endl;
        }
    }while(choice!=3);

    return 0;
}