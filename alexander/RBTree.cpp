#include "RBTree.h"

#include <map>

namespace Alexander {

    // PUBLIC METHODS

    RBTree::RBTree() noexcept
            : _root(nullptr),
              _nil(new _Node { ServicePrice() }),
              _last_comparisons_amount(0),
              _size(0) {
        _root = _nil;
        _nil->parent = _nil;
        _nil->color = BLACK;
        _nil->child[0] = _nil;
        _nil->child[1] = _nil;
    }

    RBTree::~RBTree() noexcept {
        _DeleteSubtree(_root);
        delete _nil;
    }

    RBTree::RBTree(RBTree&& tree) noexcept
            : _root(tree._root),
              _nil(tree._nil),
              _last_comparisons_amount(tree._last_comparisons_amount),
              _size(tree._size) {
        tree._root = nullptr;
        tree._nil = nullptr;
        tree._last_comparisons_amount = 0;
        tree._size = 0;
    }

    RBTree& RBTree::operator = (RBTree&& tree) noexcept {
        this->~RBTree();
        _root = tree._root;
        _nil = tree._nil;
        _last_comparisons_amount = tree._last_comparisons_amount;
        _size = tree._size;
        tree._root = nullptr;
        tree._nil = nullptr;
        tree._last_comparisons_amount = 0;
        tree._size = 0;

        return *this;
    }

    void RBTree::Insert(ServicePrice sp) noexcept {
        _last_comparisons_amount = 0;
        _Node* node = BuildNewNode(std::move(sp));
        _InsertNode(node);
        ++_size;
    }

    void RBTree::Remove(const key_t& key) noexcept {
        RBTree::Remove(key, [](const ServicePrice&) { return true; });
    }

    Vector<const ServicePrice*> RBTree::Find(const key_t& key) const noexcept {
        return Find(key, [](const ServicePrice&) { return true; });
    }

    Vector<const ServicePrice*> RBTree::LookUp() const noexcept {
        return LookUp([](const ServicePrice&) { return true; });
    }

    size_t RBTree::Size() const {
        return _size;
    }

    size_t RBTree::LastComparisonsAmount() const {
        return _last_comparisons_amount;
    }

    // PRIVATE METHODS

    bool RBTree::_Comp(const key_t& lhs, const key_t& rhs) const noexcept {
        ++_last_comparisons_amount;
        return lhs < rhs;
    }

    void RBTree::_DeleteSubtree(_Node* st_root) noexcept {
        if (st_root == _nil) return;
        _DeleteSubtree(st_root->child[0]);
        _DeleteSubtree(st_root->child[1]);
        delete st_root;
    }

    void RBTree::_Rotate(_Node* node, bool side) noexcept {
        _Node* child = node->child[!side];
        node->child[!side] = child->child[side];

        if (child->child[side] != _nil)
            child->child[side]->parent = node;
        child->parent = node->parent;

        if (node->parent == _nil)
            _root = child;
        else node->parent->child[((node == node->parent->child[side]) == side)] = child;

        child->child[side] = node;
        node->parent = child;
    }

    void RBTree::_Transplant(_Node* x, _Node* y) noexcept {
        if (x->parent == _nil)
            _root = y;
        else
            x->parent->child[x != x->parent->child[0]] = y;
        y->parent = x->parent;
    }

    void RBTree::_InsertNode(_Node* node) noexcept {
        _Node *y = _nil;
        _Node *x = _root;
        key_t key = node->data.GetName();
        while (x != _nil) {
            y = x;
            x = x->child[!_Comp(key, x->data.GetName())];
        }

        if (y == _nil)
            _root = node;
        else
            y->child[!_Comp(key, y->data.GetName())] = node;
        node->parent = y;

        _FixInsert(node);
    }

    void RBTree::_FixInsert(_Node* node) noexcept {
        while (!node->parent->color) {
            _Node *parent = node->parent;
            _Node *gparent = node->parent->parent;

            bool side = (parent != gparent->child[0]);
            _Node *uncle = gparent->child[!side];

            if (!uncle->color) {
                parent->color = BLACK;
                uncle->color = BLACK;
                gparent->color = RED;
                node = gparent;
            } else {
                if (node == parent->child[!side]) {
                    node = parent;
                    _Rotate(node, side);
                }
                node->parent->color = BLACK;
                gparent->color = RED;
                _Rotate(gparent, !side);
            }

        }

        _root->color = BLACK;
    }

    void RBTree::_RemoveNode(_Node* node) noexcept {
        _Node *y = node;
        _Node *x;
        bool original = node->color;

        if (node->child[0] == _nil) {
            x = node->child[1];
            _Transplant(node, node->child[1]);
        } else if (node->child[1] == _nil) {
            x = node->child[0];
            _Transplant(node, node->child[0]);
        } else {
            y = _Min(node->child[1]);
            original = y->color;
            x = y->child[1];
            if (y->parent == node) {
                x->parent = y;
            } else {
                _Transplant(y, y->child[1]);
                y->child[1] = node->child[1];
                y->child[1]->parent = y;
            }
            _Transplant(node, y);
            y->child[0] = node->child[0];
            y->child[0]->parent = y;
            y->color = node->color;
        }

        if (original == BLACK) {
            _FixRemove(x);
        }
        delete node;
    }

    void RBTree::_FixRemove(_Node* node) noexcept {
        while (node != _root && node->color) {
            bool side = node != node->parent->child[0];
            _Node *sibling = node->parent->child[!side];
            if (!sibling->color) {
                sibling->color = BLACK;
                node->parent->color = RED;
                _Rotate(node->parent, side);
                sibling = node->parent->child[!side];
            }
            if (sibling->child[side]->color && sibling->child[!side]->color) {
                sibling->color = RED;
                node = node->parent;
            } else {
                if (sibling->child[!side]->color == BLACK) {
                    sibling->child[side]->color = BLACK;
                    sibling->color = RED;
                    _Rotate(sibling, !side);
                    sibling = node->parent->child[!side];
                }
                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                sibling->child[!side]->color = BLACK;
                _Rotate(node->parent, side);
                node = _root;
            }
        }
        node->color = BLACK;
    }

    RBTree::_Node* RBTree::_LowerBound(const key_t& key) const noexcept {
        _Node* x = _root;
        _Node* y = _nil;
        while (x != _nil) {
            if (!_Comp(x->data.GetName(), key)) {
                y = x;
                x = x->child[0];
            } else {
                x = x->child[1];
            }
        }

        return y;
    }

    RBTree::_Node* RBTree::_UpperBound(const key_t& key) const noexcept {
        _Node* x = _root;
        _Node* y = _nil;
        while (x != _nil) {
            if (_Comp(key, x->data.GetName())) {
                y = x;
                x = x->child[0];
            } else {
                x = x->child[1];
            }
        }

        return y;
    }

    RBTree::_Node* RBTree::_Successor(_Node* node) const noexcept {
        if (node->child[1] != _nil)
            return _Min(node->child[1]);
        _Node* y = node->parent;

        while (y != _nil && node == y->child[1]) {
            node = y;
            y = y->parent;
        }

        return y;
    }

    RBTree::_Node* RBTree::_Min(_Node* node) const noexcept {
        if (node == _nil) return _nil;

        while (node->child[0] != _nil) {
            node = node->child[0];
        }

        return node;
    }

    RBTree::_Node* RBTree::_Max(_Node* node) const noexcept {
        if (node == _nil) return _nil;

        while (node->child[1]  != _nil) {
            node = node->child[1];
        }

        return node;
    }

    RBTree::_Node* RBTree::BuildNewNode(ServicePrice sp) const noexcept {
        return new _Node {std::move(sp), RED, _nil, { _nil, _nil }};
    }
}