#include "rental_management.h"

int main(int argc, char const *argv[]) {
    RentalManagement manager;

    manager.addProperty("Lot1", "MA", {});
    manager.addProperty("Lot2", "MA", {});

    auto property1 = manager.getProperty("Lot1");
    auto property2 = manager.getProperty("Lot1");

    std::vector<RentalRoom> rooms1 = {
        {property1, 1,  "A1", RentalRoom::RoomType::NORMAL,   100000 },
        {property1, 2,  "A2", RentalRoom::RoomType::NORMAL,   100000 },
        {property1, 3,  "A3", RentalRoom::RoomType::NORMAL,   100000 },
        {property1, 4,  "A4", RentalRoom::RoomType::NORMAL,   100000 },
        {property1, 5,  "A5", RentalRoom::RoomType::NORMAL,   100000 },
        {property1, 6,  "A6", RentalRoom::RoomType::NORMAL,   100000 },
        {property1, 7,  "A7", RentalRoom::RoomType::NORMAL,   100000 },
        {property1, 8,  "A8", RentalRoom::RoomType::NORMAL,   100000 },
        {property1, 10, "B1", RentalRoom::RoomType::SPECICAL, 2000000},
        {property1, 11, "B2", RentalRoom::RoomType::SPECICAL, 2000000},
        {property1, 12, "B3", RentalRoom::RoomType::SPECICAL, 2000000},
        {property1, 13, "B4", RentalRoom::RoomType::SPECICAL, 2000000},
        {property1, 14, "B5", RentalRoom::RoomType::SPECICAL, 2000000},
        {property1, 15, "B6", RentalRoom::RoomType::SPECICAL, 2000000},
        {property1, 16, "B7", RentalRoom::RoomType::SPECICAL, 2000000},
        {property1, 17, "B8", RentalRoom::RoomType::SPECICAL, 2000000}
    };

    std::vector<RentalRoom> rooms2 = {
        {property2, 11,  "MA1", RentalRoom::RoomType::NORMAL,   100000 },
        {property2, 12,  "MA2", RentalRoom::RoomType::NORMAL,   100000 },
        {property2, 13,  "MA3", RentalRoom::RoomType::NORMAL,   100000 },
        {property2, 14,  "MA4", RentalRoom::RoomType::NORMAL,   100000 },
        {property2, 15,  "MA5", RentalRoom::RoomType::NORMAL,   100000 },
        {property2, 16,  "MA6", RentalRoom::RoomType::NORMAL,   100000 },
        {property2, 17,  "MA7", RentalRoom::RoomType::NORMAL,   100000 },
        {property2, 18,  "MA8", RentalRoom::RoomType::NORMAL,   100000 },
        {property2, 110, "MB1", RentalRoom::RoomType::SPECICAL, 2000000},
        {property2, 111, "MB2", RentalRoom::RoomType::SPECICAL, 2000000},
        {property2, 112, "MB3", RentalRoom::RoomType::SPECICAL, 2000000},
        {property2, 113, "MB4", RentalRoom::RoomType::SPECICAL, 2000000},
        {property2, 114, "MB5", RentalRoom::RoomType::SPECICAL, 2000000},
        {property2, 115, "MB6", RentalRoom::RoomType::SPECICAL, 2000000},
        {property2, 116, "MB7", RentalRoom::RoomType::SPECICAL, 2000000},
        {property2, 117, "MB8", RentalRoom::RoomType::SPECICAL, 2000000}
    };

    for (auto &i : rooms1) {
        property1->addRoom(i);
    }

    for (auto &i : rooms2) {
        property2->addRoom(i);
    }
    property1->info();
    property2->info();

    std::vector<RentalUser> users_room1 = {
        RentalUser("John Doe", "john.doe@example.com", 30, "1992-05-10", "123 Main St", "555-1234"),
        RentalUser("Jane JO", "jane.smith@example.com", 25, "1997-08-15", "456 Elm St", "555-5678"),
        RentalUser("John Daniel", "john.doe@example.com", 30, "1992-05-10", "123 Main St", "555-1234")};

    std::vector<RentalUser> users_room2 = {
        RentalUser("Will Tunel", "jane.smith@example.com", 25, "1997-08-15", "456 Elm St", "555-5678"),
        RentalUser("Alizabeth L", "john.doe@example.com", 30, "1992-05-10", "123 Main St", "555-1234"),
        RentalUser("Jane D", "jane.smith@example.com", 25, "1997-08-15", "456 Elm St", "555-5678"),
    };

    std::chrono::system_clock::time_point startDate = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point endDate = startDate + std::chrono::hours(24 * 365);
    std::chrono::system_clock::time_point payDate = startDate + std::chrono::hours(24 * 30);
    int paymentDate = 5;

    RentalContractPrice contractPrice;
    contractPrice.add("room", 100000)
        .add("water", 1000)
        .add("electric", 15000);

    RentalContract contract(property1->findRoom(1), property1, users_room1, startDate, endDate, paymentDate, contractPrice);
    contract.info();

    RentalBill bill(property1->findRoom(1), payDate);
    bill.addBill("water", {"water", 0, 0, 20, 0, 100000})
        .addBill("electric", {"water", 0, 0, 10, 0, 200000});
    bill.info();

    manager.processRent(contract);
    manager.propertiesInfo();
    manager.contractInfo();
    manager.processPayment(property1->findRoom(1), bill, 100000);
    return 0;
}
