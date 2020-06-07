#include "RBTree.h"

namespace Alexander {

    RBTree::RBTree() noexcept
            : _root(nullptr),
              _last_comparisons_amount(0),
              _size(0) {}

    RBTree::~RBTree() noexcept {
        _DeleteSubtree(_root);
    }

    RBTree::RBTree(RBTree&& tree) noexcept
            : _root(tree._root) {
        tree._root = nullptr;
    }

    RBTree& RBTree::operator = (RBTree&& tree) noexcept {
        this->~RBTree();
        _root = tree._root;
        tree._root = nullptr;
        return *this;
    }

    void RBTree::Insert(ServicePrice sp) noexcept {
        _Node* node = new _Node(std::move(sp));
        const key_t& key = node->data.GetName();

        _Node* y = nullptr;
        _Node* x = _root;

        while (x != nullptr) {
            y = x;
            x = x->child[key > x->data.GetName()];
        }

        if (y == nullptr)
            _root = node;
        else
            y->child[key > y->data.GetName()] = node;
        node->parent = y;

        ++_size;
        _FixInsert(node);
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

    RBTree::_Node::_Node(ServicePrice _data)
            : data(std::move(_data)),
              color(RED),
              parent(nullptr),
              child{ nullptr, nullptr } {}
}