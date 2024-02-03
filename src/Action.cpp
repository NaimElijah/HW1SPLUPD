#include "../include/Action.h"
#include "../include/Order.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

///               Action Class      <=================================================

Action::Action(): errorMsg(""), status(){};

ActionStatus Action::getStatus() const{
    return status;
}

// more pure virtual methods(act, toString, clone) here to be implemented in children

void Action::complete(){
    status = ActionStatus::COMPLETED;
}

void Action::error(string errorMsg){
    status = ActionStatus::ERROR;
    this->errorMsg = errorMsg;
    cout << "Error: " + this->errorMsg;
}

string Action::getErrorMsg() const{
    return errorMsg;
}

void Action::setErrorMsg(string err){
    errorMsg = err;
}

void Action::setStatus(ActionStatus a_s){
    status = a_s;
}
















//           Class SimulateStep extends Action.           <=================================================

SimulateStep::SimulateStep(int numOfSteps): numOfSteps(numOfSteps){};


void SimulateStep::act(WareHouse& wareHouse){
    for(int j=1; j <= numOfSteps; j++){

        wareHouse.handleOrders();

        wareHouse.handleVolunteers();

    }
    this->complete();
}


string SimulateStep::toString() const{
    string res = "";
    res += "SimulateStep " + to_string(numOfSteps);

    if(this->getStatus() == ActionStatus::COMPLETED){
        res += " COMPLETED";
    }else if (this->getStatus() == ActionStatus::ERROR){
        res += " ERROR";
    }

    return res;
}

SimulateStep* SimulateStep::clone() const{
    return new SimulateStep(*this);  // using the default copy constructor
}
















//             Class AddOrder extends Action      <=================================================

AddOrder::AddOrder(int id): customerId(id){};


void AddOrder::act(WareHouse& wareHouse){
    if((customerId > wareHouse.getCustomerCounter()) || (wareHouse.getCustomer(customerId).canMakeOrder() == false)){
        error("Cannot place this order\n");
    }else{
        Order* o = new Order(wareHouse.getOrdersCounter(), customerId, wareHouse.getCustomer(customerId).getCustomerDistance());
        o->setStatus(OrderStatus::PENDING);
        wareHouse.addOrder(o);
        this->complete();
    }
}

AddOrder* AddOrder::clone() const{
    return new AddOrder(*this);  // using the default copy constructor
}

string AddOrder::toString() const{
    string res = "";
    res += "order " + to_string(customerId);
    if(this->getStatus() == ActionStatus::COMPLETED){
        res += " COMPLETED";
    }else if (this->getStatus() == ActionStatus::ERROR){
        res += " ERROR";
    }

    return res;
}
















//             Class AddCustomer extends Action      <=================================================

AddCustomer::AddCustomer(const string &customerName, const string &customerType, int distance, int maxOrders): customerName(customerName), customerType(customerType == "soldier" ? CustomerType::Soldier : CustomerType::Civilian), distance(distance), maxOrders(maxOrders){  // if this doesn't compile, make a helper method in this class and use it here in initia'
};


void AddCustomer::act(WareHouse& wareHouse){
    Customer* c;
    if(this->customerType == CustomerType::Soldier){
        c = new SoldierCustomer(wareHouse.getCustomerCounter(), customerName, distance, maxOrders);
    }else if(this->customerType == CustomerType::Civilian){
        c = new CivilianCustomer(wareHouse.getCustomerCounter(), customerName, distance, maxOrders);
    }
    wareHouse.addCustomer(c);
    this->complete();
}

AddCustomer* AddCustomer::clone() const{
    return new AddCustomer(*this);  // using the default copy constructor
}

string AddCustomer::toString() const{
    string res = "";
    res += "customer " + customerName;
    res += " " + to_string(distance);
    res += " " + to_string(maxOrders);
    if(this->getStatus() == ActionStatus::COMPLETED){
        res += " COMPLETED";
    }else if (this->getStatus() == ActionStatus::ERROR){
        res += " ERROR";
    }

    return res;
}
















//             Class PrintOrderStatus extends Action      <=================================================

PrintOrderStatus::PrintOrderStatus(int id): orderId(id){};


void PrintOrderStatus::act(WareHouse& wareHouse){
    if(orderId > wareHouse.getOrdersCounter()){
        error("Order doesn't exist\n");
    }else{
        cout << wareHouse.getOrder(orderId).toString() + "\n";
        this->complete();
    }

}

PrintOrderStatus* PrintOrderStatus::clone() const{
    return new PrintOrderStatus(*this);  // using the default copy constructor
}

string PrintOrderStatus::toString() const{
    string res = "";
    res += "orderStatus " + to_string(orderId);
    if(this->getStatus() == ActionStatus::COMPLETED){
        res += " COMPLETED";
    }else if (this->getStatus() == ActionStatus::ERROR){
        res += " ERROR";
    }

    return res;
}

















//             Class PrintCustomerStatus extends Action      <=================================================

PrintCustomerStatus::PrintCustomerStatus(int customerId): customerId(customerId){};

void PrintCustomerStatus::act(WareHouse& wareHouse){
    if(customerId > wareHouse.getCustomerCounter()){
        error("Customer doesn't exist\n");
    }else{
        cout << wareHouse.getCustomer(customerId).toString(wareHouse) + "\n";
        this->complete();
    }
}

PrintCustomerStatus* PrintCustomerStatus::clone() const{
    return new PrintCustomerStatus(*this);  // using the default copy constructor
}

string PrintCustomerStatus::toString() const{
    string res = "";
    res += "customerStatus " + to_string(customerId);
    if(this->getStatus() == ActionStatus::COMPLETED){
        res += " COMPLETED";
    }else if (this->getStatus() == ActionStatus::ERROR){
        res += " ERROR";
    }

    return res;
}

















//             Class PrintVolunteerStatus extends Action      <=================================================

PrintVolunteerStatus::PrintVolunteerStatus(int id): volunteerId(id){};


void PrintVolunteerStatus::act(WareHouse& wareHouse){
    if(wareHouse.getVolunteer(volunteerId).getName() == "not found"){
        error("Volunteer doesn't exist\n");
    }else{
        cout << wareHouse.getVolunteer(volunteerId).toString() +"\n";
        this->complete();
    }
}

PrintVolunteerStatus* PrintVolunteerStatus::clone() const{
    return new PrintVolunteerStatus(*this);  // using the default copy constructor
}

string PrintVolunteerStatus::toString() const{
    string res = "";
    res += "volunteerStatus " + to_string(volunteerId);
    if(this->getStatus() == ActionStatus::COMPLETED){
        res += " COMPLETED";
    }else if (this->getStatus() == ActionStatus::ERROR){
        res += " ERROR";
    }

    return res;
}

















//             Class PrintActionsLog extends Action      <=================================================

PrintActionsLog::PrintActionsLog(){};


void PrintActionsLog::act(WareHouse& wareHouse){
    for(Action* a : wareHouse.getActions()){
        cout << a->toString() + "\n";
    }
    cout << wareHouse.getCustomers().size();   //   <<<===================  test
	cout << wareHouse.getVolunteers().size();   //   <<<===================  test
	cout << wareHouse.getPendingOrders().size();   //   <<<===================  test
    this->complete();
}

PrintActionsLog* PrintActionsLog::clone() const{
    return new PrintActionsLog(*this);  // using the default copy constructor
}

string PrintActionsLog::toString() const{
    string res = "log";
    if(this->getStatus() == ActionStatus::COMPLETED){
        res += " COMPLETED";
    }else if (this->getStatus() == ActionStatus::ERROR){
        res += " ERROR";
    }

    return res;
}
















//             Class Close extends Action      <=================================================

Close::Close(){};


void Close::act(WareHouse& wareHouse){
    // print all the orders with each of their status's
    string output = "";
    for(Order* o : wareHouse.getPendingOrders()){
        output += "OrderID: " + to_string(o->getId());
        output += ", CustomerID: " + to_string(o->getCustomerId());
        output += ", OrderStatus: PENDING\n";
    }

    string status_s;
    for(Order* o : wareHouse.getInProcessOrders()){
        output += "OrderID: " + to_string(o->getId());
        output += ", CustomerID: " + to_string(o->getCustomerId());
        
        if(o->getStatus() == OrderStatus::COLLECTING){
            status_s = "COLLECTING";
        }else if (o->getStatus() == OrderStatus::DELIVERING){
            status_s = "DELIVERING";
        }
        output += ", OrderStatus: " + status_s + "\n";
    }


    for(Order* o : wareHouse.getCompletedOrders()){
        output += "OrderID: " + to_string(o->getId());
        output += ", CustomerID: " + to_string(o->getCustomerId());
        output += ", OrderStatus: COMPLETED\n";
    }

    // output.erase(output.end());  to delete the \n
    cout << output;

    wareHouse.close();
    // delete wareHouse;
    ///   ===========================>>>>>>>>>>>  the destructor will automatically activate when the WareHouse in main goes out of scope, becasue the WareHouse in main is on the stack

    this->complete();
}



Close* Close::clone() const{
    return new Close(*this);  // using the default copy constructor
}

string Close::toString() const{  // for the sake of this having a toString(), even though we won't get to use it
    string res = "close";
    if(this->getStatus() == ActionStatus::COMPLETED){
        res += " COMPLETED";
    }else if (this->getStatus() == ActionStatus::ERROR){
        res += " ERROR";
    }

    return res;
}


















//             Class BackupWareHouse extends Action      <=================================================

BackupWareHouse::BackupWareHouse(){};


void BackupWareHouse::act(WareHouse& wareHouse){
    if(backup!=nullptr){
        delete backup;
    }

    if(wareHouse.getBackedUp()==false){
        wareHouse.changeBackedUp();
    }
    backup = new WareHouse(wareHouse);
    complete();
}

BackupWareHouse* BackupWareHouse::clone() const{
    return new BackupWareHouse(*this);  // using the default copy constructor
}

string BackupWareHouse::toString() const{
    string res = "backup";
    if(this->getStatus() == ActionStatus::COMPLETED){
        res += " COMPLETED";
    }else if (this->getStatus() == ActionStatus::ERROR){  // even though it doesn't get an error
        res += " ERROR";
    }

    return res;
}

















//             Class RestoreWareHouse extends Action      <=================================================

RestoreWareHouse::RestoreWareHouse(){};


void RestoreWareHouse::act(WareHouse& wareHouse){

    if(wareHouse.getBackedUp()){
        wareHouse = *backup;  // using copy assignment operator
        complete();
    }else{
        error("No backup available\n");
    }

}

RestoreWareHouse* RestoreWareHouse::clone() const{
    return new RestoreWareHouse(*this);  // using the default copy constructor
}

string RestoreWareHouse::toString() const{
    string res = "restore";
    if(this->getStatus() == ActionStatus::COMPLETED){
        res += " COMPLETED";
    }else if (this->getStatus() == ActionStatus::ERROR){
        res += " ERROR";
    }

    return res;
}

