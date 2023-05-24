#ifndef __RENTAL_PROPERTY_H__
#define __RENTAL_PROPERTY_H__

#include "rental_user.h"
#include <iostream>
#include <string>
#include <vector>

class RentalContract;
class RentalProperty;

class RentalRoom
{
    friend class RentalManagerment;

public:
    enum class RoomType {
        NORMAL = 0,
        SPECICAL,
        VIP,
    };

    class Accessory
    {
    private:
        std::string accessoryName;
        double p;
        double c;

    public:
        Accessory(const std::string &name, double count, double accessoryPrice = 0) :
            accessoryName(name), c(count), p(accessoryPrice) {}

        std::string name() const { return accessoryName; }
        double price() const { return p; }
        double count() const { return c; }

        void info() const {
            std::cout << "Accessory Name: " << accessoryName << std::endl;
            std::cout << "Price: $" << p << std::endl;
        }
    };

    class Utilities
    {
    private:
        std::string utilityName;
        double p;

    public:
        Utilities(const std::string &name, double utilityPrice) :
            utilityName(name), p(utilityPrice) {}

        std::string name() const { return utilityName; }
        double price() const { return p; }

        void info() const {
            std::cout << "Utility Name: " << utilityName << std::endl;
            std::cout << "Price: $" << p << std::endl;
        }
    };

private:
    int m_number;
    std::string m_name;
    /* before contract price */
    double m_price;
    mutable const RentalProperty *p;
    mutable const RentalContract *contract;
    mutable std::vector<RentalUser> rentalUsers;
    std::vector<Accessory> m_accessories;
    std::vector<Utilities> m_utilities;
    RoomType roomType;

public:
    RentalRoom(const RentalProperty *prop, int num, const std::string &name, RoomType type, double price) :
        p(prop), m_number(num), roomType(type), m_price(price), m_name(name), contract(NULL) {}

    int number() const { return m_number; }

    std::string name() const { return m_name; }

    RoomType type() const { return roomType; }

    double price() const;

    void setPrice(double p);

    bool rented() const;

    void addAccessory(const Accessory &accessory) { m_accessories.push_back(accessory); }

    void addUtility(const Utilities &utility) { m_utilities.push_back(utility); }

    std::vector<Accessory> accessories() { return m_accessories; }

    std::vector<Utilities> utilities() { return m_utilities; }

    const std::vector<RentalUser> &users() const { return rentalUsers; }

    void addRentalUser(const RentalUser &user) { rentalUsers.push_back(user); }

    const RentalProperty *property() const { return p; }

    const RentalContract *currentContract() const { return contract; }

    void rent(const RentalContract *ct, const std::vector<RentalUser> &users) const;

    double totalRent() const;

    void info() const;
};

class RentalProperty
{
    friend class RentalManagement;

private:
    std::string propertyName;
    std::vector<RentalRoom> m_rooms;
    std::string m_address;
    std::string m_owner;

public:
    RentalProperty(const std::string &name, const std::string &owner) :
        propertyName(name), m_owner(owner) {}

    std::string name() const { return propertyName; }

    void addRoom(const RentalRoom &room) { m_rooms.push_back(room); }

    std::string address() const { return m_address; }

    std::string owner() const { return m_owner; }

    const RentalRoom *findRoom(int number) const {
        for (int i = 0; i < m_rooms.size(); i++) {
            if (m_rooms[i].number() == number) {
                return &m_rooms[i];
            }
        }
        return NULL;
    }

    const std::vector<RentalRoom> &rooms() const { return m_rooms; }

    void info() const;
};

#endif // __RENTAL_PROPERTY_H__