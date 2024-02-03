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
    int pos_v;
    // vector<int> indicesToRemove;
    // int indice = 0;
    // Order* ord_in_del = new Order(-1,-1,-1);
    // cout << " beforebeforependings ";   //  <<<<<<================================  test
    // cout << wareHouse.getCustomers().size();   //   <<<===================  test
    // cout << wareHouse.getVolunteers().size();   //   <<<===================  test
	// cout << wareHouse.getPendingOrders().size();   //   <<<===================  test

    for(int j=1; j <= numOfSteps; j++){

        wareHouse.handleOrdersInStep();



        cout << " beforependings ";  //   <<<<<<================================  test
        cout << wareHouse.getCustomers().size();   //   <<<===================  test
	    cout << wareHouse.getVolunteers().size();   //   <<<===================  test
	    cout << wareHouse.getPendingOrders().size();   //   <<<===================  test
        // if(wareHouse.getPendingOrders().size() > 0){          //                                   copied from here to handleOrdersInStep
        //     int pendOrd_index = 0;
        //     for(Order* pendingOrder : wareHouse.getPendingOrders()){  // taking care of the orders in the pendingorders vector((before collecting) or (after collecting and before delivering), checkkkkkkkkkkkkkkkkk)

        // //         // for(int i=0; i< int(wareHouse.getPendingOrders().size()); i++){
        // //         // for(int i=0; (i>=0 && (size_t)i<wareHouse.getPendingOrders().size()); i++){
        // //         // for(auto iter = wareHouse.getPendingOrders().begin(); iter != wareHouse.getPendingOrders().end();){  // <<<<<=======================  with iterator
        // //         // for(auto iter = wareHouse.getPendingOrders().rbegin(); iter != wareHouse.getPendingOrders().rend();){  // <<<<<=======================  with reverse iterator
        // //         // Order* order = *iter;
        //         // go over all the collectors and see who is available   <<<============
        // //         // if(wareHouse.getPendingOrders().at(i)->getStatus() == OrderStatus::PENDING && wareHouse.getPendingOrders().at(i)->getCollectorId() == NO_VOLUNTEER){  // assigning a new order to a collector. move orders between vectors accordingly, when finished.
        //         if(pendingOrder->getStatus() == OrderStatus::PENDING && pendingOrder->getCollectorId() == NO_VOLUNTEER && pendingOrder != nullptr){
        //             for(Volunteer* vol : wareHouse.getVolunteers()){
        //                 if(vol->get_vol_identifier() == "c" && vol->canTakeOrder(*(pendingOrder))){
        //                     pendingOrder->setCollectorId(vol->getId());
        // //                     // cout << (*iter)->toString();     //        <<<<<===================  test
        //                     vol->acceptOrder(*(pendingOrder));   ///    do a clone to Order and add a clone when giving it to the next place and delete the old
        //                     pendingOrder->setStatus(OrderStatus::COLLECTING);
        //                     wareHouse.addOrder(pendingOrder->clone()); // adding to inprocessorders now because we changed the order's status, might need to put Order o* = new Order(pendingOrder) inside<=========, because erase deletes, so it won't delete our order(so we want to use the copy constructor)
        //                     // it adds the same order*thenumofcollectors and each of them get the same one <<<<<<<<<================================================== # fix # !!!!!!
        //                     delete pendingOrder;
        //                     pendingOrder = nullptr;
        //                     wareHouse.getPendingOrders().at(0) = nullptr;   //  <<<<<<========================================  testing
        //                     // wareHouse.getPendingOrders().erase(wareHouse.getPendingOrders().begin() + pendOrd_index); // remove because the order moved to the inprocessorders vector
        //                     // pendingOrder = ord_in_del;
        //                     indicesToRemove.push_back(indice);
        //                     indice++;
        //                     break;
        //                     // wareHouse.getPendingOrders().erase(wareHouse.getPendingOrders().begin() + pendOrd_index); // remove because the order moved to the inprocessorders vector
        // //                     // delete *iter;
        // //                     // iter = wareHouse.getPendingOrders().erase(iter);  // iterator
        // //                     // iter = vector<Order*>::reverse_iterator(wareHouse.getPendingOrders().erase(next(iter).base()));   // reverse iterator
        //                     // pendingOrder = nullptr;  // <<<<<<<<<===============================================  this gives a segmentation fault right now !!!!!!

        //                 } // now gave the new order to a collector if a collector is free
        //             }

        // //         // }else if(wareHouse.getPendingOrders().at(i)->getStatus() == OrderStatus::PENDING){  // assigning an order that has been processed by a collector, to a driver. move orders between vectors accordingly, when finished.
        //         }else if(pendingOrder->getStatus() == OrderStatus::PENDING && pendingOrder != nullptr){  // <<<<<============================  with iterator
        //             for(Volunteer* vol : wareHouse.getVolunteers()){
        //                 if(vol->get_vol_identifier() == "d" && vol->canTakeOrder(*(pendingOrder))){
        //                     pendingOrder->setDriverId(vol->getId());
        //                     vol->acceptOrder(*(pendingOrder));
        //                     pendingOrder->setStatus(OrderStatus::DELIVERING);
        //                     wareHouse.addOrder(pendingOrder->clone()); // adding to inprocessorders now because we changed the order's status, might need to put Order o* = new Order(pendingOrder) inside<=========, because erase deletes, so it won't delete our order(so we want to use the copy constructor)
        // //                     // wareHouse.getPendingOrders().erase(wareHouse.getPendingOrders().begin() + pendOrd_index); // remove because the order moved to the inprocessorders vector
        // //                     // delete *iter;
        // //                     // iter = wareHouse.getPendingOrders().erase(iter);  // iterator
        // //                     // iter = vector<Order*>::reverse_iterator(wareHouse.getPendingOrders().erase(next(iter).base()));   // reverse iterator
        //                     delete pendingOrder;
        //                     pendingOrder = nullptr;
        //                     wareHouse.getPendingOrders().at(0) = nullptr;   //  <<<<<<========================================  testing
        //                     // wareHouse.getPendingOrders().erase(wareHouse.getPendingOrders().begin() + pendOrd_index); // remove because the order moved to the inprocessorders vector
        //                     // pendingOrder = ord_in_del;
        //                     indicesToRemove.push_back(indice);
        //                     indice++;
        //                     break;
        //                     // pendingOrder = nullptr;  // <<<<<<<<<===============================================  this gives a segmentation fault right now !!!!!!
                            
        //                 } // now gave the already collected order to a driver if a driver is free
        //             }
        //         }else{
        //             pendOrd_index ++;
        //             indice++;
        // //             // ++iter;
        //         }
        //     }

        //     // cout << " pendordssizebeshr ";
        //     // cout << wareHouse.getPendingOrders().size();    //  <<<<===================  test

        //     // for (int i = indicesToRemove.size() - 1; i >= 0; --i) {
        //     //     wareHouse.getPendingOrders().erase(wareHouse.getPendingOrders().begin() + indicesToRemove.at(i));
        //     // }

        //     //  erase-remove idiom:
        //     // wareHouse.getPendingOrders().erase(remove(wareHouse.getPendingOrders().begin(), wareHouse.getPendingOrders().end(), nullptr), wareHouse.getPendingOrders().end());


        //     // cout << wareHouse.getPendingOrders().size();    //  <<<<===================  test
        //     // cout << " pendordssizeafshr ";

        // //     cout << " after pendings ";   //  <<<<<<================================  test

        // //     // int k=0;
        // //     // while(wareHouse.getPendingOrders().at(k) == nullptr){
        // //     //     wareHouse.getPendingOrders().erase(wareHouse.getPendingOrders().begin() + k);
        // //     //     k++;
        // //     // }

            
        // //     for(int h=0; h < static_cast<int>(wareHouse.getPendingOrders().size()); h++){
        // //         if(wareHouse.getPendingOrders().at(h) != Order*){                                                                      # important #
        // //             wareHouse.getPendingOrders().erase(wareHouse.getPendingOrders().begin() + h); /// maybe if this gives a segmentation fault, remove instead of erase and then shrink
        // //             h--;
        // //         }
        //     // }

        // }        //                         copied until here to handleOrdersInStep





        // wareHouse.handleVolunteers()  //   add to WareHouse class    <<<<<<<<<<<<<<<<<<=====================================================  TO DO !!!!!!!!  <<<<=====================


        // if(wareHouse.getVolunteers().size() > 0){
        //     //  also take care of moving orders from one vector to another   <<<============
        //     pos_v = 0;
        //     int in_proc_Ord_index;
        //     for(Volunteer* volunteer : wareHouse.getVolunteers()){
        //         if(volunteer->isBusy()){  // doing the step is relavent only if he is given a task
        //             volunteer->step();
        //         }

        //         if((volunteer->isBusy() == false) && (volunteer->getCompletedOrderId()!= NO_ORDER)){  // if the volunteer finished his task
        //             Order* o = new Order(wareHouse.getOrder(volunteer->getCompletedOrderId()));  // using default copy constructor, this is the order the volunteer just finished processing
        //             if(volunteer->get_vol_identifier() == "c"){
        //                 o->setStatus(OrderStatus::PENDING); // from what nir said it should be in pending again because it's waiting for a driver to pick it up
        //                 // then move the order to the relavent vector
        //             }else if(volunteer->get_vol_identifier() == "d"){
        //                 o->setStatus(OrderStatus::COMPLETED);
        //             }
        //             wareHouse.addOrder(o); // adding to pendingorders/completedorders(depends on the status we changed to) now

        //             in_proc_Ord_index = 0;
        //             for(Order* ord: wareHouse.getInProcessOrders()){  // delete copied order and erase it's place
        //                 if(ord->getId() == o->getId()){
        //                     delete ord;  // might need to delete this  <<<<================================
        //     //                 wareHouse.getInProcessOrders().erase(wareHouse.getInProcessOrders().begin() + in_proc_Ord_index); // remove because the order moved to the pending/completedorders vector
        //     //                 break; // there's only one order with that order id so let's save time
        //                 }else{
        //                     in_proc_Ord_index ++;
        //                 }
        //             }

        //     //         volunteer->setCompletedOrderId(NO_ORDER);  // change the completedOrderId of the volunteer back to NO_ORDER
        //         }


        //         if(volunteer->hasOrdersLeft() == false && volunteer->isBusy() == false){   //  check which limited volunteers have finished and reached their max and delete them   <<<============
        //     //         delete volunteer;  // might need to delete this  <<<<================================
        //     //         // see if this is ok   <<<<==================================
        //     //         wareHouse.getVolunteers().erase(wareHouse.getVolunteers().begin() + pos_v);  //  delete and organize the vector(vector volunteers)
        //         }else{
        //             pos_v ++;
        //         }

        //     }
        // }






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

