#pragma once
#include <functional>
#include "../helper/Pair.h"
#include "ForwardList.h"
#include "../helper/Vector.h"

namespace Aleksei {
	class HashTable {
	public:
		HashTable() noexcept;
		~HashTable() noexcept;

		HashTable(const HashTable&) = delete;

		HashTable& operator = (const HashTable&) = delete;
		
		HashTable(HashTable&&) = default;
		
		HashTable& operator = (HashTable&&) = default;

		void Insert(Company t) noexcept;

		void Remove(const std::string& t) noexcept;

		const Company* Find(const Company& t) noexcept;

		Vector<Pair<Company, size_t>> Lookup() const noexcept;

		size_t Capacity() const;

		size_t LastComparisonsAmount() const;

		Vector<Company> GetData() const;

	private:

		size_t N;
		ForwardList* table;
		size_t last_comparison_amount;
		size_t size;

		int Hash(std::string s) const;

		void ReHash();
	};
}
