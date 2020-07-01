#include "IndexManager.h"

#include <stdexcept>
#include <fstream>

void IndexManager::AddCompany(Company c) {
	bool success = _companies.Insert(std::move(c));
	if (!success) {
		throw std::invalid_argument("Компания с таким названием уже есть в базе данных");
	}
}

void IndexManager::AddCustomer(Customer c) {
	Company* c_ptr = _companies.Find(c.GetCompanyName());

	if (c_ptr == nullptr) {
		throw std::invalid_argument("Компании с таким названием нету в базе данных");
	}

	bool has_service = false;
	for (auto it = c_ptr->GetServices().Begin(); it != c_ptr->GetServices().End(); ++it) {
		if (*it == c.GetService()) {
			has_service = true;
			break;
		}
	}

	if (has_service) {
		_customers.Insert(std::move(c));
	} else {
		throw std::invalid_argument("Данная компания не предоставляет такой услуги");
	}

}


void IndexManager::AddServicePrice(ServicePrice sp) {
	auto lambda = [&sp](const ServicePrice& s) {
		return s.GetCompany() == sp.GetCompany();
	};
	auto v = _service_prices.Find(sp.GetName(), lambda);

	if (v.Size() != 0) {
		throw std::invalid_argument("Услуга уже предоставляется данной компанией");
	}

	Company* c_ptr = _companies.Find(sp.GetCompany());
	if (c_ptr == nullptr) {
		throw std::invalid_argument("Компании с таким названием нету в базе данных");
	}
	c_ptr->GetServices().PushBack(sp.GetName());

	_service_prices.Insert(std::move(sp));
}


void IndexManager::AddServiceDuration(ServiceDuration sd) {
	bool success = _service_durations.Insert(std::move(sd));
	if (!success) {
		throw std::invalid_argument("Данная услуга уже существует");
	}
}

void IndexManager::RemoveCompany(const std::string &name) {
	bool success = _companies.Remove(name);
	if (!success) {
		throw std::invalid_argument("Компании с таким названием нету в базе данных");
	}

	auto customer_lambda = [&name](const Customer& c) {
		return c.GetCompanyName() == name;
	};
	_customers.Remove(name, customer_lambda);

	auto service_price_lambda = [&name](const ServicePrice& sp) {
		return sp.GetCompany() == name;
	};
	_service_prices.Remove(name, service_price_lambda);

}

void IndexManager::RemoveCustomer(const std::string &name) {
	auto v = _customers.Find(name);

	if (v.Size() != 0) {
		throw std::invalid_argument("Клиента с таким именем нету в базе данных");
	}

	_customers.Remove(name);
}

void IndexManager::RemoveServicePrice(const std::string &name, const std::string& company) {
	auto lambda = [&company](const ServicePrice& sp) {
		return company == sp.GetCompany();
	};
	auto v = _service_prices.Find(name, lambda);

	if (v.Size() != 0) {
		throw std::invalid_argument("Данная компания не предоставляет такой услуги");
	}

	_service_prices.Remove(name, lambda);

	auto& services = _companies.Find(company)->GetServices();
	for (size_t i = 0; i < services.Size(); ++i) {
		if (services[i] == name) {
			services.Erase(i);
			break;
		}
	}

	auto customer_lambda = [&name, &company](const Customer& c) {
		return name == c.GetService() && company == c.GetCompanyName();
	};
	auto customers = _customers.LookUp(customer_lambda);

	for (auto it = customers.Begin(); it != customers.End(); ++it) {
		_customers.Remove((**it).GetName(), customer_lambda);
	}

}

void IndexManager::RemoveServiceDuration(const std::string &name) {
	bool success = _service_durations.Remove(name);

	if (!success) {
		throw std::invalid_argument("Данной услуги нету в базе данных");
	}

	auto lambda = [&name, &_companies](const ServicePrice& sp) {
		if (name == sp.GetName()) {
			auto services = _companies.Find(sp.GetCompany())->GetServices();
			for (size_t i = 0; i < services.Size(); ++i) {
				if (services[i] == name) {
					services.Erase(i);
					break;
				}
			}
			return true;
		}
		return false;
	};

	auto customer_lambda = [&name](const Customer& c) {
		return name == c.GetService();
	};
	auto customers = _customers.LookUp(customer_lambda);

	for (auto it = customers.Begin(); it != customers.End(); ++it) {
		_customers.Remove((**it).GetName(), customer_lambda);
	}

}

Company IndexManager::FindCompany(const std::string &name) {
	auto company_ptr = _companies.Find(name);
	if (company_ptr == nullptr) {
		throw std::invalid_argument("Компании с таким названием нету в базе данных");
	}
	return *company_ptr;
}


Vector<Customer> IndexManager::FindCustomer(const std::string &name) {
	Vector<Customer> result;
	auto customer_ptrs = _customers.Find(name);

	if (customer_ptrs.Size() == 0) {
		throw std::invalid_argument("Заказчика с таким именем нету в базе данных");
	}

	for (auto it = customer_ptrs.Begin(); it != customer_ptrs.End(); ++it)
		result.PushBack(**it);

	return result;
}


Vector<ServicePrice> IndexManager::FindServicePrice(const std::string &name) {
	Vector<ServicePrice> result;
	auto service_price_ptrs = _service_prices.Find(name);

	if (service_price_ptrs.Size() == 0) {
		throw std::invalid_argument("Компаний, выполняющих данную услугу нету в базе данных");
	}

	for (auto it = service_price_ptrs.Begin(); it != service_price_ptrs.End(); ++it)
		result.PushBack(**it);

	return result;
}


ServiceDuration IndexManager::FindServiceDuration(const std::string &name) {
	auto service_duration_ptr = _service_durations.Find(name);
	if (service_duration_ptr == nullptr) {
		throw std::invalid_argument("Компании с таким названием нету в базе данных");
	}
	return *service_duration_ptr;
}

Vector<Pair<Company, size_t>> IndexManager::LookUpCompanies() {
	Vector<Pair<Company, size_t>> result;
	auto v = _companies.LookUp();
	for (auto it = v.Begin(); it != v.End(); ++it) {
		result.PushBack({*it->first, it->second});
	}

	return result;
}

Vector<Customer> IndexManager::LookUpCustomers() {
	Vector<Customer> result;
	auto v = _customers.LookUp();
	for (auto it = v.Begin(); it != v.End(); ++it) {
		result.PushBack(**it);
	}

	return result;
}
Vector<ServicePrice> IndexManager::LookUpServicePrices() {
	Vector<ServicePrice> result;
	auto v = _service_prices.LookUp();
	for (auto it = v.Begin(); it != v.End(); ++it) {
		result.PushBack(**it);
	}

	return result;
}
Vector<Pair<ServiceDuration, size_t>> IndexManager::LookUpServiceDurations() {
	Vector<Pair<ServiceDuration, size_t>> result;
	auto v = _service_durations.LookUp();
	for (auto it = v.Begin(); it != v.End(); ++it) {
		result.PushBack({*it->first, it->second});
	}

	return result;
}

void IndexManager::SaveData(const std::string &file_name) {
	std::ofstream fout(file_name);

	auto company_lookup = _companies.LookUp();
	auto customer_lookup = _customers.LookUp();
	auto service_price_lookup = _service_prices.LookUp();
	auto service_duration_lookup = _service_durations.LookUp();

	fout << company_lookup.Size() << '\n';
	for (auto it = company_lookup.Begin(); it != company_lookup.End(); ++it) {
		const Company& c = *it->first;
		fout << c.GetName() << '\n';

		auto& v = c.GetServices();
		fout << v.Size() << '\n';
		for (auto jt = v.Begin(); jt != v.End(); ++jt) {
			fout << *jt << '\n';
		}

		fout << c.GetAdress() << '\n';
	}

	fout << customer_lookup.Size() << '\n';
	for (auto it = customer_lookup.Begin(); it != customer_lookup.End(); ++it) {
		const Customer& c = **it;
		fout << c.GetName() << '\n';
		fout << c.GetService() << '\n';
		fout << c.GetCompanyName() << '\n';
		fout << c.GetVolume() << '\n';
	}

	fout << service_price_lookup.Size() << '\n';
	for (auto it = customer_lookup.Begin(); it != customer_lookup.End(); ++it) {
		const ServicePrice& sp = **it;
		fout << sp.GetName() << '\n';
		fout << sp.GetCompany() << '\n';
		fout << sp.GetPrice() << '\n';
		fout << sp.GetMeasure() << '\n';
	}

	fout << service_duration_lookup.Size() << '\n';
	for (auto it = customer_lookup.Begin(); it != customer_lookup.End(); ++it) {
		const ServiceDuration& sd = **it;
		fout << sd.GetName() << '\n';
		fout << sd.GetMinDuration() << '\n';
		fout << sd.GetMaxDuration() << '\n';
	}


}

void IndexManager::LoadData(const std::string &file_name) {
	std::ifstream fin(file_name);
	std::string buffer;

	{
		std::getline(fin, buffer);
		size_t amount = std::stoull(buffer);

		for (size_t i = 0; i < amount; ++i) {
			std::string name;
			std::getline(fin, name);

			Vector<std::string> services;
			std::getline(fin, buffer);

			size_t services_amount = std::stoull(buffer);
			for (size_t j = 0; j < services_amount; ++j) {
				std::getline(fin, buffer);
				services.PushBack(buffer);
			}

			std::string address;
			std::getline(fin, address);

			_companies.Insert(Company(std::move(name), std::move(services), std::move(address)));
		}
	}

	{
		std::getline(fin, buffer);
		size_t amount = std::stoull(buffer);

		for (size_t i = 0; i < amount; ++i) {
			std::string name;
			std::getline(fin, name);

			std::string service;
			std::getline(fin, service);

			std::string company_name;
			std::getline(fin, company_name);

			std::getline(fin, buffer);
			int16_t volume = std::stoi(buffer);

			_customers.Insert(Customer(std::move(name), std::move(service), std::move(company_name), volume));
		}
	}

	{
		std::getline(fin, buffer);
		size_t amount = std::stoull(buffer);

		for (size_t i = 0; i < amount; ++i) {
			std::string name;
			std::getline(fin, name);

			std::string company;
			std::getline(fin, company);

			std::getline(fin, buffer);
			double price = std::stod(buffer);

			std::string measure;
			std::getline(fin, measure);

			_service_prices.Insert(ServicePrice(std::move(name), std::move(company), price, std::move(measure)));
		}
	}

	{
		std::getline(fin, buffer);
		size_t amount = std::stoull(buffer);

		for (size_t i = 0; i < amount; ++i) {
			std::string name;
			std::getline(fin, name);

			std::getline(fin, buffer);
			double min_duration = std::stod(buffer);

			std::getline(fin, buffer);
			double max_duration = std::stod(buffer);

			_service_durations.Insert(ServiceDuration(std::move(name), min_duration, max_duration));
		}
	}

}

// TODO написать
// vector of {company name, income of this company}
Vector<Pair<std::string, double>> IndexManager::GetCompaniesIncomes() {
	Vector<Pair<std::string, double>> result;

	return result;
}

// TODO написать
// vector of {company name, vector of its clients}
Vector<Pair<std::string, Vector<std::string>>> IndexManager::GetCompaniesClients() {

}


// vector of {customer name, {min duration of its services, max duration of its services}}
Vector<Pair<std::string, Pair<double, double>>> IndexManager::GetCustomersServiceDurations() {
	Vector<Pair<std::string, Pair<double, double>>> result;
	auto lookup = _customers.LookUp();

	std::string current_customer = "";
	for (auto it = lookup.Begin(); it != lookup.End(); ++it) {
		const ServiceDuration* sd = _service_durations.Find((**it).GetService());
		if ((**it).GetName() != current_customer) {
			current_customer = (**it).GetName();
			result.PushBack({current_customer, {0, 0}});
		}
		result[result.Size() - 1].second.first += sd->GetMinDuration();
		result[result.Size() - 1].second.second += sd->GetMaxDuration();
	}

	return result;
}

// vector of {service, {companies, who perform this service}}
Vector<Pair<std::string, Vector<std::string>>> IndexManager::GetServiceCompanies() {

}
