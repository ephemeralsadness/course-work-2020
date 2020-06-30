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
		template <typename Predicate>
		void Remove(const std::string& key, Predicate pred) noexcept;
		void Remove(const std::string& key) noexcept;
		Vector<const Customer*> Find(const std::string& key) noexcept;
		template <typename Predicate>
		Vector<const Customer*> Find(const std::string& key, Predicate pred) noexcept;
		Vector<const Customer*> LookUp() const noexcept;
		template <typename Predicate>
		Vector<const Customer*> LookUp(Predicate pred) const noexcept;
		size_t Size() const noexcept;
		size_t LastComparisonsAmount() const noexcept;


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
		Node* _LowerBound(const std::string& key) noexcept;
		Node* _UpperBound(const std::string& key) noexcept;
		Node* _Successor(Node* node) const noexcept;
		Node* _Predecessor(Node* node) const noexcept;
		Node* _Min(Node* node) const noexcept;
		Node* _Max(Node* node) const noexcept;
		bool Empty();
		void _RemoveNode(Node* node) noexcept;
		void _DeleteSubtree(Node* st_root) noexcept;
		bool _Compare(const std::string rhs, const std::string& lhs) noexcept;
		template <typename T>
		bool _Equals(const T& rhs, const T& lhs) noexcept;
	
	};

	template <typename Predicate>
	void RBTree::Remove(const std::string& key, Predicate pred) noexcept {
		last_comparison_amount = 0;

		Node* first = _LowerBound(key);
		Node* last = _UpperBound(key);
		while (first != last) {
			Node* next = _Successor(first);
			if (pred(first->key)) {
				_RemoveNode(first);
			}
			first = next;
		}
	}

	template <typename Predicate>
	Vector<const Customer*> RBTree::Find(const std::string& key, Predicate pred)noexcept {
		last_comparison_amount = 0;

		Vector<const Customer*> result;
		Node* first = _LowerBound(key);
		Node* last = _UpperBound(key);

		while (first != last) {
			if (pred(first->key))
				result.PushBack(&first->key);
			first = _Successor(first);
		}

		return result;
	}

	template <typename Predicate>
	Vector<const Customer*> RBTree::LookUp(Predicate pred) const noexcept {
		Vector<const Customer*> result;

		Node* first = _Min(root);
		Node* last = nil;

		while (first != last) {
			if (pred(first->key))
				result.PushBack(&first->key);
			first = _Successor(first);
		}
		return result;
	}
}
