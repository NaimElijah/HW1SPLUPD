#include "../include/WareHouse.h"
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>
using namespace std;

WareHouse::WareHouse(const string& configFilePath):isOpen(false), backedUp(false), actionsLog(), pendingOrders(), inProcessOrders(), completedOrders(), volunteers(), customers(),
 customerCounter(0), volunteerCounter(0), ordersCounter(0), notfV(new CollectorVolunteer(-1, "not found", -1)){
	
	InputFromFile(configFilePath);
	
};









WareHouse::WareHouse(const WareHouse& wh): isOpen(wh.isOpen), backedUp(wh.backedUp), actionsLog(), pendingOrders(), inProcessOrders(), completedOrders(), volunteers(), customers(), 
 customerCounter(wh.customerCounter), volunteerCounter(wh.volunteerCounter), ordersCounter(wh.ordersCounter), notfV(wh.getNotfV().clone()){   //  copy constructor

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

		for (Action* ac : this->getActions()) {  // deletion
			delete ac;
		}

		for (Volunteer* vol : this->getVolunteers()) {
			delete vol;
		}

		for (Customer* cus : this->getCustomers()) {
			delete cus;
		}

		for (Order* ord : this->getPendingOrders()) {
			delete ord;
		}
		
		for (Order* ord : this->getInProcessOrders()) {
			delete ord;
		}
			
		for (Order* ord : this->getCompletedOrders()) {
			delete ord;
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

	}
	return *this;
}











WareHouse& WareHouse::operator=(WareHouse&& other) noexcept {   //   move assignment operator

	if(this != &other){
		delete notfV;
    	for (Action* ac : this->getActions()) {  // deletion
			delete ac;
		}

		for (Volunteer* vol : this->getVolunteers()) {
			delete vol;
		}

		for (Customer* cus : this->getCustomers()) {
			delete cus;
		}

		for (Order* ord : this->getPendingOrders()) {
			delete ord;
		}
		
		for (Order* ord : this->getInProcessOrders()) {
			delete ord;
		}
			
		for (Order* ord : this->getCompletedOrders()) {
			delete ord;
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
		other.notfV = nullptr;
		backedUp = other.getBackedUp();
		other.backedUp = false;

	 	for (Action* ac : other.getActions()) {   ///   assignment to the lvalue(this) and nullptr'ing the rvalue(the other)
        	actionsLog.push_back(ac->clone());
       		ac = nullptr;
    	}
		
		for (Volunteer* vol : other.getVolunteers()) {
        	volunteers.push_back(vol->clone());
       		vol = nullptr;
    	}

		for (Customer* cus : other.getCustomers()) {
        	customers.push_back(cus->clone());             //                    check in nir's ps if we should delete or only = nullptr it.   <<<<<============================
        	cus = nullptr;
    	}

    	for (Order* ord : other.getInProcessOrders()) {
        	inProcessOrders.push_back(ord->clone());
       		ord = nullptr;
    	}

    	for (Order* ord : other.getPendingOrders()) {
        	pendingOrders.push_back(ord->clone());
       		ord = nullptr;
    	}
    	
    	for (Order* ord : other.getCompletedOrders()) {
        	completedOrders.push_back(ord->clone());
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
 customerCounter(other.getCustomerCounter()), volunteerCounter(other.getVolunteerCounter()), ordersCounter(other.getOrdersCounter()), notfV(other.getNotfV().clone()){   /// move constructor

	other.isOpen = false;
	other.setCustomerCounter(0);
	other.setVolunteerCounter(0);
	other.setOrdersCounter(0);
	other.notfV = nullptr;
	other.backedUp = false;
	

	for (Action* ac : other.getActions()) {   ///   assignment to the lvalue(this) and nullptr'ing the rvalue(the other)
        actionsLog.push_back(ac->clone());
       	ac = nullptr;
    }
		
	for (Volunteer* vol : other.getVolunteers()) {
        volunteers.push_back(vol->clone());
       	vol = nullptr;
    }

	for (Customer* cus : other.getCustomers()) {
        customers.push_back(cus->clone());
        cus = nullptr;
    }

    for (Order* ord : other.getInProcessOrders()) {
        inProcessOrders.push_back(ord->clone());
       	ord = nullptr;
    }

    for (Order* ord : other.getPendingOrders()) {
        pendingOrders.push_back(ord->clone());
       	ord = nullptr;
    }
    	
    for (Order* ord : other.getCompletedOrders()) {
        completedOrders.push_back(ord->clone());
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
	}
	actionsLog.clear();

	for(Order* o: pendingOrders){  //  delete pendingOrders
		delete o;
	}
	pendingOrders.clear();

	for(Order* o: inProcessOrders){  //  delete inProcessOrders
		delete o;
	}
	inProcessOrders.clear();

	for(Order* o: completedOrders){  //  delete completedOrders
		delete o;
	}
	completedOrders.clear();

	for(Customer* c: customers){  //  delete customers
		delete c;
	}
	customers.clear();

	for(Volunteer* v: volunteers){  //  delete volunteers
		delete v;
	}
	volunteers.clear();

	delete notfV;
	// we don't need to delete the backup, according to nir the backup survives even after the WareHouse is destroyed and then it's destroyed in the main
}










void WareHouse::InputFromFile(const string& configFilePath){            //             <=================================================  input from configFile
	string line;
    ifstream file(configFilePath);
    if (file.is_open()) {

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
		cout << "enter a command: ";
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
			// actionsLog.push_back(clo); // the WareHouse is closing so we don't want to add this because we're deleting the contents of every vector as well

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




const vector<Action*>& WareHouse::getActions() const{
		return actionsLog;
}



void WareHouse::addOrder(Order* order){
	if(order->getStatus() == OrderStatus::PENDING){
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
vector<Order*> WareHouse::getInProcessOrders() const{  // try and put these as const
	return inProcessOrders;
}
vector<Order*> WareHouse::getCompletedOrders() const{
	return completedOrders;
}

vector<Volunteer*> WareHouse::getVolunteers() const{  // try and put these as const
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
	return *(new SoldierCustomer(-1, "won't reach this new SoldierCustomer", -1, -1));
}  // the compiler has a problem if we don't return anything here so we're returning something even though it won't reach here because before we activate this get, we check if a 
                                                                                                             // customer exists, so it's also good that this Customer won't be created

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
	return *(new Order(-1, -1, -1));
}  // the compiler has a problem if we don't return anything here so we're returning something even though it won't reach here because before we activate this get, we check if an 
                                                                                                             // order exists, so it's also good that this Order won't be created



void WareHouse::close(){
	// close the Warehouse
	isOpen = false;
	//  from what I gathered, the destructor is automatically activated when the WareHouse instance is on the stack and is out of scope, but still activate the destructor here 
	//                                                                                                                            for the case that the instance is on the heap
	// delete *this;  // using the destructor        no need (explanation below)
	///   ===========================>>>>>>>>>>>  the destructor will automatically activate when the WareHouse in main goes out of scope, becasue the WareHouse in main is on the stack

}

void WareHouse::open(){
	/// open the Warehouse
	backedUp = false;
	isOpen = true;
	cout << "Warehouse is open!\n";
}

