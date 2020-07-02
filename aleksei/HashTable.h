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

		bool Insert(Company t) noexcept;
		bool InsertService(const std::string& company, std::string service) noexcept;
		bool Remove(const std::string& t) noexcept;
		const Company* Find(const std::string& t) noexcept;
		Vector<Pair<const Company*, size_t>> LookUp() const noexcept;
		template <typename Predicate>
		Vector<Pair<const Company*, size_t>> LookUp(Predicate pred) const noexcept;
		size_t Capacity() const;
		size_t LastComparisonsAmount() const;
		size_t Buckets() const noexcept;
		size_t Size() const noexcept;
		Vector<Company> GetData() const;

	private:

		size_t N;
		ForwardList* table;
		size_t last_comparison_amount;
		size_t size;

		int Hash(std::string s) const;
		void ReHash();
	};

	template <typename Predicate>
	Vector<Pair<const Company*, size_t>> HashTable::LookUp(Predicate pred) const noexcept {
		Vector<Pair<const Company*, size_t>> v;
		Vector<const Company*> buf;
		Pair<Company, int> pair;
		for (size_t i = 0; i < N; i++) {
			buf = table[i].LookUp(pred);
			for (size_t j = 0; j < table[i].Size(); j++) {
				v.PushBack(Pair<const Company*, size_t>(buf[j], (size_t)Hash(buf[j]->GetName())));
			}
		}
		return v;
	}
}

