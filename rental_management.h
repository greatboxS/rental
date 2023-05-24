#ifndef __RENTAL_MANAGERMENT_H__
#define __RENTAL_MANAGERMENT_H__

#include "rental_property.h"
#include <chrono>
#include <iomanip>
#include <map>

class RentalContractPrice
{
private:
    std::map<std::string, double> prices;

public:
    RentalContractPrice &add(std::string type, double unitPrice) {
        prices[type] = unitPrice;
        return *this;
    }

    const std::map<std::string, double> holder() const { return prices; }
};

class RentalContract
{
    friend class RentalManagerment;

private:
    const RentalRoom *m_room;
    const RentalProperty *p;
    std::vector<RentalUser> m_users;
    std::chrono::system_clock::time_point m_startDate;
    std::chrono::system_clock::time_point m_endDate;
    std::chrono::system_clock::time_point m_actualEndDate;
    int m_paymentDate;
    RentalContractPrice m_price;
    bool valid;
    std::string endReason;

public:
    RentalContract(const RentalRoom *room, const RentalProperty *prop, const std::vector<RentalUser> &users,
                   const std::chrono::system_clock::time_point &startDate,
                   const std::chrono::system_clock::time_point &endDate,
                   int payDate,
                   RentalContractPrice &p);

    std::string startDate() const;
    std::string endtDate() const;
    std::string actualEndtDate() const;
    int paymentDate() const;
    double duration() const; /* Day is returned */
    const RentalContractPrice &contractPrice() const;
    bool isValid() const;
    const RentalProperty *property() const;
    void endContract(const std::string &reason);
    void info() const;
};

class RentalBill
{
    friend class RentalManagement;

public:
    typedef struct {
        std::string name;
        double oldValue;
        double newValue;
        double amount;
        double unitPrice;
        double price;
    } Bill;

private:
    int m_id;
    static int billId;
    const RentalRoom *m_room;
    std::map<std::string, Bill> m_bills;
    std::chrono::system_clock::time_point m_date;
    std::chrono::system_clock::time_point m_paiedDate;
    double m_paied;

    int pay(double money);

public:
    RentalBill(const RentalRoom *room, const std::chrono::system_clock::time_point &date);

    RentalBill &addBill(const std::string &name, const Bill &bill);
    int id() const;
    double paied() const;
    double oweMoney() const;
    double total() const;
    std::string date() const;
    std::string paiedDate() const;
    const std::map<std::string, Bill> &bills() const;
    void info() const;
};

class RentalManagement
{
private:
    std::map<std::string, RentalProperty *> m_properties;
    std::vector<RentalContract> m_contracts;
    std::map<const RentalRoom *, std::vector<RentalBill>> m_payment;

public:
    ~RentalManagement() {
        for (auto i : m_properties) {
            delete i.second;
        }
    }

    void addProperty(const std::string &name, const std::string &owner, const std::vector<RentalRoom> &rooms);
    RentalProperty *getProperty(const std::string &name);
    void propertiesInfo() const;
    void contractInfo() const;
    void processRent(const RentalContract &contract) { m_contracts.push_back(contract); }
    const std::vector<RentalContract> &contracts() const { return m_contracts; }
    void processPayment(const RentalRoom *room, RentalBill &bill, double money);
    void updatePayment(const RentalRoom *room, int id, double money);
    const std::map<const RentalRoom *, std::vector<RentalBill>> &getBills() const { return m_payment; }
};

#endif // __RENTAL_MANAGERMENT_H__