#pragma once

#include <cstddef>

#include "ServiceDuration.h"
#include "Vector.h"
#include "Pair.h"
#include "PrimeNumbersManager.h"

namespace Alexander {

	class HashTable {
	public:
		typedef ServiceDuration value_t;
		typedef ServiceDuration::name_t key_t;

		HashTable() noexcept;
		~HashTable() noexcept;
		HashTable(const HashTable& table) = delete;
		HashTable& operator=(const HashTable& table) = delete;
		HashTable(HashTable&& table) noexcept;
		HashTable& operator=(HashTable&& table) noexcept;

		bool Insert(value_t value) noexcept;
		bool Remove(const key_t& key) noexcept;
		const value_t* Find(const key_t& key) const noexcept;
		Vector<Pair<const HashTable::value_t*, size_t>> LookUp() const noexcept;
		template <typename Predicate>
		Vector<Pair<const HashTable::value_t*, size_t>> LookUp(Predicate pred) const noexcept;
		size_t Size() const noexcept;
		size_t Buckets() const noexcept;
		size_t LastComparisonsAmount() const noexcept;

	private:

		struct _Bucket {
			value_t _data;
			int8_t _offset;
		};

		size_t _buckets;
		size_t _log2_buckets;
		size_t _size;
		mutable size_t _last_comparison_amount;
		_Bucket* _table;
		PrimeNumbersManager _primes;

		constexpr static double _MAX_LOAD_FACTOR = 0.8;
		constexpr static int BUCKET_REMOVED = -1;
		constexpr static int BUCKET_UNTOUCHED = -2;

		size_t _Hash(const key_t& key) const noexcept;
		size_t _TableRealSize() const noexcept;
		bool _CheckUnique(const value_t& value, size_t hash) const noexcept;
		void _Insert(value_t value, size_t hash) noexcept;
		void _Insert(value_t value) noexcept;
		bool _Equal(const key_t& lhs, const key_t& rhs) const noexcept;
		_Bucket* _FindBucket(const key_t& key) const noexcept;
		void _Rehash() noexcept;

		_Bucket* _AllocateTable(size_t size) const noexcept;
		void _DeallocateTable(_Bucket* start) const noexcept;
	};


	template<typename Predicate>
	Vector<Pair<const HashTable::value_t*, size_t>> HashTable::LookUp(Predicate pred) const noexcept {
		Vector<Pair<const HashTable::value_t*, size_t>> result;
		size_t table_real_size = _TableRealSize();
		for (size_t i = 0; i < table_real_size; ++i) {
			_Bucket& b = _table[i];

			if (b._offset != BUCKET_REMOVED &&
				b._offset != BUCKET_UNTOUCHED &&
				pred(b._data)) {

				result.PushBack({ &b._data, i });

			}
		}

		return result;
	}

}