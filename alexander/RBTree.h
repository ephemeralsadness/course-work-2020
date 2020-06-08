// TODO Default LookUp

#pragma once

#include <istream>
#include <ostream>
#include <map>

#include "ServicePrice.h"
#include "../helper/Vector.h"

namespace Alexander {

    class RBTree {
    public:
        typedef ServicePrice::name_t key_t;

        RBTree() noexcept;

        ~RBTree() noexcept;

        RBTree(const RBTree& tree) = delete;
        RBTree& operator = (const RBTree& tree) = delete;

        RBTree(RBTree&& tree) noexcept;

        RBTree& operator = (RBTree&& tree) noexcept;

        void Insert(ServicePrice sp) noexcept;

        void Remove(const key_t& key) noexcept;

        template <typename Predicate>
        void Remove(const key_t& key, Predicate pred) noexcept;

        Vector<const ServicePrice*> Find(const key_t& key) const noexcept;

        template <typename Predicate>
        Vector<const ServicePrice*> Find(const key_t& key, Predicate pred) const noexcept;

        template <typename Predicate>
        Vector<const ServicePrice*> LookUp(Predicate pred) const noexcept;

        size_t Size() const;

        size_t GetLastComparisonsAmount() const;
    private:

        struct _Node {
            const ServicePrice data;
            bool color;
            _Node* parent;
            _Node* child[2];
        };

        _Node* _root;
        _Node* _nil;
        size_t _last_comparisons_amount;
        size_t _size;


        static const bool RED = 0;
        static const bool BLACK = 1;

        void _DeleteSubtree(_Node* node) noexcept;

        void _Rotate(_Node* node, bool side) noexcept;

        void _InsertNode(_Node* node) noexcept;

        void _FixInsert(_Node* node) noexcept;

        _Node* _LowerBound(const key_t& key) const noexcept;

        _Node* _UpperBound(const key_t& key) const noexcept;

        _Node* _Successor(_Node* node) const noexcept;

        void _RemoveNode(_Node* node) noexcept;

        void _FixRemove(_Node* node) noexcept;

        void _Transplant(_Node* x, _Node* y) noexcept;

        _Node* _Min(_Node* node) const noexcept;

        _Node* _Max(_Node* node) const noexcept;

        _Node* BuildNewNode(ServicePrice sp) const noexcept;
    };

    template <typename Predicate>
    void RBTree::Remove(const key_t& key, Predicate pred) noexcept {
        struct _Node* first = _LowerBound(key);
        struct _Node* last = _UpperBound(key);
        while (first != last) {
            _Node* next = _Successor(first);
            if (pred(first->data)) {
                _RemoveNode(first);
            }
            first = next;
        }
    }

    template <typename Predicate>
    Vector<const ServicePrice*> RBTree::Find(const key_t& key, Predicate pred) const noexcept {
        Vector<const ServicePrice*> result;
        _Node* first = _LowerBound(key);
        _Node* last = _UpperBound(key);

        while (first != last) {
            if (pred(first->data))
                result.PushBack(&first->data);
            first = _Successor(first);
        }

        return result;
    }

    template <typename Predicate>
    Vector<const ServicePrice*> RBTree::LookUp(Predicate pred) const noexcept {
        Vector<const ServicePrice*> result;

        _Node* first = _Min(_root);
        _Node* last = _nil;

        while (first != last) {
            if (pred(first->data))
                result.PushBack(&first->data);
            first = _Successor(first);
        }

        return result;
    }

}