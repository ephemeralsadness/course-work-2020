#pragma once

#include <cstddef>

#include "ServiceDuration.h"
#include "../helper/Vector.h"

class HashTable {
public:
    typedef ServiceDuration::name_t key_t;

    HashTable() noexcept;
    ~HashTable() noexcept;
    HashTable(const HashTable& table) = delete;
    HashTable& operator = (const HashTable& table) = delete;
    HashTable(HashTable&& table) noexcept;
    HashTable& operator = (HashTable&& table) noexcept;

    void Insert(ServiceDuration sp) noexcept;
    void Remove(const key_t& key) noexcept;
    const ServiceDuration& Find(const key_t& key) const noexcept;
    Vector<const ServiceDuration*> LookUp() const noexcept;
    template <typename Predicate>
    Vector<const ServiceDuration*> LookUp(Predicate pred) const noexcept;
    size_t Capacity() const;
    size_t LastComparisonsAmount() const;

private:
    size_t hash(const key_t& key) {
        const size_t R = 27644437;
        size_t hash = 0;
        for (size_t i = 0; i < key.length(); ++i)
            hash = (R * hash + key[i]) % _capacity;

        return hash;
    }

    size_t _capacity;
    ServiceDuration* _table;
};
