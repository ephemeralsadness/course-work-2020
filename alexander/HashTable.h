#pragma once

#include <cstddef>

#include "ServiceDuration.h"
#include "../helper/Vector.h"
#include "../helper/Pair.h"
#include "../helper/PrimeNumbersManager.h"

namespace Alexander {

    class HashTable {
    public:
        typedef ServiceDuration::name_t key_t;

        HashTable() noexcept;

        ~HashTable() noexcept;

        HashTable(const HashTable &table) = delete;

        HashTable &operator=(const HashTable &table) = delete;

        HashTable(HashTable &&table) noexcept;

        HashTable &operator=(HashTable &&table) noexcept;

        void Insert(ServiceDuration sd) noexcept;

        void Remove(const key_t &key) noexcept;

        const ServiceDuration* Find(const key_t &key) const noexcept;

        Vector<const ServiceDuration *> LookUp() const noexcept;

        template<typename Predicate>
        Vector<const ServiceDuration *> LookUp(Predicate pred) const noexcept;

        size_t Size() const noexcept;

        size_t Buckets() const noexcept;

        size_t LastComparisonsAmount() const noexcept;

    private:
        struct _Bucket {
            ServiceDuration _data;
            int8_t _offset;
        };

        size_t _buckets;
        size_t _log2_buckets;
        size_t _size;
        mutable size_t _last_comparisons_amount;
        _Bucket* _table;
        const double _max_load_factor;
        PrimeNumbersManager _primes;

        size_t _Hash(const key_t &key) const noexcept;
        _Bucket _BuildNewBucket(ServiceDuration sd) const noexcept;
        bool _CheckUnique(const ServiceDuration& sd, size_t hash) const noexcept;
        void _Rehash();

    };


    template<typename Predicate>
    Vector<const ServiceDuration *> HashTable::LookUp(Predicate pred) const noexcept {
        return Vector<const ServiceDuration *>();
    }

}