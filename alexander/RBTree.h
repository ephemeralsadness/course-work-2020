#pragma once

#include <istream>
#include <ostream>

#include "ServicePrice.h"
#include "../helpers/Vector.h"

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

        void Remove(key_t key) noexcept;

        template <typename Predicate>
        void Remove(key_t key, Predicate pred) noexcept;

        Vector<ServicePrice*> Find(key_t key) const noexcept;

        template <typename Predicate>
        Vector<ServicePrice*> Find(key_t key, Predicate pred) const noexcept;

        Vector<ServicePrice*> LookUp() const noexcept;

        void ReadToStream(std::istream& in) noexcept;

        void WriteToStream(std::ostream& out) const;
    private:

        struct Node {

        };

    };

}