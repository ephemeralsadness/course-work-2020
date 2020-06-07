#pragma once

#include <istream>
#include <ostream>

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
        enum _Color {
            RED = 0,
            BLACK = 1
        };

        enum _Side {
            LEFT = 0,
            RIGHT = 1
        };

        struct _Node {
            const ServicePrice data;
            _Color color;
            _Node* parent;
            _Node* child[2];

            _Node(ServicePrice _data);
        };

        _Node* _root;
        size_t _last_comparisons_amount;
        size_t _size;


        void _DeleteSubtree(_Node* node);

        _Node* _LowerBound() const;
        _Node* _UpperBound() const;

        _Node* _FixInsert(_Node* node);

        _Node* Successor(_Node* node) const;

        // make --_size;
        _Node* _RemoveNode(_Node* node);

        _Node* _Min(_Node* node) const;

        _Node* _Max(_Node* node) const;
    };

    template <typename Predicate>
    void RBTree::Remove(const key_t& key, Predicate pred) noexcept {
        struct _Node* first = _LowerBound();
        struct _Node* last = _UpperBound();
        while (first != last) {
            _Node* next = Successor(first);
            if (pred(first->data)) {
                _RemoveNode(first);
            }
            first = next;
        }
    }

    template <typename Predicate>
    Vector<const ServicePrice*> RBTree::Find(const key_t& key, Predicate pred) const noexcept {
        Vector<const ServicePrice*> result;
        _Node* first = _LowerBound();
        _Node* last = _UpperBound();

        while (first != last) {
            if (pred(first->data))
                result.PushBack(&first->data);
            first = Successor(first);
        }

        return result;
    }

    template <typename Predicate>
    Vector<const ServicePrice*> RBTree::LookUp(Predicate pred) const noexcept {
        Vector<const ServicePrice*> result;

        _Node* first = _Min(_root);
        _Node* last = nullptr;

        while (first != last) {
            if (pred(first->data))
                result.PushBack(&first->data);
            first = Successor(first);
        }

        return result;
    }

}