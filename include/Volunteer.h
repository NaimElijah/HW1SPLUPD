#pragma once
#include <string>
#include <vector>
#include "Order.h"
using std::string;
using std::vector;

#define NO_ORDER -1


class Volunteer {    //           <=================================================
    public:
        Volunteer(int id, const string& name);
        virtual ~Volunteer() = default;

        int getId() const;
        const string& getName() const;

        int getActiveOrderId() const;
        int getCompletedOrderId() const;
        void setActiveOrderId(int actId);
        void setCompletedOrderId(int comId);
        bool isBusy() const;
        string get_vol_identifier() const;
        void set_vol_identifier(string iden);

        virtual bool hasOrdersLeft() const = 0;
        virtual bool canTakeOrder(const Order& order) const = 0;     
        virtual void acceptOrder(const Order& order) = 0;
                
        virtual void step() = 0;

        virtual string toString() const = 0;
        virtual Volunteer* clone() const = 0;

    protected:
        int completedOrderId;
        int activeOrderId;
    
    private:
        const int id;
        const string name;
        string vol_identifier;

};











class CollectorVolunteer: public Volunteer {   //   <=================================================

    public:
        CollectorVolunteer(int id, const string& name, int coolDown);

        CollectorVolunteer* clone() const override;
        void step() override;
        int getCoolDown() const;
        int getTimeLeft() const;
        void setTimeLeft(int time);
        bool decreaseCoolDown();
        bool hasOrdersLeft() const override;
        bool canTakeOrder(const Order& order) const override;
        void acceptOrder(const Order& order) override;
        string toString() const override;
    
    private:
        const int coolDown;
        int timeLeft;
};






class LimitedCollectorVolunteer: public CollectorVolunteer {   //   <=================================================

    public:
        LimitedCollectorVolunteer(int id, const string& name, int coolDown ,int maxOrders);

        LimitedCollectorVolunteer* clone() const override;
        bool hasOrdersLeft() const override;
        bool canTakeOrder(const Order& order) const override;
        void acceptOrder(const Order& order) override;

        int getMaxOrders() const;
        int getNumOrdersLeft() const;
        void setNumOrdersLeft(int nol);
        string toString() const override;
    
    private:
        const int maxOrders;
        int ordersLeft;
};













class DriverVolunteer: public Volunteer {   //      <=================================================

    public:
        DriverVolunteer(int id, const string& name, int maxDistance, int distancePerStep);

        DriverVolunteer* clone() const override;
        int getDistanceLeft() const;
        int getMaxDistance() const;
        int getDistancePerStep() const;
        void setDistanceLeft(int distance);
        bool decreaseDistanceLeft();
        bool hasOrdersLeft() const override;
        bool canTakeOrder(const Order& order) const override;
        void acceptOrder(const Order& order) override;
        void step() override;
        string toString() const override;

    private:
        const int maxDistance;
        const int distancePerStep;
        int distanceLeft;
};







class LimitedDriverVolunteer: public DriverVolunteer {   //    <=================================================

    public:
        LimitedDriverVolunteer(int id, const string& name, int maxDistance, int distancePerStep,int maxOrders);
                
        LimitedDriverVolunteer* clone() const override;
        int getMaxOrders() const;
        int getNumOrdersLeft() const;
        void setNumOrdersLeft(int nol);
        bool hasOrdersLeft() const override;
        bool canTakeOrder(const Order& order) const override;
        void acceptOrder(const Order& order) override;
        string toString() const override;

    private:
        const int maxOrders;
        int ordersLeft;
};

