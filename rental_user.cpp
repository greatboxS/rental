#include "rental_user.h"
#include "rental_property.h"

void RentalUser::rent(const RentalContract *contract, const RentalRoom *room) {
    m_room = room;
    m_contract = contract;
}

void RentalUser::info() const {
    std::cout << "Username: " << m_userName << std::endl;
    std::cout << "Email: " << m_email << std::endl;
    std::cout << "Age: " << m_age << std::endl;
    std::cout << "Date of Birth: " << dateOfBirth << std::endl;
    std::cout << "Address: " << m_address << std::endl;
    std::cout << "Phone: " << m_phone << std::endl;
    if (m_room)
        std::cout << "Current Apartment Number: " << m_room->number() << std::endl;
}