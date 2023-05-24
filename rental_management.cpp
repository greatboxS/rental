#include "rental_management.h"
#include <assert.h>

int RentalBill::billId = 0;

RentalContract::RentalContract(const RentalRoom *room, const RentalProperty *prop, const std::vector<RentalUser> &users,
                               const std::chrono::system_clock::time_point &startDate,
                               const std::chrono::system_clock::time_point &endDate,
                               int payDate,
                               RentalContractPrice &p) :
    m_room(room),
    p(prop),
    m_users(users),
    m_startDate(startDate),
    m_endDate(endDate),
    m_paymentDate(payDate),
    m_price(p),
    m_actualEndDate(endDate), valid(true) {
    assert(room);

    for (auto &user : m_users) {
        user.rent(this, m_room);
    }
    m_room->rent(this, m_users);
}

std::string RentalContract::startDate() const {
    std::stringstream startDateStream;
    auto time = std::chrono::system_clock::to_time_t(m_startDate);
    startDateStream << std::put_time(std::localtime(&time), "%Y-%m-%d");
    return startDateStream.str();
}

std::string RentalContract::endtDate() const {
    std::stringstream endDateStream;
    auto time = std::chrono::system_clock::to_time_t(m_endDate);
    endDateStream << std::put_time(std::localtime(&time), "%Y-%m-%d");
    return endDateStream.str();
}

std::string RentalContract::actualEndtDate() const {
    std::stringstream actualEndDateStream;
    auto time = std::chrono::system_clock::to_time_t(m_actualEndDate);
    actualEndDateStream << std::put_time(std::localtime(&time), "%Y-%m-%d");
    return actualEndDateStream.str();
}

int RentalContract::paymentDate() const { return m_paymentDate; }

double RentalContract::duration() const {
    std::chrono::duration<double> duration = m_endDate - m_startDate;
    double days = std::chrono::duration_cast<std::chrono::hours>(duration).count() / 24.0;
    return days;
}

const RentalContractPrice &RentalContract::contractPrice() const { return m_price; }

bool RentalContract::isValid() const {
    std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
    std::chrono::duration<double> validityPeriod = m_endDate - currentTime;

    if (validityPeriod.count() <= 0 || !valid) {
        return false;
    } else {
        return true;
    }
}

const RentalProperty *RentalContract::property() const { return p; }

void RentalContract::endContract(const std::string &reason) {
    m_actualEndDate = std::chrono::high_resolution_clock::now();
    endReason = reason;
    valid = false;
}

void RentalContract::info() const {
    std::cout << "Contract Information\n";
    std::cout << "-------------------\n";
    std::cout << "Room Details:\n";
    m_room->info();
    std::cout << std::endl;
    std::cout << "Rental Users:\n";
    for (const auto &user : m_users) {
        user.info();
        std::cout << std::endl;
    }
    std::cout << "Start Date: " << startDate() << std::endl;
    std::cout << "End Date: " << endtDate() << std::endl;

    std::cout << "Contract Detail Prices:\n";
    for (auto p : m_price.holder()) {
        std::cout << "Type: " << p.first << ", price: " << p.second << std::endl;
    }

    std::chrono::duration<double> validityPeriod = m_endDate - m_startDate;
    int days = std::chrono::duration_cast<std::chrono::hours>(validityPeriod).count() / 24;

    if (validityPeriod.count() > 0) {
        std::cout << "Contract is valid for: " << days << " days" << std::endl;
    } else {
        std::cout << "Contract has expired" << std::endl;
    }
}

/**
 * @fn RentalBill::pay()
 * @brief
 *
 * @param money
 * @return int
 */
int RentalBill::pay(double money) {
    int owe = 0;
    if (m_paied + money < total()) {
        owe = 1;
    }
    m_paied = money;
    m_paiedDate = std::chrono::system_clock::now();
    return owe;
}

RentalBill::RentalBill(const RentalRoom *room, const std::chrono::system_clock::time_point &date) :
    m_room(room), m_paied(0.0), m_date(date), m_id(++billId) {
    m_bills.clear();

    /* Add the room price, the price is based on contract price */
    if (m_room) {
        if (room->currentContract()) {
            Bill roomBill = {
                "room",
                0,
                0,
                m_room->currentContract()->contractPrice().holder().at("room"),
                0,
                m_room->currentContract()->contractPrice().holder().at("room")};

            addBill("room", roomBill);
        }
    }
}

RentalBill &RentalBill::addBill(const std::string &name, const Bill &bill) {
    if (!m_room->rented()) {
        std::cout << "Room " << m_room->number() << " is not rented\n";
        return *this;
    }

    m_bills[name] = bill;
    return *this;
}

int RentalBill::id() const { return m_id; }

double RentalBill::paied() const { return m_paied; }

double RentalBill::oweMoney() const { return total() - paied(); }

double RentalBill::total() const {
    double total = 0.0;
    for (auto p : m_bills) {
        total += p.second.price;
    }
    return total;
}

std::string RentalBill::date() const {
    std::stringstream stream;
    auto time = std::chrono::system_clock::to_time_t(m_date);
    stream << std::put_time(std::localtime(&time), "%Y-%m-%d");
    return stream.str();
}

std::string RentalBill::paiedDate() const {
    std::stringstream stream;
    auto time = std::chrono::system_clock::to_time_t(m_paiedDate);
    stream << std::put_time(std::localtime(&time), "%Y-%m-%d");
    return stream.str();
}

const std::map<std::string, RentalBill::Bill> &RentalBill::bills() const { return m_bills; }

void RentalBill::info() const {
    std::cout << "\nBill Infomations:" << std::endl;
    std::cout << "Id: " << m_id << std::endl;
    std::cout << "Date: " << date() << std::endl;
    if (m_room)
        std::cout << "Room: " << m_room->name() << std::endl;
    std::cout << "Bill Detail Prices:\n";
    for (auto p : m_bills) {
        std::cout << "Types: " << p.first << ", price: " << p.second.price << std::endl;
    }
    std::cout << "Bill Total Price: " << total() << std::endl;
}

void RentalManagement::addProperty(const std::string &name, const std::string &owner, const std::vector<RentalRoom> &rooms) {
    RentalProperty *prop = new RentalProperty(name, owner);
    for (auto &i : rooms) {
        prop->addRoom(i);
    }

    m_properties[name] = prop;
}

RentalProperty *RentalManagement::getProperty(const std::string &name) {
    if (m_properties.find(name) == m_properties.end()) return NULL;
    return m_properties.at(name);
}

/**
 * @fn propertiesInfo
 * @brief
 *
 */
void RentalManagement::propertiesInfo() const {
    std::cout << "\nRental Properties\n";
    std::cout << "-----------------\n";
    for (const auto &property : m_properties) {
        property.second->info();
    }
    std::cout << std::endl;
}

void RentalManagement::contractInfo() const {
    std::cout << "\nRental Contracts\n";
    std::cout << "----------------\n";
    for (const auto &contract : m_contracts) {
        contract.info();
    }
    std::cout << std::endl;
}

void RentalManagement::processPayment(const RentalRoom *room, RentalBill &bill, double money) {
    if (!room) return;
    bill.pay(money);
    m_payment[room].push_back(bill);
}

void RentalManagement::updatePayment(const RentalRoom *room, int id, double money) {
    if (!room) return;
    if (m_payment.find(room) == m_payment.end()) return;

    for (auto i : m_payment[room]) {
        if (i.id() == id) {
            double owe = i.oweMoney();
            /* No owe money */
            if (owe == 0) return;
            i.pay(std::min(owe, money));
        }
    }
}