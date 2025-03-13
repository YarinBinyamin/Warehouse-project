#include <iostream>
#include "../include/Volunteer.h"

DriverVolunteer::DriverVolunteer(int id1, const string &name1, int maxDistance1, int distancePerStep1):Volunteer(id1, name1),maxDistance(maxDistance1),distancePerStep(distancePerStep1),distanceLeft(0){
   
}

 DriverVolunteer* DriverVolunteer::clone() const{//we deleted override
    return new DriverVolunteer(*this);

 }

 int DriverVolunteer::getDistanceLeft() const{
    return distanceLeft;
 }

 int DriverVolunteer::getMaxDistance() const{
    return maxDistance;
 }

 int DriverVolunteer::getDistancePerStep() const{
    return distancePerStep;
 }

  bool DriverVolunteer::decreaseDistanceLeft(){//if distanceLeft=0 in first place?
    distanceLeft = distanceLeft - distancePerStep;

    if(distanceLeft<=0){
        distanceLeft=0;
        return true;
    }

    else{
        return false;
    }

  }

   bool DriverVolunteer::hasOrdersLeft() const{
    return true;
   }

   bool DriverVolunteer::canTakeOrder(const Order &order) const{
      return (!isBusy() && order.getDistance()<=maxDistance);
   }

   void DriverVolunteer::acceptOrder(const Order &order){
      activeOrderId = order.getId();
      distanceLeft = order.getDistance();
   }

   void  DriverVolunteer::step(){
      if(decreaseDistanceLeft()){
         completedOrderId = activeOrderId;
         activeOrderId = NO_ORDER;
      }
   }

   string DriverVolunteer::toString() const{
   return ("VolunteerId: " + std::to_string(getId()) +
    "\nisBusy:" + ((isBusy()) ? "True":"False" ) +
    "\nOrderId:" + ((activeOrderId == NO_ORDER) ? "None":std::to_string(activeOrderId)) +
    "\nDistanceLeft: " + std::to_string(distanceLeft) + 
    "\nOrdersLeft: No Limit");
   }