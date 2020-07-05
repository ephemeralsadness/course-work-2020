#include "AlekseiHashTable.h"

namespace Aleksei {

	HashTable::HashTable() noexcept {
		N = 4;
		table = new ForwardList[N];
		size = 0;
		last_comparison_amount = 0;
	}

	HashTable::~HashTable() noexcept {
		delete[] table;
	}

	HashTable::HashTable(HashTable&& ht)
		: N(ht.N),
		table(ht.table),
		size(ht.size),
		last_comparison_amount(ht.last_comparison_amount) {

		ht.table = nullptr;

	}

	HashTable& HashTable::operator = (HashTable&& ht) {
		if (this != &ht) {
			delete[] table;

			N = ht.N;
			table = ht.table;
			size = ht.size;
			last_comparison_amount = ht.last_comparison_amount;

			ht.table = nullptr;
		}
		return *this;
	}

	bool HashTable::Insert(Company t) noexcept {
		if (Find(t.GetName()) == nullptr) {
			table[Hash(t.GetName())].Push(std::move(t));
			size++;
			// TODO лучше вынести 3/4 как static поле класса, 
			// которое обычно называется MAX_LOAD_FACTOR
			if (size >= (N / 4) * 3)
				ReHash();
			return true;
		}
		else return false;
	}

	bool HashTable::InsertService(const std::string& company, std::string service) noexcept {
		auto ptr = table[Hash(company)].Find(company);
		if (ptr != nullptr) {
			ptr->GetServices().PushBack(std::move(service));
			return true;
		}
		return false;
	}

	bool HashTable::Remove(const std::string& t) noexcept {
		size_t s = table[Hash(t)].Size();
		if (table[Hash(t)].Erase(t)) {
			size = size - s + table[Hash(t)].Size();
			last_comparison_amount = table[Hash(t)].LastComparisonAmount();
			return true;
		}
		else return false;
	}

	bool HashTable::RemoveService(const std::string& company, const std::string& service) noexcept {
		auto ptr = table[Hash(company)].Find(company);
		if (ptr != nullptr) {
			auto& v = ptr->GetServices();
			for (size_t i = 0; i < v.Size(); ++i) {
				if (v[i] == service) {
					v.Erase(i);
					return true;
				}
			}
		}
		return false;
	}

	const Company* HashTable::Find(const std::string& t) noexcept {
		const Company* result = table[Hash(t)].Find(t);
		last_comparison_amount = table[Hash(t)].LastComparisonAmount();
		return result;
	}

	Vector<Pair<const Company*, size_t>> HashTable::LookUp() const noexcept {
		Vector<Pair<const Company*, size_t>> v;
		Vector<const Company*> buf;
		Pair<Company, int> pair;
		for (size_t i = 0; i < N; i++) {
			buf = table[i].ToPointerVector();
			for (size_t j = 0; j < table[i].Size(); j++) {
				v.PushBack(Pair<const Company*, size_t>(buf[j], i));
			}
		}
		return v;
	}

	size_t HashTable::Buckets() const noexcept {
		return N;
	}

	size_t HashTable::Size() const noexcept {
		return size;
	}

	size_t HashTable::Capacity() const {
		return size;
	}

	size_t HashTable::LastComparisonsAmount() const {
		return last_comparison_amount;
	}


	int HashTable::Hash(std::string s) const {
		float h = 0;
		float A = (float)0.6180339887;
		for (size_t i = 0; i < s.size(); i++) {
			h = (abs((int)s[i]) * A + h) - (int)(abs((int)s[i]) * A + h);
		}
		int result = (int)(N * h);
		return result;
	}

	Vector<Company> HashTable::GetData() const {
		Vector<Company> v, buf;
		v.Reserve(size);
		int k = 0;
		for (int i = 0; i < N; i++) {
			buf = table[i].ToVector();
			for (auto it = buf.Begin(); it != buf.End(); ++it) {
				v.PushBack(*it);
				k++;
			}
		}
		return v;
	}

	void HashTable::ReHash() {
		Vector<Company> v = GetData();
		N *= 2;
		delete[] table;
		table = new ForwardList[N];
		size = 0;
		for (int i = 0; i < v.Size(); i++)
			this->Insert(v[i]);
	}

}
