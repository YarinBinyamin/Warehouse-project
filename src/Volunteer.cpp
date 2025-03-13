#include <iostream>
#include "../include/Volunteer.h"

Volunteer::Volunteer(int id1, const string &name1):completedOrderId(NO_ORDER),activeOrderId(NO_ORDER), id(id1),name(name1){

    }

int Volunteer::getId() const{
    return id;

}

const string& Volunteer:: getName() const{
    return name;
}

int Volunteer:: getActiveOrderId() const{
    return activeOrderId;
}

int Volunteer::getCompletedOrderId() const{
    return completedOrderId;
}

bool Volunteer::isBusy() const{
    if(activeOrderId!=NO_ORDER){
        return true;
    }

    else{
        return false;
    }

}















