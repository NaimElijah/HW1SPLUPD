#include "../include/WareHouse.h"
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>
#include "../include/Order.h"
using namespace std;

WareHouse::WareHouse(const string& configFilePath):isOpen(false), backedUp(false), actionsLog(), pendingOrders(), inProcessOrders(), completedOrders(), volunteers(), customers(),
 customerCounter(0), volunteerCounter(0), ordersCounter(0), notfV(new CollectorVolunteer(-1, "not found", -1)), notfC(new SoldierCustomer(-1,"not found", -1,-1)), 
 notfO(new Order(-1,-1,-1)) {
	
	InputFromFile(configFilePath);
	
};









WareHouse::WareHouse(const WareHouse& wh): isOpen(wh.isOpen), backedUp(wh.backedUp), actionsLog(), pendingOrders(), inProcessOrders(), completedOrders(), volunteers(), customers(), 
 customerCounter(wh.customerCounter), volunteerCounter(wh.volunteerCounter), ordersCounter(wh.ordersCounter), notfV(wh.getNotfV().clone()), notfC(wh.getNotfC().clone()), 
 notfO(wh.getNotfO().clone()){   //  copy constructor

	for (Action* ac : wh.getActions()) {  // assignment
		actionsLog.push_back(ac->clone());
	}

	for (Volunteer* vol : wh.getVolunteers()) {
		volunteers.push_back(vol->clone());
	}

	for (Customer* cus : wh.getCustomers()) {
		customers.push_back(cus->clone());
	}

	for (Order* ord : wh.getPendingOrders()) {
		pendingOrders.push_back(ord->clone());
	}
		
	for (Order* ord : wh.getInProcessOrders()) {
		inProcessOrders.push_back(ord->clone());
	}
			
	for (Order* ord : wh.getCompletedOrders()) {
		completedOrders.push_back(ord->clone());
	}

}








WareHouse& WareHouse::operator=(const WareHouse& other){ // copy assignment operator(=)

	if(this != &other){
		isOpen = other.isOpen;
        customerCounter = other.getCustomerCounter();
        volunteerCounter = other.getVolunteerCounter();
		ordersCounter = other.getOrdersCounter();
		backedUp = other.backedUp;
		delete notfV;
		delete notfC;
		delete notfO;

		for (Action* ac : this->getActions()) {  // deletion
			delete ac;
			ac = nullptr;
		}

		for (Volunteer* vol : this->getVolunteers()) {
			delete vol;
			vol = nullptr;
		}

		for (Customer* cus : this->getCustomers()) {
			delete cus;
			cus = nullptr;
		}

		for (Order* ord : this->getPendingOrders()) {
			delete ord;
			ord = nullptr;
		}
		
		for (Order* ord : this->getInProcessOrders()) {
			delete ord;
			ord = nullptr;
		}
			
		for (Order* ord : this->getCompletedOrders()) {
			delete ord;
			ord = nullptr;
		}

		actionsLog.clear();
		volunteers.clear();
		customers.clear();       //  clearing  the vectors
		inProcessOrders.clear();
    	completedOrders.clear();
    	pendingOrders.clear();

		for (Action* ac : other.getActions()) {  // assignment
			actionsLog.push_back(ac->clone());
		}

		for (Volunteer* vol : other.getVolunteers()) {
			volunteers.push_back(vol->clone());
		}

		for (Customer* cus : other.getCustomers()) {
			customers.push_back(cus->clone());
		}

		for (Order* ord : other.getPendingOrders()) {
			pendingOrders.push_back(ord->clone());
		}
		
		for (Order* ord : other.getInProcessOrders()) {
			inProcessOrders.push_back(ord->clone());
		}
			
		for (Order* ord : other.getCompletedOrders()) {
			completedOrders.push_back(ord->clone());
		}
		notfV = other.getNotfV().clone();  // even though they have the same one, just because
		notfC = other.getNotfC().clone();
		notfO = other.getNotfO().clone();

	}
	return *this;
}











WareHouse& WareHouse::operator=(WareHouse&& other) noexcept {   //   move assignment operator

	if(this != &other){
		delete notfV;
		delete notfC;
		delete notfO;

    	for (Action* ac : this->getActions()) {  // deletion
			delete ac;
			ac = nullptr;
		}

		for (Volunteer* vol : this->getVolunteers()) {
			delete vol;
			vol = nullptr;
		}

		for (Customer* cus : this->getCustomers()) {
			delete cus;
			cus = nullptr;
		}

		for (Order* ord : this->getPendingOrders()) {
			delete ord;
			ord = nullptr;
		}
		
		for (Order* ord : this->getInProcessOrders()) {
			delete ord;
			ord = nullptr;
		}
			
		for (Order* ord : this->getCompletedOrders()) {
			delete ord;
			ord = nullptr;
		}


		actionsLog.clear();
		volunteers.clear();
		customers.clear();       //  clearing  the vectors
		inProcessOrders.clear();
    	completedOrders.clear();
    	pendingOrders.clear();

    	isOpen = other.isOpen;
		other.isOpen = false;

    	customerCounter = other.getCustomerCounter();
		other.setCustomerCounter(0);
    	volunteerCounter = other.getVolunteerCounter();
		other.setVolunteerCounter(0);
		ordersCounter = other.getOrdersCounter();
		other.setOrdersCounter(0);

    	notfV = other.getNotfV().clone();  // even though they have the same one, just because
		delete other.notfV;

		notfC = other.getNotfC().clone();  // even though they have the same one, just because
		delete other.notfC;

		notfO = other.getNotfO().clone();  // even though they have the same one, just because
		delete other.notfO;

		other.notfV = nullptr;
		other.notfC = nullptr;
		other.notfO = nullptr;

		backedUp = other.getBackedUp();
		other.backedUp = false;

	 	for (Action* ac : other.getActions()) {   ///   assignment to the lvalue(this) and nullptr'ing the rvalue(the other)
        	actionsLog.push_back(ac->clone());
			delete ac;
       		ac = nullptr;
    	}
		
		for (Volunteer* vol : other.getVolunteers()) {
        	volunteers.push_back(vol->clone());
			delete vol;
       		vol = nullptr;
    	}

		for (Customer* cus : other.getCustomers()) {
        	customers.push_back(cus->clone());
        	delete cus;
			cus = nullptr;
    	}

    	for (Order* ord : other.getInProcessOrders()) {
        	inProcessOrders.push_back(ord->clone());
			delete ord;
       		ord = nullptr;
    	}

    	for (Order* ord : other.getPendingOrders()) {
        	pendingOrders.push_back(ord->clone());
			delete ord;
       		ord = nullptr;
    	}
    	
    	for (Order* ord : other.getCompletedOrders()) {
        	completedOrders.push_back(ord->clone());
			delete ord;
       		ord = nullptr;
    	}

		other.actionsLog.clear();
		other.getVolunteers().clear();
		other.getCustomers().clear();       //  clearing the other's vectors
		other.getInProcessOrders().clear(); 
    	other.getCompletedOrders().clear();
    	other.getPendingOrders().clear();

	}
    return *this;
}










WareHouse::WareHouse(WareHouse&& other) noexcept: isOpen(other.isOpen), backedUp(other.backedUp), actionsLog(), pendingOrders(), inProcessOrders(), completedOrders(), volunteers(), customers(), 
 customerCounter(other.getCustomerCounter()), volunteerCounter(other.getVolunteerCounter()), ordersCounter(other.getOrdersCounter()), notfV(other.getNotfV().clone()), notfC(other.getNotfC().clone()), 
 notfO(other.getNotfO().clone()){   /// move constructor

	other.isOpen = false;
	other.setCustomerCounter(0);
	other.setVolunteerCounter(0);
	other.setOrdersCounter(0);

	delete other.notfV;
	other.notfV = nullptr;

	delete other.notfC;
	other.notfC = nullptr;

	delete other.notfO;
	other.notfO = nullptr;

	other.backedUp = false;
	

	for (Action* ac : other.getActions()) {   ///   assignment to the lvalue(this) and nullptr'ing the rvalue(the other)
        actionsLog.push_back(ac->clone());
		delete ac;
       	ac = nullptr;
    }
		
	for (Volunteer* vol : other.getVolunteers()) {
        volunteers.push_back(vol->clone());
		delete vol;
       	vol = nullptr;
    }

	for (Customer* cus : other.getCustomers()) {
        customers.push_back(cus->clone());
		delete cus;
        cus = nullptr;
    }

    for (Order* ord : other.getInProcessOrders()) {
        inProcessOrders.push_back(ord->clone());
		delete ord;
       	ord = nullptr;
    }

    for (Order* ord : other.getPendingOrders()) {
        pendingOrders.push_back(ord->clone());
		delete ord;
       	ord = nullptr;
    }
    	
    for (Order* ord : other.getCompletedOrders()) {
        completedOrders.push_back(ord->clone());
		delete ord;
       	ord = nullptr;
    }

	other.actionsLog.clear();
	other.getVolunteers().clear();
	other.getCustomers().clear();       //  clearing the other's vectors
	other.getInProcessOrders().clear(); 
    other.getCompletedOrders().clear();
    other.getPendingOrders().clear();

}












WareHouse::~WareHouse(){     ///  Destructor

	for(Action* a: actionsLog){  //  delete actionsLog
		delete a;
		a = nullptr;
	}
	actionsLog.clear();

	for(Order* o: pendingOrders){  //  delete pendingOrders
		delete o;
		o = nullptr;
	}
	pendingOrders.clear();

	for(Order* o: inProcessOrders){  //  delete inProcessOrders
		delete o;
		o = nullptr;
	}
	inProcessOrders.clear();

	for(Order* o: completedOrders){  //  delete completedOrders
		delete o;
		o = nullptr;
	}
	completedOrders.clear();

	for(Customer* c: customers){  //  delete customers
		delete c;
		c = nullptr;
	}
	customers.clear();

	for(Volunteer* v: volunteers){  //  delete volunteers
		delete v;
		v = nullptr;
	}
	volunteers.clear();

	delete notfV;
	notfV = nullptr;

	delete notfC;
	notfC = nullptr;

	delete notfO;
	notfO = nullptr;
	// we don't need to delete the backup, according to nir the backup survives even after the WareHouse is destroyed and then it's destroyed in the main
}










void WareHouse::InputFromFile(const string& configFilePath){            //             <=================================================  input from configFile
	string line;
    ifstream file(configFilePath);
    if (file.is_open()){

		vector<string> strin_s;  // 0 - type , 1 - name, and for each other argument, it depends on the person
		//  in vector because this way this will be flexible for each type of person

        while (getline(file, line)) {                          // <======= iterating the lines in the file  <=======

			string str; // each word will be in here when we iterate over the line
			stringstream s(line);    // s is an object of stringstream that references the S string.

			while (getline(s, str, ' ')){   ///     getting all the current line's arguments into a vector
				strin_s.push_back(str);
			}

			/// now building the person according to the line we got into strin_s: (below)
			if(strin_s.size() >= 3){
				if(strin_s.at(2) == "soldier"){  // SoldierCustomer
					addCustomer(new SoldierCustomer(customerCounter, strin_s.at(1), stoi(strin_s.at(3)), stoi(strin_s.at(4))));
				}else if(strin_s.at(2) == "civilian"){  // CivilianCustomer
					addCustomer(new CivilianCustomer(customerCounter, strin_s.at(1), stoi(strin_s.at(3)), stoi(strin_s.at(4))));

				}else if(strin_s.at(2) == "collector"){  // CollectorVolunteer
					addVolunteer(new CollectorVolunteer(volunteerCounter, strin_s.at(1), stoi(strin_s.at(3))));
				}else if(strin_s.at(2) == "limited_collector"){  // LimitedCollectorVolunteer
					addVolunteer(new LimitedCollectorVolunteer(volunteerCounter, strin_s.at(1), stoi(strin_s.at(3)), stoi(strin_s.at(4))));
				}else if(strin_s.at(2) == "driver"){  // DriverVolunteer
					addVolunteer(new DriverVolunteer(volunteerCounter, strin_s.at(1), stoi(strin_s.at(3)), stoi(strin_s.at(4))));
				}else if(strin_s.at(2) == "limited_driver"){  // LimitedDriverVolunteer
					addVolunteer(new LimitedDriverVolunteer(volunteerCounter, strin_s.at(1), stoi(strin_s.at(3)), stoi(strin_s.at(4)), stoi(strin_s.at(5))));
				}
			}
			
			strin_s.clear();
        }

		///   no need to delete the vectors because they are on the stack as well as their interior variables
    }

	file.close();
}


bool WareHouse::is_Open() const{
	return isOpen;
}


void WareHouse::start(){
	open();
	string user_input;
	vector<string> input_parts;

    while (is_Open()){
		getline(cin, user_input);

		string str;  // each word will be in here when we iterate over the line
		stringstream s(user_input);    // s is an object of stringstream that references the S string.
		input_parts.clear();  // reseting the vector for the incoming new line


		while (getline(s, str, ' ')){                     // <======= saving the input parts <=======
		    input_parts.push_back(str);
		}


		///            Now making the actions according to the Command we got
		if(input_parts.at(0) == "step"){
			SimulateStep* step = new SimulateStep(stoi(input_parts.at(1)));
			step->act(*(this));
			actionsLog.push_back(step);

		}else if(input_parts.at(0) == "order"){
			AddOrder* o = new AddOrder(stoi(input_parts.at(1)));
			o->act(*(this));
			actionsLog.push_back(o);

		}else if(input_parts.at(0) == "customer"){
			AddCustomer* customer = new AddCustomer(input_parts.at(1), input_parts.at(2), stoi(input_parts.at(3)), stoi(input_parts.at(4)));
			customer->act(*(this));
			actionsLog.push_back(customer);

		}else if(input_parts.at(0) == "orderStatus"){
			PrintOrderStatus* pri_ord_sta = new PrintOrderStatus(stoi(input_parts.at(1)));
			pri_ord_sta->act(*(this));
			actionsLog.push_back(pri_ord_sta);

		}else if(input_parts.at(0) == "customerStatus"){
			PrintCustomerStatus* pri_cus_sta = new PrintCustomerStatus(stoi(input_parts.at(1)));
			pri_cus_sta->act(*(this));
			actionsLog.push_back(pri_cus_sta);

		}else if(input_parts.at(0) == "volunteerStatus"){
			PrintVolunteerStatus* pri_vol_sta = new PrintVolunteerStatus(stoi(input_parts.at(1)));
			pri_vol_sta->act(*(this));
			actionsLog.push_back(pri_vol_sta);

		}else if(input_parts.at(0) == "log"){
			PrintActionsLog* pri_act_log = new PrintActionsLog();
			pri_act_log->act(*(this));
			actionsLog.push_back(pri_act_log);

		}else if(input_parts.at(0) == "close"){
			Close* clo = new Close();
			clo->act(*(this));
			actionsLog.push_back(clo); // the WareHouse is closing, but we still add this so it will be deleted alongside the other actions

		}else if(input_parts.at(0) == "backup"){
			BackupWareHouse* bac_up_wa = new BackupWareHouse();
			bac_up_wa->act(*(this));
			actionsLog.push_back(bac_up_wa);

		}else if(input_parts.at(0) == "restore"){
			RestoreWareHouse* res_wa = new RestoreWareHouse();
			res_wa->act(*(this));
			actionsLog.push_back(res_wa);

		}


    }

}



Volunteer& WareHouse::getNotfV() const{
	return *(notfV);
}

Customer& WareHouse::getNotfC() const{
	return *(notfC);
}

Order& WareHouse::getNotfO() const{
	return *(notfO);
}

int WareHouse::getCustomerCounter() const{
	return customerCounter;
}
void WareHouse::setCustomerCounter(int i){
	customerCounter = i;
}

int WareHouse::getVolunteerCounter() const{
	return volunteerCounter;
}
void WareHouse::setVolunteerCounter(int i){
	volunteerCounter = i;
}

int WareHouse::getOrdersCounter()const{
	return ordersCounter;
}
void WareHouse::setOrdersCounter(int i){
	ordersCounter = i;
}


void WareHouse::changeBackedUp(){
	backedUp = !backedUp;
}
bool WareHouse::getBackedUp(){
	return backedUp;
}








void WareHouse::handleOrders(){
	if(pendingOrders.size() > 0){
        for(int i=0; i< static_cast<int>(pendingOrders.size()); i++){
            // go over all the collectors and see who is available   <<<============
            if(pendingOrders.at(i)->getStatus() == OrderStatus::PENDING){  // assigning a new order to a collector.
                for(Volunteer* vol : volunteers){
                    if(vol->get_vol_identifier() == "c" && vol->canTakeOrder(*(pendingOrders.at(i)))){
                        pendingOrders.at(i)->setCollectorId(vol->getId());
                        vol->acceptOrder(*(pendingOrders.at(i)));   ///    do a clone to Order and add a clone when giving it to the next place and delete the old
                        pendingOrders.at(i)->setStatus(OrderStatus::COLLECTING);

						Order* o1;
						o1 = new Order(*(pendingOrders.at(i))); // using default copy constructor
                        addOrder(o1); // adding to inprocessorders now because we changed the order's status, tried giving the clone as well

						delete pendingOrders.at(i);
                        pendingOrders.erase(pendingOrders.begin() + i); // remove because the order moved to the inprocessorders vector
                        i--;
                        break;
                    } // now gave the new order to a collector if a collector is free
                }

			}else{ // if  ====>> (pendingOrders.at(i)->getStatus() == OrderStatus::COLLECTING)
                for(Volunteer* vol : volunteers){
                    if(vol->get_vol_identifier() == "d" && vol->canTakeOrder(*(pendingOrders.at(i)))){
                        pendingOrders.at(i)->setDriverId(vol->getId());
                        vol->acceptOrder(*(pendingOrders.at(i)));
                        pendingOrders.at(i)->setStatus(OrderStatus::DELIVERING);

						Order* o2;
						o2 = new Order(*(pendingOrders.at(i))); // using default copy constructor
                        addOrder(o2); // adding to inprocessorders now because we changed the order's status, tried giving the clone as well

						delete pendingOrders.at(i);
                        pendingOrders.erase(pendingOrders.begin() + i); // remove because the order moved to the inprocessorders vector
                        i--;
                        break;
                    } // now gave the already collected order to a driver if a driver is free
                }
            }
        }
    }
	
}










void WareHouse::handleVolunteers(){
	if(volunteers.size() > 0){
			for(int i=0; i< static_cast<int>(volunteers.size()); i++){  // going over the volunteers
				
                if(volunteers.at(i)->isBusy()){  // doing the step is relavent only if he is given a task
                    volunteers.at(i)->step();
                }

                if((volunteers.at(i)->isBusy() == false) && (volunteers.at(i)->getCompletedOrderId()!= NO_ORDER)){  // if the volunteer finished his task
                    Order* o;
					o = new Order(getOrder(volunteers.at(i)->getCompletedOrderId()));  // using default copy constructor, this is the order the volunteer just finished processing
                    if(volunteers.at(i)->get_vol_identifier() == "c"){
                        getOrder(volunteers.at(i)->getCompletedOrderId()).setStatus(OrderStatus::PENDING); // from what nir said it should be in pending again because it's waiting for a driver to pick it up
                    }else if(volunteers.at(i)->get_vol_identifier() == "d"){
                        getOrder(volunteers.at(i)->getCompletedOrderId()).setStatus(OrderStatus::COMPLETED);
                    }

					addOrder(o);

					for(int j=0; j< static_cast<int>(inProcessOrders.size()); j++){  // erase copied order from inProcessOrders
                        if(inProcessOrders.at(j)->getId() == o->getId()){
							delete inProcessOrders.at(j); // or in the other way in git   <<<<<<=============================
                            inProcessOrders.erase(inProcessOrders.begin() + j); // remove because the order moved to the pending/completedorders vector
							j--; // not really needed because we are activating break, but still, just because.
							break; // we can break because there should only be one order with that id, only one order like that, so let's save a bit of time.
                        }
                    }
                    volunteers.at(i)->setCompletedOrderId(NO_ORDER);  // change the completedOrderId of the volunteer back to NO_ORDER
                }

                if(volunteers.at(i)->hasOrdersLeft() == false && volunteers.at(i)->isBusy() == false){   //  check which limited volunteers have finished and reached their max and delete them   <<<============
                    delete volunteers.at(i);
					volunteers.erase(volunteers.begin() + i);  //  delete and organize the vector(vector volunteers)
					i--;
                }

            }
        }

}







const vector<Action*>& WareHouse::getActions() const{
		return actionsLog;
}



void WareHouse::addOrder(Order* order){

	if(order->getStatus() == OrderStatus::PENDING){
		if(order->getCollectorId() != NO_VOLUNTEER){ // order finished processing at collector
			order->setStatus(OrderStatus::COLLECTING);
		}
		pendingOrders.push_back(order);
		if(order->getCollectorId() == NO_VOLUNTEER){ // in case it's a new order
			getCustomer(order->getCustomerId()).addOrder(ordersCounter);
			ordersCounter = ordersCounter + 1;
		}

	}else if(order->getStatus() == OrderStatus::COLLECTING || order->getStatus() == OrderStatus::DELIVERING){
		inProcessOrders.push_back(order);

	}else{  // status is OrderStatus::COMPLETED
		completedOrders.push_back(order);
	}
}

void WareHouse::addAction(Action* action){
	actionsLog.push_back(action);
}

void WareHouse::addVolunteer(Volunteer* volunteer){
	volunteers.push_back(volunteer);
	volunteerCounter = volunteerCounter + 1;
}


void WareHouse::addCustomer(Customer* customer){
	customers.push_back(customer);
	customerCounter = customerCounter + 1;
}



vector<Order*> WareHouse::getPendingOrders() const{
	return pendingOrders;
}
vector<Order*> WareHouse::getInProcessOrders() const{
	return inProcessOrders;
}
vector<Order*> WareHouse::getCompletedOrders() const{
	return completedOrders;
}

vector<Volunteer*> WareHouse::getVolunteers() const{
	return volunteers;
}
vector<Customer*> WareHouse::getCustomers() const{
	return customers;
}



Customer& WareHouse::getCustomer(int customerId) const{
	for(Customer* c : customers){
		if(c->getId() == customerId){
			return *(c);
		}
	}
	return *(notfC); // returns this if not found
}

Volunteer& WareHouse::getVolunteer(int volunteerId) const{
	for(Volunteer* v : volunteers){
		if(v->getId() == volunteerId){
			return *(v);
		}
	}
	return *(notfV); // returns this if not found
}

Order& WareHouse::getOrder(int orderId) const{
	for(Order* o : pendingOrders){
		if(o->getId() == orderId){
			return *(o);
		}
	}
	for(Order* o : inProcessOrders){
		if(o->getId() == orderId){
			return *(o);
		}
	}
	for(Order* o : completedOrders){
		if(o->getId() == orderId){
			return *(o);
		}
	}
	return *(notfO); // returns this if not found
}



void WareHouse::close(){
	// close the Warehouse
	isOpen = false;
	///   ===========================>>>>>>>>>>>  the destructor will automatically activate when the WareHouse in main goes out of scope, because the WareHouse in main is on the stack
}

void WareHouse::open(){
	/// open the Warehouse
	backedUp = false;
	isOpen = true;
	cout << "Warehouse is open!\n";
}

