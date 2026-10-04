#ifndef VEHICLE_H
#define VEHICLE_H

#include<bits/stdc++.h>
using namespace std;

class Vehicle {
    protected:
        string number;
    public:
        virtual void inputDetails()=0;
        virtual void displayDetails()=0;
        string getNumber();
        
        friend void setDetails(Vehicle*);
        friend void getDetails(Vehicle*);
        virtual ~Vehicle() {}
};

class Car: public Vehicle {
    protected:
        int seats;

    public:
        void inputDetails() override;
        void displayDetails() override;

};

class Bike: public Vehicle {
    protected:
        string type;
    public:
        void inputDetails() override;
        void displayDetails() override;
};


#endif