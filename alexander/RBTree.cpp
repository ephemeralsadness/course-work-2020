#include "RBTree.h"

#include <map>

namespace Alexander {

    RBTree::RBTree() noexcept
            : _root(_nil),
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
        _Node* node = BuildNewNode(std::move(sp));
        _InsertNode(node);
    }

    void RBTree::Remove(const key_t& key) noexcept {
        RBTree::Remove(key, [](const ServicePrice&) { return true; });
    }

    Vector<const ServicePrice*> RBTree::Find(const key_t& key) const noexcept {
        return Find(key, [](const ServicePrice&) { return true; });
    }

    size_t RBTree::GetLastComparisonsAmount() const {
        return _last_comparisons_amount;
    }

    size_t RBTree::Size() const {
        return _size;
    }

    void RBTree::_DeleteSubtree(_Node* node) noexcept {
        if (node == _nil) return;
        _DeleteSubtree(node->child[0]);
        _DeleteSubtree(node->child[1]);
        delete node;
    }

    void RBTree::_Rotate(_Node* node, bool side) noexcept {
        _Node* c = node->child[!side];
        node->child[!side] = c->child[side];

        if (c->child[side] != _nil)
            c->child[side]->parent = node;
        c->parent = node->parent;

        if (node->parent == _nil)
            _root = c;
        else node->parent->child[((node == node->parent->child[side]) == side)] = c;

        c->child[side] = node;
        node->parent = c;
    }

    void RBTree::_InsertNode(_Node* node) noexcept {
        ++_size;

        _Node *y = _nil;
        _Node *x = _root;
        key_t key = node->data.GetName();
        while (x != _nil) {
            y = x;
            x = x->child[key >= x->data.GetName()];
        }

        if (y == _nil)
            _root = node;
        else
            y->child[key >= y->data.GetName()] = node;
        node->parent = y;

        _FixInsert(node);
    }

    void RBTree::_FixInsert(_Node* node) noexcept {
        while (!node->parent->color)
        {
            _Node *p = node->parent;
            _Node *g = node->parent->parent;
            _Node *u;
            bool side = (p != g->child[0]);
            u = g->child[!side];
            if (!u->color) {
                p->color = BLACK;
                u->color = BLACK;
                g->color = RED;
                node = g;
            } else {
                if (node == p->child[!side]) {
                    node = p;
                    _Rotate(node, side);
                }
                node->parent->color = BLACK;
                g->color = RED;
                _Rotate(g, !side);
            }
        }
        _root->color = BLACK;
    }

    RBTree::_Node* RBTree::_LowerBound(const key_t& key) const noexcept {
        _Node* x = _root;
        _Node* y = _nil;
        while (x != _nil) {
            if (x->data.GetName() >= key)
                y = x, x = x->child[0];
            else
                x = x->child[1];
        }

        return y;
    }

    RBTree::_Node* RBTree::_UpperBound(const key_t& key) const noexcept {
        _Node* x = _root;
        _Node* y = _nil;
        while (x != _nil) {
            if (x->data.GetName() > key)
                y = x, x = x->child[0];
            else
                x = x->child[1];
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

    void RBTree::_RemoveNode(_Node* z) noexcept {
        _Node *y = z;
        bool original = z->color;
        _Node *x;

        if (z->child[0] == _nil) {
            x = z->child[1];
            _Transplant(z, z->child[1]);
        } else if (z->child[1] == _nil) {
            x = z->child[0];
            _Transplant(z, z->child[0]);
        } else {
            y = _Min(z->child[1]);
            original = y->color;
            x = y->child[1];
            if (y->parent == z) {
                x->parent = y;
            } else {
                _Transplant(y, y->child[1]);
                y->child[1] = z->child[1];
                y->child[1]->parent = y;
            }
            _Transplant(z, y);
            y->child[0] = z->child[0];
            y->child[0]->parent = y;
            y->color = z->color;
        }

        if (original == BLACK) {
            _FixRemove(x);
        }
        delete z;
    }

    void RBTree::_FixRemove(_Node* n) noexcept {
        while (n != _root && n->color) {
            bool side = n != n->parent->child[0];
            _Node *w = n->parent->child[!side];
            if (!w->color) {
                w->color = BLACK;
                n->parent->color = RED;
                _Rotate(n->parent, side);
                w = n->parent->child[!side];
            }
            if (w->child[side]->color && w->child[!side]->color) {
                w->color = RED;
                n = n->parent;
            } else {
                if (w->child[!side]->color == BLACK) {
                    w->child[side]->color = BLACK;
                    w->color = RED;
                    _Rotate(w, !side);
                    w = n->parent->child[!side];
                }
                w->color = n->parent->color;
                n->parent->color = BLACK;
                w->child[!side]->color = BLACK;
                _Rotate(n->parent, side);
                n = _root;
            }
        }
        n->color = BLACK;
    }

    void RBTree::_Transplant(_Node* x, _Node* y) noexcept {
        if (x->parent == _nil)
            _root = y;
        else
            x->parent->child[x != x->parent->child[0]] = y;
        y->parent = x->parent;
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
        return new _Node {std::move(sp), 0, _nil, { _nil, _nil }};
    }
}