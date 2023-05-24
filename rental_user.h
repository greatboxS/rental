#ifndef __RENTAL_USER_H__
#define __RENTAL_USER_H__

#include <iostream>
#include <string>

class RentalRoom;
class RentalContract;

class RentalUser
{
private:
    std::string m_userName;
    std::string m_email;
    std::string dateOfBirth;
    std::string m_address;
    std::string m_phone;
    const RentalRoom *m_room;
    const RentalContract *m_contract;
    int m_age;

public:
    RentalUser(const std::string &name, const std::string &userEmail, int userAge,
               const std::string &dob, const std::string &userAddress,
               const std::string &userPhone) :
        m_userName(name),
        m_email(userEmail), m_age(userAge), dateOfBirth(dob),
        m_address(userAddress), m_phone(userPhone),
        m_room(NULL), m_contract(NULL) {}

    std::string name() const { return m_userName; }
    std::string email() const { return m_email; }
    std::string birthday() const { return dateOfBirth; }
    std::string address() const { return m_address; }
    std::string phone() const { return m_phone; }
    int age() const { return m_age; }
    const RentalRoom *room() const { return m_room; }
    const RentalContract *contract() const { return m_contract; }
    void rent(const RentalContract *contract, const RentalRoom *room);
    void info() const;
};
#endif // __RENTAL_USER_H__