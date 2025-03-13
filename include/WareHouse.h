#pragma once
#include <string>
#include <vector>
using namespace std;

#include "../include/Order.h"
#include "../include/Customer.h"
#include "../include/Volunteer.h"
#include "../include/Action.h"

class BaseAction;
class Volunteer;

// Warehouse responsible for Volunteers, Customers Actions, and Orders.


class WareHouse {

    public:
        void parseVolunteer(const std::vector<std::string>& tokens);//we added it
        void parseCustomer(const std::vector<std::string>& tokens);//we added it
        std::vector<std::string> split(const std::string& s, char delimiter);//we added it
        WareHouse(const string &configFilePath);
        WareHouse(const WareHouse &other);//copy constructor
        WareHouse(WareHouse &&other);//move copt constructor//should be const? 
        ~WareHouse();//destructor
        WareHouse &operator=(const WareHouse &other);//copy assignment operator
        WareHouse &operator=(const WareHouse &&other);//move copy assignment operator
        void start();
        void addOrder(Order* order);
        void addAction(BaseAction* action);
        void addCustomer(Customer* customer);//we added it
        bool customerExist(int customerId) const;//we added it
        Customer &getCustomer(int customerId) const;
        //bool volunteerExist(int volunteerId) const;//we added it
        Volunteer &getVolunteer(int volunteerId) const;
        bool orderExist(int orderId) const;//we added it
        Order &getOrder(int orderId) const;
        const vector<BaseAction*> &getActions() const;
        vector<Order*> &getPendingOrders();//we added it
        vector<Order*> &getInProcessOrders();//we added it
        vector<Order*> &getCompletedOrders();//we added it
        vector<Volunteer*> &getVolunteers();//we added it
        int getCustomerCounter();//we added it
        int getOrderCounter();//we added it


        int getIndexInPendingOrder(int orderId)const;//we atded it
        int getIndexInProcessOrder(int orderId)const;//we atded it


        void close();
        void open();

        vector<Volunteer*> FictVol; // i added it
        vector<Order*> FictOrder ;// i added it
        vector<Customer*> FictCust;// i added it

    private:
        bool isOpen;
        vector<BaseAction*> actionsLog;
        vector<Volunteer*> volunteers;
        vector<Order*> pendingOrders;
        vector<Order*> inProcessOrders;
        vector<Order*> completedOrders;
        vector<Customer*> customers;
        int customerCounter; //For assigning unique customer IDs
        int volunteerCounter; //For assigning unique volunteer IDs
        int orderCounter;//we added it

        


};