#include <iostream>
#include "../include/Action.h"
#include <typeinfo>
#include <vector>
#include <algorithm>
using std:: string;

//BaseAction

BaseAction::BaseAction():errorMsg(""),status(ActionStatus::ERROR){}

ActionStatus BaseAction::getStatus() const{
    return status;
}

void BaseAction::complete(){
    status = ActionStatus::COMPLETED;
}

void BaseAction::error(string errorMsg1){
    errorMsg = errorMsg1;
    status = ActionStatus::ERROR;

}

string BaseAction::getErrorMsg() const{
    return "Error:" + errorMsg;
}

//finished BaseAction------------------------------------------------------------------
//SimulateStep

SimulateStep::SimulateStep(int numOfSteps1):BaseAction(),numOfSteps(numOfSteps1){}

 void SimulateStep::act(WareHouse &wareHouse){
    for(int i=0; i<numOfSteps; i++){
        actOneStep(wareHouse);
    }
    complete();
}


void SimulateStep::actOneStep(WareHouse &wareHouse){
    step1(wareHouse);
    step2(wareHouse);

    

    }

void SimulateStep::step1(WareHouse &wareHouse){
    vector<Order*> & pendingOrders = wareHouse.getPendingOrders();

    for (auto it = pendingOrders.begin(); it != pendingOrders.end();) {
        if ((*it)->getStatus() == OrderStatus::PENDING) {
              if(orderToCollectorVolunteer(wareHouse, *it)){
                --it;
              }
              

        } else {
            if(orderToDriverVolunteer(wareHouse, *it)){
                --it;
            } 
            
        }

        ++it;
    }
} 




bool SimulateStep::orderToCollectorVolunteer(WareHouse &wareHouse, Order* order){
    vector<Volunteer*> & volunteers= wareHouse.getVolunteers();
    vector<Order*> & pendingOrders = wareHouse.getPendingOrders();
    vector<Order*> & inProcessOrders = wareHouse.getInProcessOrders();

    for (Volunteer* vol : volunteers) {
        if((typeid(*vol) == typeid(CollectorVolunteer) ||  typeid(*vol) == typeid(LimitedCollectorVolunteer)) && vol->canTakeOrder(*order)){
                static_cast<CollectorVolunteer*>(vol)->acceptOrder(*order);
                order->setStatus(OrderStatus::COLLECTING);
                order->setCollectorId(vol->getId());
                inProcessOrders.push_back(order);
                int i = wareHouse.getIndexInPendingOrder(order->getId());
                pendingOrders.erase(pendingOrders.begin() + i);
                return true;
                
            }

        }

        return false;

    }




bool SimulateStep::orderToDriverVolunteer(WareHouse &wareHouse, Order* order){
    vector<Volunteer*> & volunteers= wareHouse.getVolunteers();
    vector<Order*> & pendingOrders = wareHouse.getPendingOrders();
    vector<Order*> & inProcessOrders = wareHouse.getInProcessOrders();

    for (Volunteer* vol : volunteers){
            
        if((typeid(*vol) == typeid(DriverVolunteer) ||  typeid(*vol) == typeid(LimitedDriverVolunteer)) && vol->canTakeOrder(*order)){
            dynamic_cast<DriverVolunteer*>(vol)->acceptOrder(*order);
            order->setStatus(OrderStatus::DELIVERING);
            order->setDriverId(vol->getId());
            inProcessOrders.push_back(order);
            int i = wareHouse.getIndexInPendingOrder(order->getId());
            pendingOrders.erase(pendingOrders.begin() + i);

            return true;
                
        }

    }

    return false;
            
}

void SimulateStep::step2(WareHouse &wareHouse){
    vector<Volunteer*> & volunteers= wareHouse.getVolunteers();
    for (Volunteer* vol : volunteers){
        if(vol->isBusy()){
            vol->step();
            if((typeid(*vol) == typeid(CollectorVolunteer) ||  typeid(*vol) == typeid(LimitedCollectorVolunteer))){
                checkCollectorInProcess(wareHouse, vol);
            }
            else if( (typeid(*vol) == typeid(DriverVolunteer) ||  typeid(*vol) == typeid(LimitedDriverVolunteer))){
                checkDriverInProcess(wareHouse, vol);
            }
            

        }
    }

}



void SimulateStep::checkCollectorInProcess(WareHouse &wareHouse, Volunteer* collector){
    vector<Order*> & pendingOrders = wareHouse.getPendingOrders();
    vector<Order*> & inProcessOrders = wareHouse.getInProcessOrders();
    vector<Volunteer*> & volunteers = wareHouse.getVolunteers();
    if(dynamic_cast<CollectorVolunteer*>(collector)->getTimeLeft()==0){
                int orderId = collector->getCompletedOrderId();
                Order* order = &(wareHouse.getOrder(orderId));
                //order->setCollectorId(NO_VOLUNTEER);
                pendingOrders.push_back(order);
                int inProIndex = wareHouse.getIndexInProcessOrder(orderId);
                inProcessOrders.erase(inProcessOrders.begin() + inProIndex);
                if(dynamic_cast<LimitedCollectorVolunteer*>(collector)){
                    if(dynamic_cast<LimitedCollectorVolunteer*>(collector)->getNumOrdersLeft()==0) {
                    volunteers.erase(remove(volunteers.begin(), volunteers.end(),collector),volunteers.end());
                    delete collector;
            
                }
            }

    }
}
void SimulateStep::checkDriverInProcess(WareHouse &wareHouse, Volunteer* driver){
    vector<Order*> & inProcessOrders = wareHouse.getInProcessOrders();
    vector<Order*> & completedOrders = wareHouse.getCompletedOrders();
    vector<Volunteer*> & volunteers = wareHouse.getVolunteers();
    if(static_cast<DriverVolunteer*>(driver)->getDistanceLeft()==0){
        int orderId = driver->getCompletedOrderId();
        Order* order = &(wareHouse.getOrder(orderId));
        order->setStatus(OrderStatus::COMPLETED);
        //order->setDriverId(NO_VOLUNTEER);
        completedOrders.push_back(order);
        int inProIndex = wareHouse.getIndexInProcessOrder(orderId);
        inProcessOrders.erase(inProcessOrders.begin() + inProIndex);
        
        if(dynamic_cast<LimitedDriverVolunteer*>(driver)) {
         if(dynamic_cast<LimitedDriverVolunteer*>(driver)->getNumOrdersLeft()==0){
            volunteers.erase(remove(volunteers.begin(), volunteers.end(),driver),volunteers.end());
            delete driver;
            
        }
        }
    }
}



std::string SimulateStep::toString() const{
    return ("simulateStep " + std::to_string(numOfSteps));

}

SimulateStep* SimulateStep::clone() const{
    return new SimulateStep(*this);
}


//finished SimulateStep-----------


//finished SimulateStep------------------------------------------------------------------
//AddOrder

AddOrder:: AddOrder(int id):BaseAction(),customerId(id){
      
}


void AddOrder::act(WareHouse &wareHouse){

    if(wareHouse.customerExist(customerId)){
        auto customer = &(wareHouse.getCustomer(customerId));

        if( !(*customer).canMakeOrder()){
            error("Cannot place this order");
            cout<< getErrorMsg() << endl;
        }

        else{
        Order* order = new Order (wareHouse.getOrderCounter(), customerId,(*customer).getCustomerDistance());
        (*order).setStatus(OrderStatus::PENDING);
        wareHouse.addOrder(order);
        (*customer).addOrder((*order).getId());
        complete();

    }

    }

    else{
        error("Cannot place this order");
        cout<< getErrorMsg() << endl;
    }

}


AddOrder* AddOrder::clone() const{
        return new AddOrder(*this);
}

string AddOrder::toString() const{
    return (" Order " + std::to_string(customerId));
}

 //finished AddOrder--------------------------------------------------------------------
 //AddCustomer

AddCustomer::AddCustomer(const string &customerName1, const string &customerType1, int distance1, int maxOrders1):BaseAction(),customerName(customerName1),customerType((customerType1=="soldier") ? CustomerType::Soldier:CustomerType::Civilian),distance(distance1),maxOrders(maxOrders1){
  
}

void AddCustomer::act(WareHouse &wareHouse){
    int id = wareHouse.getCustomerCounter();
    if (customerType==CustomerType::Soldier){
        SoldierCustomer* soldier = new  SoldierCustomer(id, customerName, distance, maxOrders);
        wareHouse.addCustomer(soldier);
   }

   else{
        CivilianCustomer* civilian = new CivilianCustomer(id, customerName, distance, maxOrders);
        wareHouse.addCustomer(civilian);
   }

   complete();

}

AddCustomer* AddCustomer::clone() const{
    return new AddCustomer(*this);
}

string AddCustomer::toString() const{
    return (" customer " + customerName + " "  + customerTypeToString(customerType) + " " + std::to_string(distance) +" " +  std::to_string(maxOrders));
}

string AddCustomer::customerTypeToString(CustomerType customerType)const{
    if(customerType == CustomerType::Soldier){
        return "soldier";
    }

    else{
        return "civilian";
    }

}

//finished AddCustomer--------------------------------------------------------------------
//PrintOrderStatus

PrintOrderStatus::PrintOrderStatus(int id):BaseAction(), orderId(id){

}

void PrintOrderStatus::act(WareHouse &wareHouse){
    
    if (!(wareHouse.orderExist(orderId))){
        error("order does not exist");
        cout<< getErrorMsg() << endl;
    }
    else{
        string output = wareHouse.getOrder(orderId).toString();   
        cout << output << endl;
        complete();
    }

}

PrintOrderStatus* PrintOrderStatus:: clone() const{
    return new PrintOrderStatus(*this);
}

string PrintOrderStatus::toString() const{
    return ("orderStatus " + std::to_string(orderId));
}
//finished PrintOrderStatus--------------------------------------------------------------------
//PrintCustomerStatus

PrintCustomerStatus::PrintCustomerStatus(int customerId1):BaseAction(),customerId(customerId1){
    
}

void PrintCustomerStatus::act(WareHouse &wareHouse){

    if(!(wareHouse.customerExist(customerId))){
         error("Customer doesn't exist");
         cout<< getErrorMsg() << endl;
    }
    else{
        auto customer = &(wareHouse.getCustomer(customerId));
        string output = "--------------------- \nCustomerId: " + std::to_string(customerId);
        auto ordersIds = (*customer).getOrdersIds();
        for(int id:ordersIds){
            Order order = wareHouse.getOrder(id);
            string status = order.orderStatusToString(order.getStatus());
            output = output +"\nOrderId: " + std::to_string(id) +
            "\nOrderStatus: " + status;

        }

        output = output + "\n numOrdersLeft: " + std::to_string((*customer).getOrdersLeft()) + + "\n--------------------- ";
        cout << output << endl;
        complete();
    }

        

    }

PrintCustomerStatus* PrintCustomerStatus::clone() const{
    return new PrintCustomerStatus(*this);
}

string PrintCustomerStatus::toString() const{
    return ("customerStatus " + std::to_string(customerId));
}

//finished PrintCustomerStatus--------------------------------------------------------------------
//PrintVolunteerStatus

PrintVolunteerStatus::PrintVolunteerStatus(int id):BaseAction(), volunteerId(id){
}

void PrintVolunteerStatus::act(WareHouse &wareHouse){
    auto vol = &(wareHouse.getVolunteer(volunteerId));
    if((*vol).getId()==-1){
        error("volunteer does not exist");
        cout<< getErrorMsg() << endl;
    }
    else{
         cout << (*vol).toString() << endl;
         complete();
    }

}

PrintVolunteerStatus* PrintVolunteerStatus::clone() const{
    return new PrintVolunteerStatus(*this);
}

string PrintVolunteerStatus::toString() const{
    return ("volunteerStatus " +  std::to_string(volunteerId));
}

//finished PrintVolunteerStatus--------------------------------------------------------------------
//PrintActionsLog

PrintActionsLog::PrintActionsLog():BaseAction(){}

void PrintActionsLog::act(WareHouse &wareHouse){
    auto actionsLog = wareHouse.getActions();
    string output = "";
    for(auto action:actionsLog){
        output = output + "\n" + 
        action->toString() + " " + PrintActionsLog::actionStatusToString(action->getStatus());
    }

    cout << output << endl;
    complete();

}

std::string PrintActionsLog::actionStatusToString(ActionStatus status)const {
    switch (status) {
        case ActionStatus::COMPLETED:
            return "COMPLETED";
        case ActionStatus::ERROR:
            return "ERROR";
        default:
            return "UNDEFINED";
    }
}

PrintActionsLog* PrintActionsLog::clone() const{
    return new PrintActionsLog(*this);
}

string PrintActionsLog::toString() const{
    return "log ";
}

//finished PrintActionsLog--------------------------------------------------------------------
//Close

Close::Close():BaseAction(){}

void Close::act(WareHouse &wareHouse){
    for (Order* penOrder : wareHouse.getPendingOrders()){
         cout << penOrder->closeToString() << endl;
    }
    for (Order* ProOrder : wareHouse.getInProcessOrders()){
         cout << ProOrder->closeToString() << endl;
    }
    for (Order* compOrder : wareHouse.getCompletedOrders()){
         cout << compOrder->closeToString() << endl;
    }

    wareHouse.close();
    complete();

}

Close* Close::clone() const{
    return new Close(*this);
}

string Close::toString() const{
    return "";
}

//finished Close--------------------------------------------------------------------
//BackupWareHouse

BackupWareHouse::BackupWareHouse():BaseAction(){}

void BackupWareHouse::act(WareHouse &wareHouse){
    if(backup==nullptr){
        backup = new WareHouse(wareHouse);
    }

    else{
        *backup = wareHouse;
    }

    complete();
}

 BackupWareHouse* BackupWareHouse::clone() const{
    return new BackupWareHouse(*this);
 }

 string BackupWareHouse::toString() const{
    return "backup ";
 }

//finished BackupWareHouse--------------------------------------------------------------------
//RestoreWareHouse

RestoreWareHouse::RestoreWareHouse():BaseAction(){}

void RestoreWareHouse::act(WareHouse &wareHouse){
    if(backup==nullptr){
        error("No backup available");
        cout<< getErrorMsg() << endl;
    }

    else{
         wareHouse = *backup;
         complete();
    }

}

 RestoreWareHouse* RestoreWareHouse::clone() const{
    return new RestoreWareHouse(*this);
 }

 string RestoreWareHouse::toString() const{
     return "restore ";
 }
//finished RestoreWareHouse--------------------------------------------------------------------