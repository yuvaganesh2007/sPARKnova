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

    string input;
    int choice;

    while (true) {
        cout << "Enter a number: ";
        cin >> input; // Read as raw text

        try {
            // 1. Attempt to convert the string to an integer
            choice = stoi(input); 
            
            cout << "You entered: " << choice << "\n";
            break; // Valid input, exit loop
            
        } catch (const invalid_argument& e) {
            // 2. Thrown if the string is not a number (e.g., "abc")
            cout << "Error: Please enter a number.\n";
            continue;
            
        } catch (const out_of_range& e) {
            // 3. Thrown if the number is too big for an int
            cout << "Error: Number is too large.\n";
            continue;
        }
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