#include <string>
#include <vector>
#include "../include/Customer.h"
#include "../include/WareHouse.h"
#include <algorithm>
#include <iostream>
#include <string>
using std::string;
using std::vector;
using namespace std;

// class Customer
Customer::Customer(int id, const string& name, int locationDistance, int maxOrders): id(id), name(name), locationDistance(locationDistance), maxOrders(maxOrders), ordersId(), orders_Counter(0){};

const string& Customer::getName() const{
    return name;
}

int Customer::getId() const{
    return id;
}

int Customer::getCustomerDistance() const{
    return locationDistance;
}

int Customer::getMaxOrders() const{
    return maxOrders;
}

int Customer::getNumOrders() const{
    return orders_Counter;
}

bool Customer::canMakeOrder() const{
    return getMaxOrders() > getNumOrders();
}

const vector<int>& Customer::getOrdersIds() const{
    return ordersId;
}

void Customer::setOrdersIds(vector<int> orders){
    this->ordersId = orders;
}

int Customer::addOrder(int orderId){
    if (orders_Counter >= maxOrders) {
        return -1;
    }
    // Check if the orderId is already in the list
    for(int id : ordersId){
        if (id == orderId) { // check if it's distinct
        return -1;
        }
    }
    ordersId.push_back(orderId); // Add the orderId to the list, return the orderId to indicate success
    orders_Counter++;
    return orderId;
}

string Customer::toString(WareHouse& wareHouse) const{
    string res = "";
    res += "CustomerID: " + to_string(getId());

    for(int id: ordersId){
        res += "\nOrderId: " + to_string(id);

        string sta;
        if(wareHouse.getOrder(id).getStatus() == OrderStatus::PENDING){
            sta = "PENDING";
        }else if(wareHouse.getOrder(id).getStatus() == OrderStatus::COLLECTING){
            sta = "COLLECTING";
        }else if(wareHouse.getOrder(id).getStatus() == OrderStatus::DELIVERING){
            sta = "DELIVERING";
        }else if(wareHouse.getOrder(id).getStatus() == OrderStatus::COMPLETED){
            sta = "COMPLETED";
        }
        res += "\nOrderStatus: " + sta;
    }
    res += "\nnumOrdersLeft: " + to_string(getMaxOrders() - getNumOrders());

    return res;
}








// class SoldierCustomer

SoldierCustomer::SoldierCustomer(int id, const string& name, int locationDistance, int maxOrders):Customer(id, name, locationDistance, maxOrders){};

SoldierCustomer* SoldierCustomer::clone() const{
    return new SoldierCustomer(*this);
}









// class CivilianCustomer

CivilianCustomer::CivilianCustomer(int id, const string& name, int locationDistance, int maxOrders):Customer(id, name, locationDistance, maxOrders){};

CivilianCustomer* CivilianCustomer::clone() const{
    return new CivilianCustomer(*this);
}

