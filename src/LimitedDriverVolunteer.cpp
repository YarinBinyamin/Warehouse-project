#include <iostream>
#include "../include/Volunteer.h"

LimitedDriverVolunteer::LimitedDriverVolunteer(int id1, const string &name1, int maxDistance1, int distancePerStep1,int maxOrders1):DriverVolunteer(id1, name1, maxDistance1, distancePerStep1),maxOrders(maxOrders1),ordersLeft(maxOrders){
   
}

LimitedDriverVolunteer* LimitedDriverVolunteer::clone() const{
    return new LimitedDriverVolunteer(*this);
}

int LimitedDriverVolunteer::getMaxOrders() const{
    return maxOrders;
}

 int  LimitedDriverVolunteer::getNumOrdersLeft() const{
    return ordersLeft;
 }

bool LimitedDriverVolunteer::hasOrdersLeft() const{
    return (ordersLeft>0);
}

bool LimitedDriverVolunteer::canTakeOrder(const Order &order) const{ //do we need to consider hasOrdersLeft?
    return (!isBusy() && order.getDistance()<=getMaxDistance() && hasOrdersLeft());
}

void LimitedDriverVolunteer::acceptOrder(const Order &order){
    DriverVolunteer::acceptOrder(order);
    decreaseOrdersLeft();
}

void LimitedDriverVolunteer::decreaseOrdersLeft(){

    ordersLeft = ordersLeft - 1;
}

string LimitedDriverVolunteer::toString() const{
      return ("VolunteerId: " + std::to_string(getId()) +
    "\nisBusy:" + ((isBusy()) ? "True":"False" ) +
    "\nOrderId:" + ((activeOrderId == NO_ORDER) ? "None":std::to_string(activeOrderId)) +
    "\nDistanceLeft: " + std::to_string(getDistanceLeft()) + 
    "\nOrdersLeft: " +  std::to_string(ordersLeft));
}