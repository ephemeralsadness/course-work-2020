#include "HashTable.h"

#include <cmath>

namespace Alexander {

    HashTable::HashTable() noexcept
            : _buckets(2),
              _log2_buckets(static_cast<size_t>(ceil(_buckets))),
              _size(0),
              _table(new _Bucket[_buckets + _log2_buckets]),
              _max_load_factor(0.8),
              _primes() {
        for (size_t i = 0; i < _buckets + _log2_buckets; ++i) {
            _table[i]._offset = -2;
        }
    }

    HashTable::~HashTable() noexcept {
        delete[] _table;
    }

    HashTable::HashTable(HashTable&& table) noexcept
            : _buckets(table._buckets),
              _log2_buckets(table._log2_buckets),
              _size(table._size),
              _table(table._table),
              _max_load_factor(table._max_load_factor),
              _primes(table._primes) {
        _table = nullptr;
    }

    HashTable& HashTable::operator = (HashTable && table) noexcept {
        _buckets = table._buckets;
        _log2_buckets = table._log2_buckets;
        _size = table._size;
        _table = table._table;
        _primes = table._primes;
        _table = nullptr;

        return *this;
    }

    void HashTable::Insert(ServiceDuration sd) noexcept {
        // -2 : не было элемента
        // -1 : был элемент, удален
        // >= 0 : offset

        size_t hash = _Hash(sd.GetName());
        if (!_CheckUnique(sd, hash))
            return;

        int8_t offset = 0;
        while (offset < _log2_buckets) {
            _Bucket& current = _table[hash];

            if (current._offset < 0) {
                current._data = std::move(sd);
                current._offset = offset;
                return;
            } else if (current._offset < offset) {
                std::swap(sd, current._data);
                std::swap(offset, current._offset);
            }

            ++hash;
            ++offset;
        }

        _Rehash();
        Insert(std::move(sd));
    }

    void HashTable::Remove(const key_t &key) noexcept {
        size_t hash = _Hash(key);
        int8_t offset = 0;

        while (offset < _log2_buckets) {
            _Bucket& current = _table[hash];

            if (current._offset == -2) {
                break;
            } else if (current._offset != -1 && current._data.GetName() == key) {
                current._data.~ServiceDuration();
                current._offset = -1;
                break;
            }

            ++hash;
            ++offset;
        }
    }

    const ServiceDuration* HashTable::Find(const key_t &key) const noexcept {
        size_t hash = _Hash(key);
        int8_t offset = 0;

        while (offset < _log2_buckets) {
            _Bucket& current = _table[hash];

            if (current._offset == -2)
                return nullptr;
            else if (current._offset != -1 && current._data.GetName() == key)
                return &current._data;

            ++hash;
            ++offset;
        }

        return nullptr;
    }

    Vector<const ServiceDuration *> HashTable::LookUp() const noexcept {
        Vector<const ServiceDuration*> result;
        for (size_t i = 0; i < _buckets + _log2_buckets; ++i) {
            if (_table[i]._offset >= 0)
                result.PushBack(&_table[i]._data);
        }

        return result;
    }

    size_t HashTable::Size() const noexcept {
        return _size;
    }

    size_t HashTable::Buckets() const noexcept {
        return _buckets;
    }

    size_t HashTable::LastComparisonsAmount() const noexcept {
        return _last_comparisons_amount;
    }

    size_t HashTable::_Hash(const key_t &key) const noexcept {
        const size_t R = 27644437;
        size_t hash = 0;
        for (char c : key)
            hash = (R * hash + c) % _buckets;

        return hash;
    }

    HashTable::_Bucket HashTable::_BuildNewBucket(ServiceDuration sd) const noexcept {
        return { std::move(sd), 0 };
    }

    bool HashTable::_CheckUnique(const ServiceDuration& sd, size_t hash) const noexcept {
        size_t limit = hash + _log2_buckets;
        while (hash != limit) {
            if (_table[hash]._offset == -2)
                return true;
            else if (_table[hash]._data.GetName() == sd.GetName())
                return false;
            ++hash;
        }

        return true;
    }

    void HashTable::_Rehash() {
        const size_t old_buckets = _buckets;
        const size_t old_log2_buckets = _log2_buckets;
        _Bucket* old_table = _table;

        _buckets = _primes.Next().Get();
        _log2_buckets = ceil(log2(_buckets));
        _size = 0;
        _table = new _Bucket[_buckets + _log2_buckets];

        for (size_t i = 0; i < _buckets + _log2_buckets; ++i) {
            _table[i]._offset = -2;
        }

        for (size_t i = 0; i < old_buckets + old_log2_buckets; ++i) {
            if (old_table[i]._offset >= 0)
                Insert(std::move(old_table[i]._data));
        }

        delete[] old_table;
    }
}