#pragma once
#include <string>
#include <vector>
#include "WareHouse.h"
using std::string;
using std::vector;

class Order;
class WareHouse;


class Customer {
    public:
        Customer(int id, const string& name, int locationDistance, int maxOrders);
        virtual ~Customer() = default;

        const string& getName() const;
        int getId() const;
        int getCustomerDistance() const;
        int getMaxOrders() const;
        int getNumOrders() const;

        void setOrdersIds(vector<int> orders);
        bool canMakeOrder() const;
        const vector<int>& getOrdersIds() const;
        int addOrder(int orderId);  //return OrderId if order was added successfully, -1 otherwise

        string toString(WareHouse& wareHouse) const; // added by us, not in the skeleton provided at the start, change other toStrings to const, makes sense.

        virtual Customer* clone() const = 0;

        
    private:
        const int id;
        const string name;
        const int locationDistance;
        const int maxOrders;
        vector<int> ordersId;
        int orders_Counter;
};




class SoldierCustomer: public Customer {
    public:
        SoldierCustomer(int id, const string& name, int locationDistance, int maxOrders);
        SoldierCustomer* clone() const override;
    private:
        
};




class CivilianCustomer: public Customer {
    public:
        CivilianCustomer(int id, const string& name, int locationDistance, int maxOrders);
        CivilianCustomer* clone() const override;
    private:
        
};
