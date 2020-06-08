#pragma once
#include <functional>
#include<utility>
#include "../helper/Vector.h"

namespace Aleksei {

	template <typename Company>
	class RBTree {
	public:

		/**
		 * Входные данные: имя нового дерева->
		 *
		 * Выходные данные: пустое дерево с заданным именем->
		 *
		 * Конструктор дерева-> Изначально дерево пустое->
		 */
		RBTree(){
			root = nil;
		}

		//~RedBlackTree();

		RBTree(const RBTree&) = delete;

		RBTree& operator=(const RBTree&) = delete;

		RBTree(RBTree&&) = default;

		RBTree& operator=(RBTree&&) = default;

		//virtual void Insert(T t) = 0;

		//virtual void Remove(const T & t) = 0;

//		virtual Vector<T> Find(const T & t) const = 0;

	//	virtual size_t GetLastComparisonAmount() const = 0;

	/**
	 * Входные данные: дерево, дата - день и месяц
	 *
	 * Выходные данные: дерево с новым узлом или с обновлённым списком одного из узлов
	 *
	 * Функция добавляет в дерево узел с указанными параметрами или
	 * если узел с такими параметрами уже есть,
	 * то просто добавлет в список этого узла новый элемент
	 *
	 * @param - day - день, month - месяц
	 */
	void Insert(Company t) //(T t)
	{

		Node* z = new Node();
		z->key = { std::move(t) };
		Node* y = nil;
		Node* x = root;
		while (x != nil) {
			y = x;
			if (z<x)
				x = x->left;
			else x = x->right;
		}
		if (root == nil) {
			root = z;
			root->color = 1;
			root->left = nil;
			root->right = nil;
			root->parent = nil;
		}
		else {
			if (z<y)
				y->left = z;
			else
				y->right = z;
			z->left = nil;
			z->right = nil;
			z->color = 0;
			z->parent = y;
			RBFixup(z);
		}
	}

	//size_t Size() const;

	private:
		struct Node {
			Company key;
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

		/**
		 * Входные данные: указатель на корень поддерева и основное дерево
		 *
		 * Выходные данные: измененное поддерево в основном дереве с помощью левого поворота
		 *
		 * Процедура делает левый поворот указанного поддерева
		 *
		 * @param x - указатель на корень поддерева
		 */
		void LeftRotate(Node* x) {
			Node* y = x->right;
			x->right = y->left;
			if (y->left != nil)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == nil)
				root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else x->parent->right = y;
			y->left = x;
			x->parent = y;
		}

		/**
		 * Входные данные: указатель на корень поддерева и основное дерево
		 *
		 * Выходные данные: измененное поддерево в основном дереве с помощью правого поворота
		 *
		 * Процедура делает правый поворот указанного поддерева
		 *
		 * @param x - указатель на корень поддерева
		 */
		void RightRotate(Node* x)
		{
			Node* y = x->left;
			x->left = y->right;
			if (y->right != nil)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == nil)
				root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else x->parent->left =y;
			y->right = x;
			x->parent = y;
		}

		/**
		 * Входные данные: указатель на два корня поддеревьев и основное дерево
		 *
		 * Выходные данные: изменённое дерево с переставленным поддеревом на другое место
		 *
		 * Перествялет поддерево на другое место
		 *
		 * @param x - указатель на корень поддерева
		 */
		void transplant(Node* u, Node* v)
		{
			if (u->parent == nil)
				root = v;
			else if (u == u->parent->left)
				u->parent = v->left;
			else u->parent = v->right;
			v->parent = u->parent;
		}

		/**
		 *Входные данные : указатель на узел дерева и само дерево->
		 *
		 * Выходные данные : Сбалансированное дерево->
		 *
		 * Балансирует дерево после добавления нового элемента
		 *
		 * @param x - указатель на корень поддерева
		 */
		void RBFixup(Node* z) {
			Node* y = z->parent;
			while (z->parent->color == 0) {
				if (z->parent == z->parent->parent->left) {
					y = z->parent->parent->right;
					if (y->color == 0) {
						z->parent->color = 1;
						y->color = 1;
						z->parent->parent->color = 0;
						z = z->parent->parent;
					}
					else {
						if (z == z->parent->right) {
							z = z->parent;
							LeftRotate(z);
						}
						z->parent->color = 1;
						z->parent->parent->color = 0;
						RightRotate(z->parent->parent);
					}
				} 
				else
				{
					y = z->parent->parent->left;
					if (y->color == 0) {
						z->parent->color = 1;
						y->color = 1;
						z->parent->parent->color = 0;
						z = z->parent->parent;
					}
					else {
						if (z == z->parent->left) {
							z = z->parent;
							RightRotate(z);
						}
						z->parent->color = 1;
						z->parent->parent->color = 0;
						LeftRotate(z->parent->parent);
					}
				}
			}
			root->color = 1;
		}

		/**
		 * Входные данные: указатель на узел дерева и само дерево->
		 *
		 * Выходные данные: Сбалансированное дерево->
		 *
		 * Балансирует дерево после удаления узла
		 *
		 * @param x - указатель на корень поддерева
		 */
		void RBDeleteFixup(Node* x) {
			Node* w;
			while ((x != root) && (x->color == 1)) {
				if (x == x->parent->left) {
					w = x->parent->right;
					if (w->color == 0) {
						w->color = 1;
						w->parent->color = 0;
						LeftRotate(w->parent);
						w = x->parent->right;
					}
					if ((w->right->color == 1) && (w->left->color == 1)) {
						w->color = 0;
						x = x->parent;
					}
					else {
						if (w->right->color == 1) {
							w->right->color = 1;
							w->color = 0;
							RightRotate(w);

						}
						w->color = w->parent->color;
						w->right->color = 1;
						w->parent->color = 1;
						LeftRotate(x->parent);
						x = root;
					}
				}
				else {
					w = x->parent->left;
					if (w->color == 0) {
						w->color = 1;
						w->parent->color = 0;
						RightRotate(w->parent);
						w = x->parent->left;
					}
					if ((w->left->color == 1) && (w->right->color == 1)) {
						w->color = 0;
						x = x->parent;
					}
					else {
						if (w->left->color == 1) {
							w->left->color = 1;
							w->color = 0;
							LeftRotate(w);
						}
						w->color = w->parent->color;
						w->left->color = 1;
						w->parent->color = 1;
						RightRotate(x->parent);
						x = root;
					}
				}
			}
			x->color=1;
		}
		/**
		 * Входные данные: узел дерева->
		 *
		 * Выходные данные: да или нет (является ли узел пустым)
		 *
		 * Проверяет список узла на пустоту
		 *
		 * @return - true (список пуст иначе false)
		 */
		bool Empty() {
			if (root == nil)
				return true;
			else return false;
		}

	
	};

}