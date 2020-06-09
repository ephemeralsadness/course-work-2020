#pragma once
#include <functional>
#include<utility>
#include "../helper/Vector.h"
#include "../aleksei/Customer.h"

namespace Aleksei {

	class RBTree {
	public:

		RBTree() noexcept;
		~RBTree() noexcept;
		RBTree(const RBTree& tree) = delete;
		RBTree& operator = (const RBTree& tree) = delete;
		RBTree(RBTree&& tree) noexcept = default;
		RBTree& operator = (RBTree&& tree) noexcept = default;

		void Insert(Customer customer) noexcept;
		void Remove(const std::string& key) noexcept;
		Vector<const Customer*> Find(const std::string& key) const noexcept;
		Vector<const Customer*> LookUp() const noexcept;
		size_t Size() const;
		size_t LastComparisonsAmount() const;


	private:
		struct Node {
			Customer key;
			bool color;
			Node* left;
			Node* right;
			Node* parent;

			Node() {
				color = 1;
				left = NULL;
				right = NULL;
				parent = NULL;
			}
		};
		Node* nil = new Node();
		size_t last_comparison_amount = 0;
		Node* root;
		size_t size = 0;

		void LeftRotate(Node* x);
		void RightRotate(Node* x);
		void transplant(Node* u, Node* v);
		void InsertFixup(Node* z);
		void DeleteFixup(Node* x);
		Node* _LowerBound(const std::string& key) const noexcept;
		Node* _UpperBound(const std::string& key) const noexcept;
		Node* _Successor(Node* node) const noexcept;
		Node* _Predecessor(Node* node) const noexcept;
		bool Empty();

	
	};

}
