#pragma once

#include "AlexanderRBTree.h"
#include "AlekseiRBTree.h"
#include "AlexanderHashTable.h"
#include "AlekseiHashTable.h"

#include <wx\wx.h>


class IndexManager {
public:
	IndexManager() = default;

	void AddCompany(std::string company_name, std::string address);
	void AddCustomer(std::string name, std::string service, std::string company, uint16_t volume);
	void AddServicePrice(std::string name, std::string company, double price, std::string measure);
	void AddServiceDuration(std::string name, double min_duration, double max_duration);

	void RemoveCompany(const std::string& name);
	void RemoveCustomer(const std::string& name);
	void RemoveServicePrice(const std::string& name, const std::string& company);
	void RemoveServiceDuration(const std::string& name);

	Company FindCompany(const std::string& name);
	Vector<Customer> FindCustomer(const std::string& name);
	Vector<ServicePrice> FindServicePrice(const std::string& name);
	ServiceDuration FindServiceDuration(const std::string& name);

	Vector<Pair<Company, size_t>> LookUpCompanies();
	Vector<Customer> LookUpCustomers();
	Vector<ServicePrice> LookUpServicePrices();
	Vector<Pair<ServiceDuration, size_t>> LookUpServiceDurations();

	void SaveData(const std::string& file_name);
	void LoadData(const std::string& file_name);

	// vector of {company name, income of this company}
	void SaveCompaniesIncomes(const std::string& file_name);

	// vector of {company name, vector of its clients}
	void SaveCompaniesClients(const std::string& file_name);

	// vector of {customer name, {min duration of its services, max duration of its services}}
	void SaveCustomersServiceDurations(const std::string& file_name);

	// vector of {service, {companies, who perform this service}}
	void SaveServiceCompanies(const std::string& file_name);

	// последнее количество сравнений
	size_t GetLastComparisonsAmount();

private:
	size_t _last_comparisons_amount = 0;
	Aleksei::HashTable _companies;
	Aleksei::RBTree _customers;
	Alexander::RBTree _service_prices;
	Alexander::HashTable _service_durations;
};
