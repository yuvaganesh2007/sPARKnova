#include<bits/stdc++.h>
using namespace std;

const int MAX=100;
int users=0;

class Vehicle {
    protected:
        string number;
    
    public:
        string select_type() {
            cout<<"Select the type of vehicle:\n";
            cout<<"1. Car\n2. Bike\n";
        }
    
};

class car: public Vehicle {

};

class bike: public Vehicle  {

};

class User{ 
    protected:
        string name,mobile_no;
        Vehicle vehicle;
    
};

User arr[MAX];

int main() {
    cout<<"Welcome to sPARKnova \n";
    cout<<"Who's trying to use:\n";
    cout<<"1. User\n2. Admin\n";
    int choice;
    cin>>choice;
    bool flag=true;
    while(flag) {
        switch(choice) {
            case 1:
                
                cout<<"Welcome, ";
            case 2:
                cout<<"Welcome, Admin\n";

            default:
                cout<<"Invalid input, Please try again\n";
        }
    }
}