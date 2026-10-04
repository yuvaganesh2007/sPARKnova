#include "../include/Vehicle.h"

void Vehicle::inputDetails() {
    cout<<"Enter vehicle number: ";
    cin>>number;
}

string Vehicle::getNumber() { return number; }
void Car::inputDetails() {
    Vehicle::inputDetails();

    cout<<"Enter number of seats: ";
    cin>>seats;
}

void Car::displayDetails() {
    cout<<"\n---Car Details---\n";
    cout<<"Car Number: "<<number<<'\n';
    cout<<"Number of seats: "<<seats<<'\n';
}

void Bike::inputDetails() {
    Vehicle::inputDetails();
    cout<<"Enter bike type: ";
    cin>>type;
}

void Bike::displayDetails() {
    cout<<"\n---Bike Deatils---\n";
    cout<<"Bike Number: "<<number<<'\n';
    cout<<"Bike type: "<<type<<'\n';
}

void setDetails(Vehicle* v) { v->inputDetails(); }
void getDetails(Vehicle* v) { v->displayDetails(); }