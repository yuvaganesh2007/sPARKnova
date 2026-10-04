#include "../include/Vehicle.h"
#include<bits/stdc++.h>
using namespace std;

int main() {
    Car c;
    Bike b;
    Vehicle* ptr;
    ptr=&c;
    setDetails(ptr);
    ptr=&b;
    setDetails(ptr);
    getDetails(ptr);
    ptr=&c;
    getDetails(ptr);
}