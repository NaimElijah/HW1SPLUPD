#pragma once
#include <string>
#include <vector>
#include "Order.h"
#include "Customer.h"
#include "Volunteer.h"
#include "Action.h"
using namespace std;
class Action;
class Volunteer;
// extern WareHouse* backup;

// Warehouse responsible for Volunteers, Customers and Actions. We need to make a constructor, copy constructor, destructor.  <========
class WareHouse {
    public:
        WareHouse(const string& configFilePath);
        WareHouse(const WareHouse& wh);  // copy constructor
        WareHouse(WareHouse&& other) noexcept;     //  move constructor
        ~WareHouse();      //  destructor

        WareHouse& operator=(const WareHouse& other);  // copy assignment operator
        WareHouse& operator=(WareHouse&& other) noexcept;    // move assignment operator

        void InputFromFile(const string& configFilePath);  //  inputs the data from the configFile and builds the WareHouse, method added by me
        void start();
        const vector<Action*>& getActions() const;
        bool is_Open() const;
        void addOrder(Order* order);
        void addAction(Action* action);
        void addVolunteer(Volunteer* volunteer);
        void addCustomer(Customer* customer);
        Customer& getCustomer(int customerId) const;
        Volunteer& getVolunteer(int volunteerId) const;
        Order& getOrder(int orderId) const;

        void handleOrders();  // used in SimulateStep in Action.cpp
        void handleVolunteers();  // used in SimulateStep in Action.cpp

        vector<Order*> getPendingOrders() const;
        vector<Order*> getInProcessOrders() const;
        vector<Order*> getCompletedOrders() const;

        vector<Volunteer*> getVolunteers() const;
        vector<Customer*> getCustomers() const;

        void changeBackedUp();
        bool getBackedUp();

        int getCustomerCounter() const;
        int getVolunteerCounter() const;
        int getOrdersCounter() const;
        Volunteer& getNotfV() const;

        void setCustomerCounter(int i);
        void setVolunteerCounter(int i);
        void setOrdersCounter(int i);

        void close();
        void open();


    private:
        bool isOpen;
        bool backedUp;
        vector<Action*> actionsLog;
        vector<Order*> pendingOrders;
        vector<Order*> inProcessOrders;
        vector<Order*> completedOrders;
        vector<Volunteer*> volunteers;
        vector<Customer*> customers;
        int customerCounter;  //For assigning unique customer IDs
        int volunteerCounter;  //For assigning unique volunteer IDs
        int ordersCounter;  //For assigning unique order IDs

        Volunteer* notfV;

};
