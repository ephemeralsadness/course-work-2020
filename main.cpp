#include <iostream>
#include <fstream>

#include "IndexManager.h"

int main() {

    IndexManager manager;

    manager.AddCompany("россия", "земля");
    manager.AddServiceDuration(ServiceDuration("захватить мир", 1, 2));
    manager.AddServicePrice(ServicePrice("захватить мир", "россия", 100, "один мир"));
    manager.AddCustomer(Customer("Алексей нахуй", "захватить мир", "россия", 20));

    std::cout << manager.FindCompany("россия");

    manager.SaveData("data.txt");

    return 0;
}
