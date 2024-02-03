#include "../include/Order.h"
#include <sstream>
#include <iostream>
#include <string>

using namespace std;


    Order::Order(int id, int customerId, int distance): id(id),customerId(customerId),distance(distance), status(), collectorId(NO_VOLUNTEER), driverId(NO_VOLUNTEER){};

    int Order::getId() const{
        return id;
    }

    int Order::getDistance() const{
        return distance;
    }

    int Order::getCustomerId() const{
        return customerId;
    }
    
    int Order::getCollectorId() const{
        if(collectorId == NO_VOLUNTEER){
            return -1;
        }
        return collectorId;
    }

    int Order::getDriverId() const{
        if(driverId == NO_VOLUNTEER){
            return -1;
        }
        return driverId;
    }

    OrderStatus Order::getStatus() const{
        return status;
    }
    
    Order* Order::clone() const{
        return new Order(*this);
    }


    void Order::setStatus(OrderStatus status){
        this->status = status;
    }

    void Order::setCollectorId(int collectorId){
        this->collectorId = collectorId;
    }
    
    void Order::setDriverId(int driverId){
        this->driverId = driverId;
    }


    const string Order::toString() const{
        string res = "";
        res += "OrderId: " + to_string(getId());

        string sta;
        if(getStatus() == OrderStatus::PENDING){
            sta = "PENDING";
        }else if(getStatus() == OrderStatus::COLLECTING){
            sta = "COLLECTING";
        }else if(getStatus() == OrderStatus::DELIVERING){
            sta = "DELIVERING";
        }else if(getStatus() == OrderStatus::COMPLETED){
            sta = "COMPLETED";
        }
        res += "\nOrderStatus: " + sta;

        res += "\nCustomerId: " + to_string(getCustomerId());
        
        if(getCollectorId() == -1){
            res += "\nCollector: None";
        }else{
            res += "\nCollector: " + to_string(getCollectorId());
        }
        
        if(getDriverId() == -1){
            res += "\nDriver: None";
        }else{
            res += "\nDriver: " + to_string(getDriverId());
        }

        return res;
    }
