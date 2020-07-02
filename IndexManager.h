#pragma once

#include "alexander/RBTree.h"
#include "alexander/HashTable.h"
#include "aleksei/RBTree.h"
#include "aleksei/HashTable.h"


/*
 * Добавление
 * - компании
 * - заказа
 * - услуги
 * Удаление
 * - компании
 * - заказа
 * - услуги
 * Поиск
 * - компании
 * - заказа
 * - цены услуги
 * - длительность услуги
 * Просмотр
 * - компаний
 * - заказов
 * - цен услуг
 * - длительность услуг
 * Работа с файлами
 * - сохранение
 * - считывание
 * Формирование отчетов
 * - первый
 * - второй
 * - третий
 * - четвертый
 */
class IndexManager {
public:
	IndexManager() = default;

	void AddCompany(std::string company_name, std::string address);
	void AddCustomer(Customer c);
	void AddServicePrice(ServicePrice sp);
	void AddServiceDuration(ServiceDuration sd);

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
	Vector<Pair<std::string, double>> GetCompaniesIncomes();

	// vector of {company name, vector of its clients}
	Vector<Pair<std::string, Vector<std::string>>> GetCompaniesClients();

	// vector of {customer name, {min duration of its services, max duration of its services}}
	Vector<Pair<std::string, Pair<double, double>>> GetCustomersServiceDurations();

	// vector of {service, {companies, who perform this service}}
	Vector<Pair<std::string, Vector<std::string>>> GetServiceCompanies();

	// последнее количество сравнений
	size_t GetLastComparisonsAmount();

private:
	size_t _last_comparisons_amount = 0;
	Aleksei::HashTable _companies;
	Aleksei::RBTree _customers;
	Alexander::RBTree _service_prices;
	Alexander::HashTable _service_durations;
};
