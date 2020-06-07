#include <utility>
#include <string>

#pragma once

// Цена услуги
class ServicePrice {
public:
    // Типы полей класса
    typedef std::string name_t;
    typedef std::string company_t;
    typedef double price_t;
    typedef std::string measure_t;

    // Инициализация по умолчанию
    ServicePrice()
            : _name("Empty"),
              _company("Empty"),
              _price(0.0),
              _measure("Empty") {}

    // Конструктор класса
    ServicePrice(name_t name, company_t company, price_t price, measure_t measure)
            : _name(std::move(name)),
              _company(std::move(company)),
              _price(std::move(price)),
              _measure(std::move(measure)) {}

    // Геттеры и сеттеры
    name_t GetName();
    company_t GetCompany();
    price_t GetPrice();
    measure_t GetMeasure();
    void SetName(name_t name);
    void SetCompany(company_t company);
    void SetPrice(price_t price);
    void SetMeasure(measure_t measure);
private:
    name_t _name;
    company_t _company;
    price_t _price;
    measure_t _measure;
};
