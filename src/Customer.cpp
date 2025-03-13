#include <iostream>
#include "../include/Customer.h"

Customer::Customer(int id1, const string &name1, int locationDistance1, int maxOrders1): id(id1), name(name1),
        locationDistance(locationDistance1), maxOrders(maxOrders1),ordersLeft(maxOrders), ordersId(vector<int>()){
    
}

const string& Customer::getName() const{
    return name;   
}

int Customer::getId() const{
    return id;
}

int Customer::getCustomerDistance() const{
    return locationDistance;
}

int Customer::getMaxOrders() const{
    return maxOrders;
} 

int Customer::getNumOrders() const{
    return ordersId.size();
} 

 int Customer::getOrdersLeft() const{
    return ordersLeft;
 }

bool Customer::canMakeOrder() const{
    return (ordersLeft > 0);
} 

const vector<int> & Customer::getOrdersIds() const{
    return ordersId;

}

int Customer::addOrder(int orderId){
    if (canMakeOrder()){
        ordersId.push_back(orderId);
        ordersLeft = ordersLeft -1;
        return orderId;
    }
    return -1;



} 





