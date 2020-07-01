#pragma once

#include "aleksei/RBTree.h"
#include "alexander/RBTree.h"
#include "aleksei/HashTable.h"
#include "alexander/HashTable.h"

namespace Reports {
    struct CompanyIncomes {
        std::string company;
        double income;
    };
}




class IndexManager {
public:
    Vector<Reports::CompanyIncomes> GetCompanyIncomes() const {
        using Reports::CompanyIncomes;
        Vector<CompanyIncomes> result;
        result.Reserve(_companies.Size());

        auto companies = _companies.LookUp();
        for (auto it = companies.Begin(); it != companies.End(); ++it) {
            result.PushBack({ it->first->GetName(), 0 });
        }

        result.MergeSort([](const CompanyIncomes& lhs, const CompanyIncomes& rhs) {
            return lhs.company < rhs.company;
        });

        auto customers = _customers.LookUp();
        for (auto it = customers.Begin(); it != customers.End(); ++it) {
            size_t company_index = companies.BinarySearch({it->first->GetName()});
        }


        result.MergeSort([](const CompanyIncomes& lhs, const CompanyIncomes& rhs) {
            return lhs.income > rhs.income;
        });
        return result;
    }

    Vector<Pair<Company, Vector<std::string>>> GetCompanyCustomers(
            const std::string& company_name
            ) const;

    Vector<Pair<std::string, Pair<double, double>>> GetCustomerServiceDuration() const;

    Vector<std::string> GetCompany(const std::string& service) const;

    bool Add(Company company);
    bool Add(Customer customer);
    bool Add(ServiceDuration service_duration);
    bool Add(ServicePrice service_price);

private:
    Aleksei::RBTree _customers;
    Aleksei::HashTable _companies;
    Alexander::RBTree _service_prices;
    Alexander::HashTable _service_durations;
};
