#include"RBTree.h"
#include<utility>

using namespace Aleksei;

RBTree::RBTree() noexcept{
	root = nil;
}

RBTree::~RBTree() noexcept{

}

void RBTree::Insert(Customer t)noexcept {

	Node* z = new Node();
	z->key = { std::move(t) };
	Node* y = nil;
	Node* x = root;
	while (x != nil) {
		y = x;
		if (z < x)
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
		if (z < y)
			y->left = z;
		else
			y->right = z;
		z->left = nil;
		z->right = nil;
		z->color = 0;
		z->parent = y;
		InsertFixup(z);
	}
	size++;
}

void RBTree::LeftRotate(Node* x) {
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

void RBTree::RightRotate(Node* x)
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
	else x->parent->left = y;
	y->right = x;
	x->parent = y;
}

void RBTree::transplant(Node* u, Node* v)
{
	if (u->parent == nil)
		root = v;
	else if (u == u->parent->left)
		u->parent = v->left;
	else u->parent = v->right;
	v->parent = u->parent;
}

void RBTree::InsertFixup(Node* z) {
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

void RBTree::DeleteFixup(Node* x) {
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
	x->color = 1;
}

/*void RBTree::Remove(const std::string& key)
{
	myList* z;
	z = this->getListPointer(day, month);
	if (z != NULL)
	{
		if (z->getSize() == 1)
		{
			myList* x;
			myList* y = z;
			bool orig_color = y->getColor();
			if (z->getLeft() == nil)
			{
				x = z->getRight();
				transplant(z, z->getLeft());
			}
			else
				if (z->getRight() == nil)
				{
					x = z->getLeft();
					transplant(z, z->getLeft());
				}
				else
				{
					y = TreeMin(z->getRight());
					orig_color = y->getColor();
					x = y->getRight();
					if (y->getParent() == z)
						x->setParent(y);
					else
					{
						transplant(y, y->getRight());
						y->setRight(z->getRight());
						y->getRight()->setParent(y);
					}
					transplant(z, y);
					y->setLeft(z->getLeft());
					y->getLeft()->setParent(y);
					y->setColor(z->getColor());
				}
			z->~myList();
			if (orig_color == 1)
				RBDeleteFixup(x);
		}
		else
		{
			z->deleteOne();
		}
	}
}

bool RBTree::Empty() {
	if (root == nil)
		return true;
	else return false;
}

size_t RBTree::Size() const {
	return size;
}*/

RBTree::Node* RBTree::_Predecessor(Node* node) const noexcept {
	Node* temp = node;
	if (temp->left != nil) {
		temp = temp->left;
		while (temp->right != nil)
			temp = temp->right;
		return temp;
	}
	while (temp != root) {
		if (temp->parent->right == temp)
			return temp->parent;
		temp = temp->parent;
	}
	while (temp->right != nil)
		temp = temp->right;
	return temp;
}

RBTree::Node* RBTree::_Successor(Node* node) const noexcept {
	Node* temp = node;
	if (temp->right != nil) {
		temp = temp->right;
		while (temp->left != nil)
			temp = temp->left;
		return temp;
	}
	while (temp != root) {
		if (temp->parent->left == temp)
			return temp->parent;
		temp = temp->parent;
	}
	while (temp->left != nil)
		temp = temp->left;
	return temp;
}

RBTree::Node* RBTree::_LowerBound(const std::string& key) const noexcept {
	Node* temp = root;
	while (temp->key.GetName() != key) {
		if (temp->key.GetName() < key)
			temp = temp->right;
		else
			temp = temp->left;
	}
	while (temp->key.GetName() == key)
		temp = _Predecessor(temp);
	return _Successor(temp);
}

RBTree::Node* RBTree::_UpperBound(const std::string& key) const noexcept {
	Node* temp = root;
	while (temp->key.GetName() != key) {
		if (temp->key.GetName() < key)
			temp = temp->right;
		else
			temp = temp->left;
	}
	while (temp->key.GetName() == key)
		temp = _Successor(temp);
	return _Predecessor(temp);
}

size_t RBTree::Size() const noexcept {
	return size;
}

size_t RBTree::LastComparisonsAmount() const noexcept {
	return last_comparison_amount;
}

bool RBTree::Empty() {
	return size;
}

Vector<const Customer*> RBTree::Find(const std::string& key) const noexcept {
	Vector<const Customer*> v;
	Node* temp = _LowerBound(key);
	while (temp->key.GetName() == key) {
		v.PushBack(&temp->key);
	}
	return v;
}

Vector<const Customer*> RBTree::LookUp() const noexcept {
	Node* temp = root;
	while (temp->left != nil)
		temp = temp->left;
	Node* buf = temp;
	Vector<const Customer*> v;
	do {
		v.PushBack(&temp->key);
		temp = _Successor(temp);
	} while (temp != buf);
		return v;
}

RBTree::Node* RBTree::_Min(Node* node) const noexcept {
	Node* temp = node;
	while (temp->left != nil)
		temp = temp->left;
	return temp;
}

RBTree::Node* RBTree::_Max(Node* node) const noexcept {
	Node* temp = node;
	while (temp->right != nil)
		temp = temp->right;
	return temp;
}

void RBTree::Remove(const std::string& key) noexcept {
	Node* z;
	Node* suc;
	z = _LowerBound(key);
	suc = _Successor(z);
	while (z->key.GetName() == key) {
		_RemoveNode(z);
		z = suc;
		suc = _Successor(z);
	}
}

void RBTree::_RemoveNode(Node* node) noexcept {
	Node* z = { std::move(node) };
	Node* x;
	Node* y = z;
	bool orig_color = y->color;
	if (z->left == nil) {
		x = z->right;
		transplant(z, z->left);
	}
	else
		if (z->right == nil) {
			x = z->left;
			transplant(z, z->left);
		}
		else {
			y = _Min(z->right);
			orig_color = y->color;
			x = y->right;
			if (y->parent == z)
				x->parent = y;
			else {
				transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
	delete z;
	size--;
	if (orig_color == 1)
		DeleteFixup(x);
}
