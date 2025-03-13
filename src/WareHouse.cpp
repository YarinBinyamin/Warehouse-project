#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "../include/WareHouse.h"

// Split a string into a vector of substrings based on a delimiter
std::vector<std::string> WareHouse::split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream ss(s);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

void WareHouse::parseCustomer(const std::vector<std::string>& tokens) {
        std::string name = tokens[1];
        std::string customerType = tokens[2];
        int distance = std::stoi(tokens[3]);
        int maxOrders = std::stoi(tokens[4]);

        if(customerType =="soldier"){
            customers.push_back(new SoldierCustomer(customerCounter, name, distance, maxOrders));
        }

        else if (customerType =="civilian"){
            customers.push_back(new CivilianCustomer(customerCounter, name, distance, maxOrders));
        }

        customerCounter = customerCounter +1;
        //customers.emplace_back(name, customerType, distance, maxOrders);
    }

void WareHouse::parseVolunteer(const std::vector<std::string>& tokens) {
        std::string name = tokens[1];
        std::string role = tokens[2];
        int maxDistance, distancePerStep, maxOrders, coolDown;

        if (role == "driver") {
            maxDistance = std::stoi(tokens[3]);
            distancePerStep = std::stoi(tokens[4]);
            volunteers.push_back(new DriverVolunteer(volunteerCounter,name, maxDistance, distancePerStep));
        } else if(role == "limited_driver"){
            maxDistance = std::stoi(tokens[3]);
            distancePerStep = std::stoi(tokens[4]);
            maxOrders = std::stoi(tokens[5]);
            volunteers.push_back(new LimitedDriverVolunteer(volunteerCounter,name, maxDistance, distancePerStep, maxOrders));
         }else if(role == "collector"){
            coolDown = std::stoi(tokens[3]);
            volunteers.push_back(new CollectorVolunteer(volunteerCounter,name, coolDown));
         }
         else if(role == "limited_collector"){
            coolDown = std::stoi(tokens[3]);
            maxOrders = std::stoi(tokens[4]);
            volunteers.push_back(new LimitedCollectorVolunteer(volunteerCounter,name, coolDown, maxOrders));

         }

         volunteerCounter = volunteerCounter +1;

        //volunteers.emplace_back(name, role, coolDown, maxDistance, distancePerStep, maxOrders);
    }

WareHouse::WareHouse(const string &configFilePath):FictVol(vector<Volunteer*>()),FictOrder(vector<Order*>()),FictCust(vector<Customer*>()), isOpen(false),actionsLog(vector<BaseAction*>()), volunteers(vector<Volunteer*>()),pendingOrders(vector<Order*>()),inProcessOrders(vector<Order*>()),completedOrders(vector<Order*>()), customers(vector<Customer*>()) ,customerCounter(0), volunteerCounter(0), orderCounter(0){
     std::ifstream file(configFilePath);
     std::string line;
     FictVol.push_back(new CollectorVolunteer(-1, "none", -1));
     FictOrder.push_back(new Order(-1, -1, -1));
     FictCust.push_back(new CivilianCustomer(-1, "none", -1, -1));
     
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') {
                // Skip empty lines and comments
                continue;
            }

            std::vector<std::string> tokens = split(line, ' ');

            if (tokens[0] == "customer") {
                parseCustomer(tokens);
            } else if (tokens[0] == "volunteer") {
                parseVolunteer(tokens);
            } else {
                std::cerr << "Unknown type: " << tokens[0] << std::endl;
            }
        }

}

//rule of 5:
// copy constructor
WareHouse::WareHouse(const WareHouse &other):FictVol(),FictOrder(),FictCust(),isOpen(other.isOpen),actionsLog(),volunteers(),pendingOrders(),inProcessOrders(),completedOrders(),customers(),customerCounter(other.customerCounter),volunteerCounter(other.volunteerCounter),orderCounter(other.orderCounter){
   //////////
    for (Volunteer* fictvol : other.FictVol) {
        FictVol.push_back(fictvol->clone());
    }
    for (Order* fictOrder : other.FictOrder) {
        FictOrder.push_back(fictOrder->clone());
    }
    for (Customer* fictCust : other.FictCust) {
        FictCust.push_back(fictCust->clone());
    }
///////////////////////////////////////

    
    for (BaseAction* action : other.actionsLog) {
        actionsLog.push_back(action->clone());
    }

    for (Volunteer* vol : other.volunteers) {
        volunteers.push_back(vol->clone());
    }

    for (Order* penOrder : other.pendingOrders) {
        pendingOrders.push_back(penOrder->clone());
    }

    for (Order* inProOrder : other.inProcessOrders) {
        inProcessOrders.push_back(inProOrder->clone());
    }

    for (Order* compOrder : other.completedOrders) {
        completedOrders.push_back(compOrder->clone());
    }

    for (Customer* cust : other.customers) {
        customers.push_back(cust->clone());
    }


}

// move copy constructor //is the parameter sould be const?
WareHouse::WareHouse(WareHouse &&other):FictVol(),FictOrder(),FictCust(),isOpen(other.isOpen),actionsLog(),volunteers(),pendingOrders(),inProcessOrders(),completedOrders(),customers(),customerCounter(other.customerCounter),volunteerCounter(other.volunteerCounter),orderCounter(other.orderCounter){
     ////////////
     for (Volunteer* fictvol : other.FictVol) {
        FictVol.push_back(fictvol);
        fictvol = nullptr;
    }
    for (Order* fictOrder : other.FictOrder) {
        FictOrder.push_back(fictOrder);
        fictOrder = nullptr;
    }
    for (Customer* fictCust : other.FictCust) {
        FictCust.push_back(fictCust);
        fictCust = nullptr;
    }
     ////////////////////////////   

    for (BaseAction* action : other.actionsLog){
        actionsLog.push_back(action);
        action = nullptr;

    }

    for (Volunteer* vol : other.volunteers){
        volunteers.push_back(vol);
        vol = nullptr;

    }

    for (Order* penOrder : other.pendingOrders){
        pendingOrders.push_back(penOrder);
        penOrder = nullptr;

    }

    for (Order* inProOrder : other.inProcessOrders){
        inProcessOrders.push_back(inProOrder);
        inProOrder = nullptr;

    }

    for (Order* compOrder : other.completedOrders){
        completedOrders.push_back(compOrder);
        compOrder= nullptr;

    }

     for (Customer* cust : other.customers){
        customers.push_back(cust);
        cust=nullptr;
    }
    }

 //Destructor

WareHouse::~WareHouse(){
    ////////////
     for (Volunteer* fictvol :FictVol) {
        if(fictvol!=nullptr){
            delete fictvol;
            fictvol = nullptr;
        }
       
    }   
    FictVol.clear();

    for (Order* fictOrder : FictOrder) {
        if(fictOrder!=nullptr){
            delete fictOrder;
            fictOrder = nullptr;
        }
       
    }
    FictOrder.clear();

    for (Customer* fictCust : FictCust) {
        if(fictCust!= nullptr){
            delete fictCust;
            fictCust = nullptr;
        }
        
    }
    FictCust.clear();
     //////////////////////////// 

    for(BaseAction* act: actionsLog){
        if(act!=nullptr){
            delete act;
            act = nullptr;
        }
        
    }
    actionsLog.clear();

    for(Volunteer* vol: volunteers ){
        if(vol!=nullptr){
            delete vol;
            vol = nullptr;
        }
       
    }
    volunteers.clear();

    for(Order* penOrd: pendingOrders ){
        if(penOrd!=nullptr){
            delete penOrd;
            penOrd = nullptr;
        }
       
    }
    pendingOrders.clear();

    for(Order* inPOrd: inProcessOrders ){
        if(inPOrd!=nullptr){
            delete inPOrd;
            inPOrd = nullptr;
        }
       
    }
    inProcessOrders.clear();

    for(Order* comOrd: completedOrders ){
        if(comOrd!=nullptr){
            delete comOrd;
            comOrd = nullptr;
        }
        
    }
    completedOrders.clear();

    for(Customer* cust: customers ){
        if(cust!=nullptr){
            delete cust;
            cust = nullptr;
        }
        
    }
    customers.clear();

    }

//copy assignment operator

WareHouse& WareHouse::operator=(const WareHouse &other){
     if (this != &other) {
        isOpen = other.isOpen;
        customerCounter = other.customerCounter;
        volunteerCounter = other.volunteerCounter;
        orderCounter = other.orderCounter;

        // Clear existing data

        ///////////////
        for (Volunteer* fictvol :FictVol) {
            if(fictvol!=nullptr){
                delete fictvol;
                fictvol = nullptr;
            }

            
        }
        FictVol.clear();

        for (Order* fictOrder : FictOrder) {
            if(fictOrder!=nullptr){
                delete fictOrder;
                fictOrder = nullptr;
            }
            
        }
        FictOrder.clear();

        for (Customer* fictCust : FictCust) {
            if(fictCust!=nullptr){
                delete fictCust;
                fictCust = nullptr;
            }
            
        }
        FictCust.clear();
        //////////////

        for (BaseAction* action : actionsLog) {
             if(action!=nullptr){
                delete action;
                action = nullptr;
             }
            
        }
        actionsLog.clear();

        for (Volunteer* vol : volunteers) {
            if(vol!=nullptr){
            delete vol;
            vol = nullptr;
            }
           
        }
        volunteers.clear();

        for (Order* penOrder : pendingOrders) {
            if(penOrder!=nullptr){
                delete penOrder;
                penOrder = nullptr;
            }
            
        }
        pendingOrders.clear();

        for (Order* inProOrder : inProcessOrders) {
            if(inProOrder!=nullptr){
                delete inProOrder;
                inProOrder = nullptr;
            }
            
        }
        inProcessOrders.clear();

        for (Order* compOrder : completedOrders) {
            if(compOrder!=nullptr){
                delete compOrder;
                compOrder = nullptr;
            }
            
        }
        completedOrders.clear();

        for (Customer* cust : customers) {
             if(cust!=nullptr){
                delete cust;
                cust = nullptr;
             }
            
        }
        customers.clear();

        // Copy new data
        ////////////////////
        for (Volunteer* fictvol : other.FictVol) {
            FictVol.push_back(fictvol->clone());
        }
        for (Order* fictOrder : other.FictOrder) {
            FictOrder.push_back(fictOrder->clone());
        }
        for (Customer* fictCust : other.FictCust) {
            FictCust.push_back(fictCust->clone());
        }

        ////////////////////
        for (BaseAction* action : other.actionsLog) {
            actionsLog.push_back(action->clone());
        }

        for (Volunteer* vol : other.volunteers) {
            volunteers.push_back(vol->clone());
        }

        for (Order* penOrder : other.pendingOrders) {
            pendingOrders.push_back(penOrder->clone());
        }

        for (Order* inProOrder : other.inProcessOrders) {
            inProcessOrders.push_back(inProOrder->clone());
        }

        for (Order* compOrder : other.completedOrders) {
            completedOrders.push_back(compOrder->clone());
        }

        for (Customer* cust : other.customers) {
            customers.push_back(cust->clone());
        }
    }

    return *this;

}

//move copy assignment operator

WareHouse& WareHouse::operator=(const WareHouse &&other){
    if (this != &other){
        isOpen = other.isOpen;
        customerCounter = other.customerCounter;
        volunteerCounter = other.volunteerCounter;
        orderCounter = other.orderCounter;

        ///////////////
        for (Volunteer* fictvol :FictVol) {
            if(fictvol!=nullptr){
                delete fictvol;
            }
            
        }
        FictVol.clear();

        for (Volunteer* fictvol : other.FictVol) {
            FictVol.push_back(fictvol);
            fictvol = nullptr;
        }

/////////
        for (Order* fictOrder : FictOrder) {
            if(fictOrder!=nullptr){
                delete fictOrder;
            }
            
        }
        FictOrder.clear();

        for (Order* fictOrder : other.FictOrder) {
            FictOrder.push_back(fictOrder);
            fictOrder = nullptr;
        }

//////////
        for (Customer* fictCust : FictCust) {
            if(fictCust!=nullptr){
                delete fictCust;
            }
            
        }
        FictCust.clear();

        for (Customer* fictCust : other.FictCust) {
            FictCust.push_back(fictCust);
            fictCust = nullptr;
        }

        //////////////

        for (BaseAction* action : actionsLog){
            if(action!=nullptr){
                delete action;
            }
            
        }

        actionsLog.clear();

        for (BaseAction* action : other.actionsLog){
            actionsLog.push_back(action);
            action = nullptr;
        }

         for (Volunteer* vol : volunteers){
            if(vol!=nullptr){
                delete vol;
            }
            
        }

        volunteers.clear();

        for (Volunteer* vol : other.volunteers){
            volunteers.push_back(vol);
            vol = nullptr;
        }

        for (Order* penOrder : pendingOrders){
            if(penOrder!=nullptr){
                delete penOrder;
            }
            
        }

        pendingOrders.clear();

        for (Order* penOrder : other.pendingOrders){
            pendingOrders.push_back(penOrder);
            penOrder = nullptr;
        }

         for (Order* inProOrder : inProcessOrders){
            if(inProOrder!=nullptr){
                delete inProOrder;
            }
            
        }

        inProcessOrders.clear();

        for (Order* inProOrder : other.inProcessOrders){
            inProcessOrders.push_back(inProOrder);
            inProOrder = nullptr;
        }

        for (Order* compOrder : completedOrders){
            if(compOrder!=nullptr){
                delete compOrder;
            }
           
        }

        completedOrders.clear();

        for (Order* compOrder : other.completedOrders){
            completedOrders.push_back(compOrder);
            compOrder = nullptr;
        }

        for (Customer* cust : customers){
             if(cust!=nullptr){
                delete cust;
             }
            
        }

        customers.clear();

        for (Customer* cust : other.customers){
            customers.push_back(cust);
            cust = nullptr;
        }


    }

    return *this;

}



 void WareHouse::start(){
    std::cout << "WareHouse is open!";
    open();
    while(isOpen){
        std::string input;
        std::getline(std::cin, input);

        // Extract the action (first word)
        std::istringstream iss(input);
        std::string action;
        iss >> action;
        // Perform actions based on the first word
        if (action == "step") {
            // Extract the number for step action
            int number;
            if (iss >> number) {
                SimulateStep* step = new SimulateStep(number);
                addAction(step);
            } 
        } 
        else if (action == "order") {
            // Extract the number for order action
            int number;
            if (iss >> number) {
                AddOrder* order = new AddOrder(number);
                addAction(order);
            }      
        }  
        else if (action =="customer"){  
            std::string name; 
            std::string type;
            int distance;
            int maxOrd;  
            if(iss >> name >> type >> distance >> maxOrd){
                AddCustomer* cust = new AddCustomer(name,type, distance, maxOrd);
                addAction(cust);
            }            
        }
        else if (action =="orderStatus"){  
            int number;
            if (iss >> number) {
                PrintOrderStatus* print = new PrintOrderStatus(number);
                addAction(print);
            }    
        }
        else if (action =="customerStatus"){  
            int number;
            if (iss >> number) {
                PrintCustomerStatus* print = new PrintCustomerStatus(number);
                addAction(print);
            }    
        }
        else if (action =="volunteerStatus"){  
            int number;
            if (iss >> number) {
                PrintVolunteerStatus* print = new PrintVolunteerStatus(number);
                addAction(print);
            }  
        }
        else if (action =="log"){  
            PrintActionsLog* log = new PrintActionsLog();
            addAction(log);
        }
        else if (action =="close"){ 
            Close* close = new Close();
            addAction(close);
        }

        else if (action =="backup"){  
            BackupWareHouse* back = new BackupWareHouse();
            addAction(back);
        }

        else if (action =="restore"){  
            RestoreWareHouse* restore = new RestoreWareHouse();
            addAction(restore);
        }
        else{
            std::cout << "try again!" << std::endl;
        }

    }


 }

 void WareHouse::addOrder(Order* order){
    pendingOrders.push_back(order);
    orderCounter = orderCounter + 1;
 }

 void WareHouse::addAction(BaseAction* action){
     (*action).act(*this);
     this->actionsLog.push_back(action);
 }

 void WareHouse::addCustomer(Customer* customer){
    customers.push_back(customer);
    customerCounter = customerCounter +1;


 }

 bool WareHouse::customerExist(int customerId) const{
    if(0<=customerId  && customerId<customerCounter){
        return true;
    }

    return false;
 }

Customer& WareHouse::getCustomer(int customerId) const{
        for (Customer* cust : customers){
            if ((*cust).getId() == customerId){
                return *cust;
            }
        }
        return *FictCust.at(0);
}

//  bool WareHouse::volunteerExist(int volunteerId) const{
//     for (Volunteer* vol : volunteers){
//             if ((*vol).getId() == volunteerId){
//                 return true;
//             }
//         }

//     return false;
//  }


Volunteer& WareHouse::getVolunteer(int volunteerId) const{
     for (Volunteer* vol : volunteers){
            if ((*vol).getId() == volunteerId){
                return *vol;
            }
        }

     return *FictVol.at(0);
    
    }

bool WareHouse::orderExist(int orderId) const{
         for (Order* penOrder : pendingOrders){
            if ((*penOrder).getId() == orderId){
                return true;
            }
        }

         for (Order* inProOrder : inProcessOrders){
            if ((*inProOrder).getId() == orderId){
                return true;
            }
        }

         for (Order* compOrder : completedOrders){
            if ((*compOrder).getId() == orderId){
                return true;
            }
        }

        return false;
}

 Order& WareHouse::getOrder(int orderId) const{
        for (Order* penOrder : pendingOrders){
            if ((*penOrder).getId() == orderId){
                return *penOrder;
            }
        }

         for (Order* inProOrder : inProcessOrders){
            if ((*inProOrder).getId() == orderId){
                return *inProOrder;
            }
        }

         for (Order* compOrder : completedOrders){
            if ((*compOrder).getId() == orderId){
                return *compOrder;
            }
        }

        
        return  *FictOrder.at(0);;
    }

const vector<BaseAction*>& WareHouse::getActions() const{
    return actionsLog;
    }

vector<Order*>& WareHouse::getPendingOrders(){
    return pendingOrders;
}

vector<Order*> & WareHouse::getInProcessOrders(){
     return inProcessOrders;
}

vector<Order*> & WareHouse::getCompletedOrders(){
    return completedOrders;
}


vector<Volunteer*> & WareHouse::getVolunteers(){
    return volunteers;
}

int WareHouse::getCustomerCounter(){
    return customerCounter;
}

 int WareHouse::getOrderCounter(){
    return orderCounter;
 }


void WareHouse::close(){
    isOpen = false;

}

void WareHouse::open(){
    isOpen = true;
}



int WareHouse::getIndexInProcessOrder(int orderId)const{
    int i = 0;
    for (Order* inProOrder : inProcessOrders){
            if ((*inProOrder).getId() == orderId){
                return i;
            }

            i+=1;
    }

    return -1;
}

int WareHouse::getIndexInPendingOrder(int orderId)const{
    int i = 0;
    //check if the vector is empty
    for (Order* pendOrder : pendingOrders){
            if ((*pendOrder).getId() == orderId){
                return i;
            }

            i+=1;
    }

    return -1;
}