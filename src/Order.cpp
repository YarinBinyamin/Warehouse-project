#include <iostream>
#include "../include/Order.h"

Order::Order(int id1, int customerId1, int distance1):id(id1), customerId(customerId1), distance(distance1),status(OrderStatus::PENDING),collectorId(NO_VOLUNTEER),driverId(NO_VOLUNTEER){
    
}

int Order::getId() const{
    return id;
}

int Order::getCustomerId() const{
    return customerId;
}

void Order::setStatus(OrderStatus status1){
    status = status1;
}

 void Order::setCollectorId(int collectorId1){
    collectorId = collectorId1;
 }

void Order::setDriverId(int driverId1){
    driverId = driverId1;
}

int Order::getCollectorId() const{
    return collectorId;
}

int Order::getDriverId() const{
    return driverId;

}

OrderStatus Order::getStatus() const{
    return status;
}

std::string Order::orderStatusToString(OrderStatus status)const {
    switch (status) {
        case OrderStatus::PENDING:
            return "PENDING";
        case OrderStatus::COLLECTING:
            return "COLLECTING";
        case OrderStatus::DELIVERING:
            return "DELIVERING";
        case OrderStatus::COMPLETED:
            return "COMPLETED";
        default:
            return "UNDEFINED";
    }
}

 const string Order::toString() const{
    return (
        "OrderId: " + std::to_string(id) +
        "\nOrderStatus: " + orderStatusToString(status) +
        "\nCustomerId: " + std::to_string(customerId) +
        "\nCollector: " + ((collectorId == NO_VOLUNTEER) ? "None":std::to_string(collectorId)) +
        "\nDriver: " + ((driverId == NO_VOLUNTEER) ? "None":std::to_string(driverId)) +
        "\n---------------------");
 }

 const string Order::closeToString() const{
     return (
        "OrderId: " + std::to_string(id) + " ,CustomerId: " + std::to_string(customerId) +
        " ,OrderStatus: " + orderStatusToString(status));

 }


int Order::getDistance() const{
    return distance;
}


 Order* Order::clone() const{
    return new Order(*this);
 }



