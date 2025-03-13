#include <iostream>
#include "../include/Volunteer.h"

 CollectorVolunteer::CollectorVolunteer(int id1, const string &name1, int coolDown1):Volunteer(id1, name1),coolDown(coolDown1),timeLeft(0){

 }

 CollectorVolunteer* CollectorVolunteer::clone() const{
    return new CollectorVolunteer(*this);


 }


 void CollectorVolunteer::step(){
    if(decreaseCoolDown()){
       completedOrderId = activeOrderId;
       activeOrderId = NO_ORDER;
    }
     
 }

 int CollectorVolunteer::getCoolDown() const{
    return coolDown;
 }

 int CollectorVolunteer::getTimeLeft() const{
    return timeLeft;//check where to change timeLeft
 }

 bool CollectorVolunteer::decreaseCoolDown(){
    if(timeLeft>0){
        timeLeft=timeLeft-1;
    }
    
    if(timeLeft==0){
        return true;
    }

    else{
        return false;
    }

 }

 bool CollectorVolunteer::hasOrdersLeft() const {//we deleted override
    return true;
 }

 bool CollectorVolunteer::canTakeOrder(const Order &order) const {//we deleted override
    return (!isBusy()) ;
 }

 void CollectorVolunteer::acceptOrder(const Order &order) {//we deleted override
    activeOrderId = order.getId();
    timeLeft = coolDown;


 }


 string CollectorVolunteer::toString() const {//we deleted override
    return ("VolunteerId: " + std::to_string(getId()) +
    "\nisBusy:" + ((isBusy()) ? "True":"False" )+
    "\nOrderId:" + ((activeOrderId == NO_ORDER) ? "None":std::to_string(activeOrderId)) +
    "\nTimeLeft: " + ((timeLeft==0) ? "None" : std::to_string(timeLeft)) + 
    "\nOrdersLeft: No Limit");
 }