#include "rental_property.h"
#include "rental_management.h"

double RentalRoom::price() const {
    if (!contract) return m_price;
    return contract->contractPrice().holder().at("room");
}

void RentalRoom::setPrice(double p) { m_price = p; }

bool RentalRoom::rented() const {
    if (!contract) return false;
    return contract->isValid();
}

void RentalRoom::rent(const RentalContract *ct, const std::vector<RentalUser> &users) const {
    contract = ct;
    rentalUsers = users;
}

double RentalRoom::totalRent() const {
    double total = contract->contractPrice().holder().at("room");
    double electric = contract->contractPrice().holder().at("electric");
    double water = contract->contractPrice().holder().at("water");

    for (const auto &utility : m_utilities) {
        total += utility.price();
    }
    for (const auto &accessory : m_accessories) {
        if (accessory.name() == "electric") {
            total += accessory.count() * electric;
        } else if (accessory.name() == "water") {
            total += accessory.count() * water;
        } else {
        }
    }
    return total;
}

void RentalRoom::info() const {
    std::cout << "Room Number: " << m_number << std::endl;
    std::cout << "Room Type: " << (int)roomType << std::endl;
    std::cout << "Rent Amount: $" << m_price << std::endl;
    std::cout << "Occupied: " << (rented() ? "Yes" : "No") << std::endl;

    if (!rentalUsers.empty()) {
        std::cout << "Rental Users:\n";
        for (const auto &user : rentalUsers) {
            user.info();
            std::cout << std::endl;
        }
    } else {
        std::cout << "No Rental Users\n";
    }

    std::cout << "Accessories:\n";
    for (const auto &accessory : m_accessories) {
        accessory.info();
        std::cout << std::endl;
    }

    std::cout << "Utilities:\n";
    for (const auto &utility : m_utilities) {
        utility.info();
        std::cout << std::endl;
    }
}

void RentalProperty::info() const {
    std::cout << "Property Name: " << propertyName << std::endl;
    std::cout << "Property Address: " << m_address << std::endl;
    std::cout << "Number of Rooms: " << m_rooms.size() << std::endl;
    std::cout << "Rooms Information:\n";
    for (const auto &room : m_rooms) {
        room.info();
        std::cout << std::endl;
    }
}