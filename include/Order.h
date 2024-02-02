#pragma once

#include <string>
#include <vector>
using std::string;
using std::vector;


class Volunteer;

enum class OrderStatus {
    PENDING,
    COLLECTING,
    DELIVERING,
    COMPLETED,
};

#define NO_VOLUNTEER -1

class Order {
    public:
        Order(int id, int customerId, int distance);

        int getId() const;
        int getDistance() const;
        int getCustomerId() const;
        int getCollectorId() const;
        int getDriverId() const;
        OrderStatus getStatus() const;
        Order* clone() const;

        void setStatus(OrderStatus status);
        void setCollectorId(int collectorId);
        void setDriverId(int driverId);
        
        const string toString() const;

    private:
        const int id;
        const int customerId;
        const int distance;
        OrderStatus status;
        int collectorId;
        int driverId;
};