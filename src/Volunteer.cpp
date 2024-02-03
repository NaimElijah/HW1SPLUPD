#include "../include/Volunteer.h"
#include <iostream>
#include <string>
using namespace std;

//        Volunteer Class      <=================================================

Volunteer::Volunteer(int id, const string& name): completedOrderId(NO_ORDER), activeOrderId(NO_ORDER), id(id), name(name), vol_identifier("abstract yet"){};

int Volunteer::getId() const{
    return id;
}

const string& Volunteer::getName() const{
    return name;
}

int Volunteer::getActiveOrderId() const{
    return activeOrderId;
}

int Volunteer::getCompletedOrderId() const{
    return completedOrderId;
}

void Volunteer::setActiveOrderId(int actId){
    activeOrderId = actId;
}

void Volunteer::setCompletedOrderId(int comId){
    completedOrderId = comId;
}


bool Volunteer::isBusy() const{
    return activeOrderId != NO_ORDER;   // so when the volunteer is done with something his activeOrderId should be NO_ORDER so that we'll know that he's free
}

string Volunteer::get_vol_identifier() const{
    return vol_identifier;
}

void Volunteer::set_vol_identifier(string iden){
    vol_identifier = iden;
}
















//               Collector Volunteer Class extends Volunteer      <=================================================

CollectorVolunteer::CollectorVolunteer(int id, const string& name, int coolDown): Volunteer(id, name), coolDown(coolDown), timeLeft(coolDown){
    this->set_vol_identifier("c");
};

CollectorVolunteer* CollectorVolunteer::clone() const{
    return new CollectorVolunteer(*this); // return with the default copy constructor  <<<<===========================
}

void CollectorVolunteer::step(){
    decreaseCoolDown(); // no need for the bool it returns, as told, we must keep the declarations as they are but we can just not use the bool it returns
}

int CollectorVolunteer::getCoolDown() const{
    return coolDown;
}

int CollectorVolunteer::getTimeLeft() const{
    return timeLeft;
}

void CollectorVolunteer::setTimeLeft(int time){
    timeLeft = time;
}

bool CollectorVolunteer::decreaseCoolDown(){
    timeLeft = timeLeft - 1; // what happen if time left is 0 before this line
    if(timeLeft == 0){
        this->setCompletedOrderId(this->getActiveOrderId());   // finished delivering the order so put the activeOrderId in the completedOrderId and put NO_ORDER in activeOrderId
        this->setActiveOrderId(NO_ORDER);  // this also makes the Volunteer not busy
        return true;
    }
    return false;
}

bool CollectorVolunteer::hasOrdersLeft() const{
    return true;
}

bool CollectorVolunteer::canTakeOrder(const Order& order) const{
    if(isBusy() == false){
        return true;
    }
    return false;
}

void CollectorVolunteer::acceptOrder(const Order& order){
    this->setActiveOrderId(order.getId());
    this->setTimeLeft(this->getCoolDown());

}

string CollectorVolunteer::toString() const{
    string res = "";
    res += "VolunteerID: " + to_string(this->getId());
    
    string boo;
    if(to_string(this->isBusy()) == "0"){
        boo = "false";
    }else{
        boo = "true";
    }
    res += "\nisBusy: " + boo;


    if(this->getActiveOrderId() == NO_ORDER){
        res += "\nOrderID: None";
        res += "\nTimeLeft: None";
    }else{
        res += "\nOrderID: " + to_string(this->getActiveOrderId());
        res += "\nTimeLeft: " + to_string(this->getTimeLeft());
    }

    res += "\nOrdersLeft: No Limit";

    return res;
}





















//                LimitedCollectorVolunteer Class extends CollectorVolunteer      <=================================================

LimitedCollectorVolunteer::LimitedCollectorVolunteer(int id, const string& name, int coolDown ,int maxOrders): CollectorVolunteer(id, name, coolDown), maxOrders(maxOrders), ordersLeft(maxOrders){};

LimitedCollectorVolunteer* LimitedCollectorVolunteer::clone() const{
    return new LimitedCollectorVolunteer(*this); // return with the default copy constructor  <<<<===========================
}

bool LimitedCollectorVolunteer::hasOrdersLeft() const{
    return ordersLeft > 0;
}

bool LimitedCollectorVolunteer::canTakeOrder(const Order& order) const{
    if(isBusy() == false && hasOrdersLeft()){
        return true;
    }
    return false;
}

void LimitedCollectorVolunteer::acceptOrder(const Order& order){  // check if can take order first, in SimulateStep
    this->setActiveOrderId(order.getId());
    this->setTimeLeft(this->getCoolDown());
    this->setNumOrdersLeft(this->getNumOrdersLeft()-1);

}

int LimitedCollectorVolunteer::getMaxOrders() const{
    return maxOrders;
}

int LimitedCollectorVolunteer::getNumOrdersLeft() const{
    return ordersLeft;
}

void LimitedCollectorVolunteer::setNumOrdersLeft(int nol){
    this->ordersLeft = nol;
}

string LimitedCollectorVolunteer::toString() const{
    string res = "";
    res += "VolunteerID: " + to_string(this->getId());

    string boo;
    if(to_string(this->isBusy()) == "0"){
        boo = "false";
    }else{
        boo = "true";
    }
    res += "\nisBusy: " + boo;
    
    if(this->getActiveOrderId() == NO_ORDER){
        res += "\nOrderID: None";
        res += "\nTimeLeft: None";
    }else{
        res += "\nOrderID: " + to_string(this->getActiveOrderId());
        res += "\nTimeLeft: " + to_string(this->getTimeLeft());
    }

    res += "\nOrdersLeft: " + to_string(this->getNumOrdersLeft());

    return res;
}


















//               DriverVolunteer Class extends Volunteer      <=================================================

DriverVolunteer::DriverVolunteer(int id, const string& name, int maxDistance, int distancePerStep): Volunteer(id, name), maxDistance(maxDistance), distancePerStep(distancePerStep), distanceLeft(maxDistance){
    this->set_vol_identifier("d");
};

DriverVolunteer* DriverVolunteer::clone() const{
    return new DriverVolunteer(*this); // return with the default copy constructor  <<<<===========================
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

void DriverVolunteer::setDistanceLeft(int distance){
    distanceLeft = distance;
}

bool DriverVolunteer::decreaseDistanceLeft(){
    distanceLeft = distanceLeft - distancePerStep;
    if(distanceLeft <= 0){  // delivered
        distanceLeft = 0;  // just so it won't be negetive
        setCompletedOrderId(getActiveOrderId());   // finished delivering the order so put the activeOrderId in the completedOrderId and put NO_ORDER in activeOrderId
        setActiveOrderId(NO_ORDER);  // this also makes the Volunteer not busy
        return true;
    }
    return false;
}

bool DriverVolunteer::hasOrdersLeft() const{
    return true;
}

bool DriverVolunteer::canTakeOrder(const Order& order) const{
    if(isBusy() == false && order.getDistance()<=this->getMaxDistance()){
        return true;
    }
    return false;
}

void DriverVolunteer::acceptOrder(const Order& order){  // check if can take order first, in SimulateStep
    this->setActiveOrderId(order.getId());
    this->setDistanceLeft(order.getDistance());

}

void DriverVolunteer::step(){
    decreaseDistanceLeft(); // no need for the bool it returns, as told, we must keep the declarations as they are but we can just not use the bool it returns
}

string DriverVolunteer::toString() const{
    string res = "";
    res += "VolunteerID: " + to_string(this->getId());

    string boo;
    if(to_string(this->isBusy()) == "0"){
        boo = "false";
    }else{
        boo = "true";
    }
    res += "\nisBusy: " + boo;
    
    if(this->getActiveOrderId() == NO_ORDER){
        res += "\nOrderID: None";
        res += "\nDistanceLeft: None";
    }else{
        res += "\nOrderID: " + to_string(this->getActiveOrderId());
        res += "\nDistanceLeft: " + to_string(this->getDistanceLeft());
    }

    res += "\nOrdersLeft: No Limit";

    return res;
}


















//               LimitedDriverVolunteer Class extends DriverVolunteer      <=================================================

LimitedDriverVolunteer::LimitedDriverVolunteer(int id, const string& name, int maxDistance, int distancePerStep,int maxOrders): DriverVolunteer(id, name, maxDistance, distancePerStep), maxOrders(maxOrders), ordersLeft(maxOrders){};

LimitedDriverVolunteer* LimitedDriverVolunteer::clone() const{
    return new LimitedDriverVolunteer(*this); // return with the default copy constructor  <<<<===========================
}

int LimitedDriverVolunteer::getMaxOrders() const{
    return maxOrders;
}

int LimitedDriverVolunteer::getNumOrdersLeft() const{
    return ordersLeft;
}

void LimitedDriverVolunteer::setNumOrdersLeft(int nol){
    ordersLeft = nol;
}

bool LimitedDriverVolunteer::hasOrdersLeft() const{
    return ordersLeft > 0;
}

bool LimitedDriverVolunteer::canTakeOrder(const Order& order) const{
    if(isBusy() == false && hasOrdersLeft() && order.getDistance()<=this->getMaxDistance()){
        return true;
    }
    return false;
}

void LimitedDriverVolunteer::acceptOrder(const Order& order){  // check if can take order first, in SimulateStep
    this->setActiveOrderId(order.getId());
    this->setDistanceLeft(order.getDistance());
    this->setNumOrdersLeft(this->getNumOrdersLeft()-1);

}

string LimitedDriverVolunteer::toString() const{
    string res = "";
    res += "VolunteerID: " + to_string(this->getId());

    string boo;
    if(to_string(this->isBusy()) == "0"){
        boo = "false";
    }else{
        boo = "true";
    }
    res += "\nisBusy: " + boo;
    
    if(this->getActiveOrderId() == NO_ORDER){
        res += "\nOrderID: None";
        res += "\nDistanceLeft: None";
    }else{
        res += "\nOrderID: " + to_string(this->getActiveOrderId());
        res += "\nDistanceLeft: " + to_string(this->getDistanceLeft());
    }

    res += "\nOrdersLeft: " + to_string(this->getNumOrdersLeft());

    return res;
}





