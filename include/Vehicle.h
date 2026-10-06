#ifndef VEHICLE_H
#define VEHICLE_H

#include<bits/stdc++.h>
using namespace std;

//Abstract Class Vehicle
class Vehicle {
    protected:
        string number;
    public:
        //pure virtual functions
        virtual void inputDetails()=0;
        virtual void displayDetails()=0;
        string getNumber();
        virtual double getHourlyRate()=0;
        
        //Function polymorphism using base class pointer
        friend void setDetails(Vehicle*);
        friend void getDetails(Vehicle*);
        virtual ~Vehicle() {}
};

//Derived Class Car
class Car: public Vehicle {
    protected:
        int seats;

    public:
        //Function Overriding
        void inputDetails() override;
        void displayDetails() override;
        double getHourlyRate() override;

};

//Derived Class Bike
class Bike: public Vehicle {
    protected:
        string type;
    public:
        //Function Overriding
        void inputDetails() override;
        void displayDetails() override;
        double getHourlyRate() override;
};


#endif