#include <iostream>
#include <fstream>

#include "IndexManager.h"

int main() {

    IndexManager manager;

    manager.AddCompany("россия", "земля");
    manager.AddServiceDuration(ServiceDuration("захватить мир", 1, 2));
    manager.AddServicePrice(ServicePrice("захватить мир", "россия", 100, "один мир"));
    manager.AddCustomer(Customer("Алексей", "захватить мир", "россия", 20));
    manager.AddCompany("США", "земля");
    manager.AddServicePrice(ServicePrice("захватить мир", "США", 200, "полмира"));
    manager.AddCustomer(Customer("Алексей", "захватить мир", "США", 1));
    manager.AddServiceDuration(ServiceDuration("освободить мир", 30, 30));
    manager.AddServicePrice(ServicePrice("освободить мир", "россия", 200, "один мир"));
    manager.AddCustomer(Customer("Саня", "освободить мир", "россия", 2));

    {
    	std::cout << "Отчет 1:" << std::endl;
        auto v = manager.GetCompaniesClients();
        for (auto it = v.Begin(); it != v.End(); ++it) {
        	std::cout << it->first << std::endl;
        	auto clients = it->second;
        	for (auto jt = clients.Begin(); jt != clients.End(); ++jt) {
        		std::cout << *jt << ' ';
        	}
        	std::cout << std::endl;
        }
    }

    {
    	std::cout << "Отчет 2:" << std::endl;
    	auto v = manager.GetCompaniesIncomes();
    	for (auto it = v.Begin(); it != v.End(); ++it) {
    		std::cout << it->first << ": " << it->second << std::endl;
    	}
    }

    {
    	std::cout << "Отчет 3:" << std::endl;
    	auto v = manager.GetCustomersServiceDurations();
    	for (auto it = v.Begin(); it != v.End(); ++it) {
    		std::cout << it->first << ": { " << it->second.first << ", "
    				  << it->second.second << " }" << std::endl;
    	}
    }

    {
    	std::cout << "Отчет 4:" << std::endl;
    	auto v = manager.GetServiceCompanies();
    	for (auto it = v.Begin(); it != v.End(); ++it) {
    		std::cout << it->first << std::endl;
    		auto companies = it->second;
    		for (auto jt = companies.Begin(); jt != companies.End(); ++jt) {
    			std::cout << *jt << ", ";
    		}
    		std::cout << std::endl;
    	}
    }


    return 0;
}
