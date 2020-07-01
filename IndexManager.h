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

	void AddCompany(Company c);
	void AddCustomer(Customer c);
	void AddService(ServicePrice sp, ServiceDuration sd);

	void RemoveCompany(const std::string& name);
	void RemoveCustomer(const std::string& name);
	void RemoveService(const std::string& name);

	const Company& FindCompany(const std::string& name);
	Vector<const Customer> FindCustomer(const std::string& name);
	Vector<const ServicePrice> FindServicePrice(const std::string& name);
	const Company& FindServiceDuration(const std::string& name);

	Vector<Pair<const Company*, size_t>> LookUpCompanies();
	Vector<const Customer*> LookUpCustomers();
	Vector<const ServicePrice*> LookUpServicePrices();
	Vector<Pair<const ServiceDuration*, size_t>> LookUpServiceDurations();

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

private:
	Aleksei::HashTable _companies;
	Aleksei::RBTree _customers;
	Alexander::RBTree _service_prices;
	Alexander::HashTable _service_durations;
};
