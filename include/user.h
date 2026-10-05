#ifndef USER_H
#define USER_H

#include "ParkingLot.h"
#include <string>

class User {
    private:
    ParkingLot& parkingLot;

    public:
        explicit User(ParkingLot& parkingLot);
        void start();
};

#endif
