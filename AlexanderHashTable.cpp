#include "AlexanderHashTable.h"

#include <cmath>
#include <utility>

namespace Alexander {

	HashTable::HashTable() noexcept
		: _buckets(2),
		_log2_buckets(1),
		_size(0),
		_last_comparison_amount(0),
		_table(_AllocateTable(_TableRealSize())),
		_primes() {}


	HashTable::~HashTable() noexcept {
		_DeallocateTable(_table);
	}


	HashTable::HashTable(HashTable&& table) noexcept
		: _buckets(table._buckets),
		_log2_buckets(table._log2_buckets),
		_size(table._size),
		_last_comparison_amount(table._last_comparison_amount),
		_table(table._table),
		_primes(table._primes) {

		table._table = nullptr;

	}


	HashTable& HashTable::operator = (HashTable&& table) noexcept {
		if (this == &table)
			return *this;

		_DeallocateTable(_table);

		_buckets = table._buckets;
		_log2_buckets = table._log2_buckets;
		_size = table._size;
		_last_comparison_amount = table._last_comparison_amount;
		_table = table._table;
		_primes = table._primes;

		table._table = nullptr;

		return *this;
	}


	bool HashTable::Insert(value_t value) noexcept {
		_last_comparison_amount = 0;

		if (1.0 * _size / _buckets > _MAX_LOAD_FACTOR)
			_Rehash();

		size_t hash = _Hash(value.GetName());

		if (_CheckUnique(value, hash)) {
			_Insert(std::move(value), hash);
			++_size;
			return true;
		}

		return false;
	}


	bool HashTable::Remove(const key_t& key) noexcept {
		_last_comparison_amount = 0;
		_Bucket* bucket = _FindBucket(key);

		if (bucket == nullptr)
			return false;

		bucket->_offset = BUCKET_REMOVED;
		--_size;
		return true;
	}


	const HashTable::value_t*
		HashTable::Find(const key_t& key) const noexcept {

		_last_comparison_amount = 0;
		_Bucket* bucket = _FindBucket(key);

		if (bucket == nullptr)
			return nullptr;

		return &bucket->_data;
	}


	Vector<Pair<const HashTable::value_t*, size_t>> HashTable::LookUp() const noexcept {
		return LookUp([](const value_t&) { return true; });
	}


	size_t HashTable::Size() const noexcept {
		return _size;
	}


	size_t HashTable::Buckets() const noexcept {
		return _buckets;
	}


	size_t HashTable::LastComparisonsAmount() const noexcept {
		return _last_comparison_amount;
	}


	size_t HashTable::_Hash(const key_t& key) const noexcept {
		const size_t R = 32767;
		size_t hash = 0;
		for (char c : key)
			hash = (R * hash + c) % _buckets;

		return hash;
	}


	size_t HashTable::_TableRealSize() const noexcept {
		return _buckets + _log2_buckets;
	}


	bool HashTable::_CheckUnique(const value_t& value, size_t hash) const noexcept {
		size_t limit = hash + _log2_buckets;
		while (hash <= limit) {
			_Bucket& bucket = _table[hash];
			if (bucket._offset == BUCKET_UNTOUCHED)
				return true;
			else if (bucket._offset == BUCKET_REMOVED)
				continue;
			else if (_Equal(bucket._data.GetName(), value.GetName()))
				return false;

			++hash;
		}

		return true;
	}


	void HashTable::_Insert(value_t value, size_t hash) noexcept {
		int8_t offset = 0;
		while (offset < _log2_buckets) {
			_Bucket& current = _table[hash];
			if (current._offset == BUCKET_UNTOUCHED || current._offset == BUCKET_REMOVED) {
				current = { std::move(value), offset };
				return;
			}
			else if (current._offset < offset) {
				std::swap(value, current._data);
				std::swap(offset, current._offset);
			}
			++offset;
			++hash;
		}

		_Rehash();
		_Insert(value, _Hash(value.GetName()));
	}


	void HashTable::_Insert(value_t value) noexcept {
		size_t hash = _Hash(value.GetName());
		_Insert(std::move(value), hash);
	}


	bool HashTable::_Equal(const key_t& lhs, const key_t& rhs) const noexcept {
		++_last_comparison_amount;
		return lhs == rhs;
	}


	HashTable::_Bucket* HashTable::_FindBucket(const key_t& key) const noexcept {
		size_t hash = _Hash(key);
		size_t limit = hash + _log2_buckets;
		while (hash <= limit) {
			_Bucket& b = _table[hash];
			if (b._offset != BUCKET_REMOVED &&
				b._offset != BUCKET_UNTOUCHED &&
				_Equal(b._data.GetName(), key)) {

				return &b;

			}
			++hash;
		}

		return nullptr;
	}

	void HashTable::_Rehash() noexcept {
		size_t old_buckets = _buckets;
		size_t old_log2_buckets = _log2_buckets;
		_Bucket* old_table = _table;

		_buckets = _primes.Next().Get();
		_log2_buckets = ceil(log2(_buckets));
		_table = _AllocateTable(_buckets + _log2_buckets);

		size_t old_limit = old_buckets + old_log2_buckets;
		for (size_t hash = 0; hash < old_limit; ++hash) {
			_Bucket& current = old_table[hash];
			if (current._offset != BUCKET_REMOVED &&
				current._offset != BUCKET_UNTOUCHED) {

				_Insert(std::move(current._data));

			}
		}

		_DeallocateTable(old_table);

	}


	HashTable::_Bucket* HashTable::_AllocateTable(size_t size) const noexcept {
		_Bucket* table = new _Bucket[size];
		for (size_t i = 0; i < size; ++i)
			table[i]._offset = BUCKET_UNTOUCHED;

		return table;
	}

	void HashTable::_DeallocateTable(_Bucket* table) const noexcept {
		delete[] table;
	}

}
