#include "RBTree.h"
#include <utility>

using namespace Aleksei;

RBTree::RBTree() noexcept{
	root = nil;
	nil->left = nil;
	nil->parent = nil;
	nil->right = nil;
}

RBTree::~RBTree() noexcept{
	_DeleteSubtree(root);
}

bool RBTree::_Compare(const std::string rhs, const std::string& lhs) noexcept {
	last_comparisons_amount++;
	return rhs < lhs;
}

template<typename T>
bool RBTree::_Equals(const T& rhs, const T& lhs) noexcept {
	last_comparisons_amount++;
	return rhs == lhs;
}

void RBTree::_DeleteSubtree(Node* st_root) noexcept {
	if (st_root != nil) {
		_DeleteSubtree(st_root->left);
		_DeleteSubtree(st_root->right);
		delete st_root;
	}
}

void RBTree::Insert(Customer t)noexcept {

    last_comparisons_amount = 0;
	Node* z = new Node();
	z->key = { std::move(t) };
	Node* y = nil;
	Node* x = root;
	while (x != nil) {
		y = x;
		if (_Compare(z->key.GetName(),x->key.GetName()))
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
		if (_Compare(z->key.GetName(), y->key.GetName()))
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
		u->parent->left = v;
	else u->parent->right = v;
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
	return nil;
}

RBTree::Node* RBTree::_LowerBound(const std::string& key) noexcept {
    Node* x = root;
    Node* y = nil;
    while (x != nil) {
        if (!_Compare(x->key.GetName(), key)) {
            y = x;
            x = x->left;
        } else {
            x = x->right;
        }
    }

    return y;
}

RBTree::Node* RBTree::_UpperBound(const std::string& key)noexcept {
    Node* x = root;
    Node* y = nil;
    while (x != nil) {
        if (_Compare(key, x->key.GetName())) {
            y = x;
            x = x->left;
        } else {
            x = x->right;
        }
    }

    return y;
}

size_t RBTree::Size() const noexcept {
	return size;
}

size_t RBTree::LastComparisonsAmount() const noexcept {
	return last_comparisons_amount;
}

bool RBTree::Empty() {
	return size;
}

Vector<const Customer*> RBTree::Find(const std::string& key) noexcept {
	return Find(key, [](const Customer& c) { return true; });
}

Vector<const Customer*> RBTree::LookUp() const noexcept {
	return LookUp([](const Customer& c) { return true; });
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
	return Remove(key, [](const Customer&) { return true; });
}

void RBTree::_RemoveNode(Node* node) noexcept {
	Node* z = node;
	Node* x;
	Node* y = z;
	bool orig_color = y->color;
	if (z->left == nil) {
		x = z->right;
		transplant(z, z->right);
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
