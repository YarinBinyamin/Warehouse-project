#pragma once

#include <string>
#include <vector>
using std::string;
using std::vector;


class Volunteer;

enum class OrderStatus {
    PENDING,
    COLLECTING,
    DELIVERING,
    COMPLETED,
};

#define NO_VOLUNTEER -1

class Order {

    public:
        Order(int id, int customerId, int distance);
        virtual ~Order()=default;//we added it
        int getId() const;
        int getCustomerId() const;
        void setStatus(OrderStatus status);
        void setCollectorId(int collectorId1);
        void setDriverId(int driverId);
        int getCollectorId() const;
        int getDriverId() const;
        OrderStatus getStatus() const;
        std::string orderStatusToString(OrderStatus status)const;//we added it
        const string toString() const;
        const string closeToString() const;//we added it
        int getDistance() const; //we added it
        Order* clone() const;//we added it

    private:
        const int id;
        const int customerId;
        const int distance;
        OrderStatus status;
        int collectorId; //Initialized to NO_VOLUNTEER if no collector has been assigned yet
        int driverId; //Initialized to NO_VOLUNTEER if no driver has been assigned yet
};