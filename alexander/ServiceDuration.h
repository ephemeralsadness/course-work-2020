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
    ServiceDuration()
            : _name("Empty"),
              _min_duration(0.0),
              _max_duration(0.0) {}


    ServiceDuration(name_t name, duration_t min_duration, duration_t max_duration)
            : _name(std::move(name)),
              _min_duration(std::move(min_duration)),
              _max_duration(std::move(max_duration)) {}

    name_t GetName();
    duration_t GetMinDuration();
    duration_t GetMaxDuration();
    void SetName(name_t name);
    void SetMinDuration(duration_t min_duration);
    void SetMaxDuration(duration_t max_duration);
private:
    name_t _name;
    duration_t _min_duration;
    duration_t _max_duration;
};
