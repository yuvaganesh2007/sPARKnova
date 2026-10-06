#include "../include/Vehicle.h"

void Vehicle::inputDetails() {
    cout<<"Enter vehicle number: ";
    cin>>number;
}

string Vehicle::getNumber() { return number; }
void Car::inputDetails() {
    Vehicle::inputDetails();
    bool flag=true;
    //exception handling in car type input
    do {
        try{
            cout<<"Enter number of seats: ";
            cin>>seats;
            if(seats!=5&&seats!=7) throw 0;
            flag=false;
        }
        catch(...) {
            cout<<"Invalid car type, Please Try Again\n";
        }
    }while(flag);
}

void Car::displayDetails() {
    cout<<"\n---Car Details---\n";
    cout<<"Car Number: "<<number<<'\n';
    cout<<"Number of seats: "<<seats<<'\n';
}

double Car::getHourlyRate() {
    if(seats==5) return 100.0;
    else return 120.0;
    return 0.0;
}

void Bike::inputDetails() {
    Vehicle::inputDetails();
    bool flag=true;
    //exception handling in bike type input
    do {
        try{
            cout<<"Enter bike type (Scooty or Gear): ";
            cin>>type;
            if(type!="Scooty"&&type!="scooty"&&
            type!="Gear"&&type!="gear") throw 0;
            flag=false;
        }
        catch(...) {
            cout<<"Invalid bike type, Please Try Again\n";
        }
    }while(flag);
}

void Bike::displayDetails() {
    cout<<"\n---Bike Deatils---\n";
    cout<<"Bike Number: "<<number<<'\n';
    cout<<"Bike type: "<<type<<'\n';
}

double Bike::getHourlyRate() {
    if(type=="Scooty"||type=="scooty") return 50.0;
    else if(type=="Gear"||type=="gear") return 70.0;
    return 0.0;
}

void setDetails(Vehicle* v) { v->inputDetails(); }
void getDetails(Vehicle* v) { v->displayDetails(); }