#include "../include/admin.h"

int main() {
    ParkingLot parkingLot(10);
    Admin admin("admin123", parkingLot);

    admin.start();

    return 0;
}