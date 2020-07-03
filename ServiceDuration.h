#include <utility>
#include <string>

#pragma once

// Цена услуги
class ServiceDuration {
public:
    // Типы полей класса
    typedef std::string name_t;
    typedef double duration_t;

    // Инициализация по умолчанию
    ServiceDuration() noexcept
            : _name("Empty"),
              _min_duration(0.0),
              _max_duration(0.0) {}


    ServiceDuration(name_t name, duration_t min_duration, duration_t max_duration) noexcept
            : _name(std::move(name)),
              _min_duration(min_duration),
              _max_duration(max_duration) {}

    ServiceDuration(const ServiceDuration& sd) = default;
    ServiceDuration(ServiceDuration&& sd) = default;
    ServiceDuration& operator = (const ServiceDuration& sd) = default;
    ServiceDuration& operator = (ServiceDuration&& sd) = default;


    name_t GetName() const noexcept;
    duration_t GetMinDuration() const noexcept;
    duration_t GetMaxDuration() const noexcept;
    void SetName(name_t name) noexcept;
    void SetMinDuration(duration_t min_duration) noexcept;
    void SetMaxDuration(duration_t max_duration) noexcept;
private:
    name_t _name;
    duration_t _min_duration;
    duration_t _max_duration;
};
