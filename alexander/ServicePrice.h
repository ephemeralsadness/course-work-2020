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
    ServicePrice() noexcept
            : _name("Empty"),
              _company("Empty"),
              _price(0.0),
              _measure("Empty") {}

    // Конструктор класса
    ServicePrice(name_t name, company_t company, price_t price, measure_t measure) noexcept
            : _name(std::move(name)),
              _company(std::move(company)),
              _price(price),
              _measure(std::move(measure)) {}

    // Геттеры и сеттеры
    name_t GetName() const noexcept;
    company_t GetCompany() const noexcept;
    price_t GetPrice() const noexcept;
    measure_t GetMeasure() const noexcept;
    void SetName(name_t name) noexcept;
    void SetCompany(company_t company) noexcept;
    void SetPrice(price_t price) noexcept;
    void SetMeasure(measure_t measure) noexcept;
private:
    name_t _name;
    company_t _company;
    price_t _price;
    measure_t _measure;
};
