#include <iostream>
#include "../include/Volunteer.h"

 LimitedCollectorVolunteer::LimitedCollectorVolunteer(int id1, const string &name1, int coolDown1 ,int maxOrders1):CollectorVolunteer(id1, name1, coolDown1),maxOrders(maxOrders1),ordersLeft(maxOrders){

 }

 LimitedCollectorVolunteer* LimitedCollectorVolunteer::clone() const{//we deleted "override"
    return new LimitedCollectorVolunteer(*this);

 }

 bool  LimitedCollectorVolunteer::hasOrdersLeft() const{//we dfeleted override
    if (ordersLeft>0){
        return true;
    }

    else{
        return false;
    }

 }

 bool LimitedCollectorVolunteer::canTakeOrder(const Order &order) const{
    
    if(!isBusy() && hasOrdersLeft()){
        return true;
    }

    else{
        return false;
    }
 }

void LimitedCollectorVolunteer::acceptOrder(const Order &order){
    if(canTakeOrder(order)){
        CollectorVolunteer::acceptOrder(order);
        decreaseOrdersLeft();
  
    }
    
    }

int LimitedCollectorVolunteer::getMaxOrders() const{
    return maxOrders;
}

int LimitedCollectorVolunteer::getNumOrdersLeft() const{
    return ordersLeft;
}

void LimitedCollectorVolunteer::decreaseOrdersLeft(){

    ordersLeft = ordersLeft - 1;
}

string LimitedCollectorVolunteer::toString() const{
    return ("VolunteerId: " + std::to_string(getId()) +
    "\nisBusy:" + ((isBusy()) ? "True":"False" ) +
    "\nOrderId:" + ((activeOrderId == NO_ORDER) ? "None":std::to_string(activeOrderId)) +
    "\nTimeLeft: " + std::to_string(getTimeLeft()) + 
    "\nOrdersLeft: " + std::to_string(ordersLeft));
 
}