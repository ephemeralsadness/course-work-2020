#pragma once
#include <functional>
#include "List.h"
#include "Pair.h"
#include "Vector.h"

namespace Aleksei {
	class HashTable {
	public:
		HashTable(){}
		~HashTable() {}

		HashTable(const HashTable&) = delete;

		HashTable& operator = (const HashTable&) = delete;
		
		HashTable(HashTable&&) = default;
		
		HashTable& operator = (HashTable&&) = default;

		void Insert(Company t) {
			table[Hash(t.GetName())].push(t);
			size++;
		}

		void Remove(const Company& t) {
			size_t s = table[Hash(t.GetName())].get_size();
			table[Hash(t.GetName())].Delete(t);
			size = size - s + table[Hash(t.GetName())].get_size();
		}

		Company* Find(const Company& t) {
			Company* result = table[Hash(t.GetName())].Find(t.GetName());
			last_comparison_amount = table[Hash(t.GetName())].GetLastComparisonAmount();
			return result;
		}

		Vector<Pair<Company, size_t>> Lookup() {
			Vector<Pair<Company, size_t>> v;
			Vector<Company> buf;
			Pair<Company, int> pair;
			for (size_t i = 0; i < N; i++) {
				buf = table[i].GetAllCompanies();
				for (size_t j = 0; j < table[i].get_size(); j++) {
					v.PushBack(Pair<Company, size_t>(buf[j], (size_t)Hash(buf[j].GetName())));
				}
			}
			return v;
		}

		int Size() const {
			return size;
		}

		size_t GetLastComparisonAmount() const {
			return last_comparison_amount;
		}

	private:

		size_t N = 1024;
		MyList* table = new MyList[N];
		size_t last_comparison_amount = 0;
		size_t size = 0;

		int Hash(std::string s) {
			float h = 0;
			float A = (float)0.6180339887;
			for (unsigned int i = 0; i < s.size(); i++) {
				h = ((int)s[i] * A + h) - (int)((int)s[i] * A + h);
			}
			return (int)round(N * h);
		}
	};
}