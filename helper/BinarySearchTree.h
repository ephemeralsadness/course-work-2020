#pragma once

#include <utility>

template <typename Key, typename Value>
class BinarySearchTree {
public:
    BinarySearchTree() noexcept : root(nullptr) {}

    ~BinarySearchTree() noexcept {
        DeleteTree(root);
    }

    BinarySearchTree(const BinarySearchTree& tree) = delete;
    BinarySearchTree& operator = (const BinarySearchTree& tree) = delete;

    BinarySearchTree(BinarySearchTree&& tree) noexcept {
        root = tree.root;
        tree.root = nullptr;
    }
    BinarySearchTree& operator = (BinarySearchTree&& tree) noexcept {
        if (this != &tree) {
            DeleteTree(root);
            root = tree.root;
            tree.root = nullptr;
        }
        return *this;
    }

    bool Insert(Key key, Value value) noexcept {
        Node* prev = nullptr;
        Node* now = root;
        Node* to_insert = new Node {std::move(key), std::move(value), nullptr, nullptr};

        if (now == nullptr) {
            root = to_insert;
            return true;
        }

        while (now != nullptr) {
            prev = now;
            if (to_insert->key == now->key)
                return false;
            else if (to_insert->key < now->key)
                now = now->left;
            else
                now = now->right;
        }

        if (to_insert->key < prev->key)
            prev->left = to_insert;
        else
            prev->right = to_insert;

        return true;
    }

    bool Remove(const Key &key) noexcept {
        Node *prev = nullptr;
        Node *now = root;

        while (now != nullptr && now->data != key) {
            prev = now;
            if (key < now->data)
                now = now->left;
            else
                now = now->right;
        }

        if (now == nullptr)
            return false;

        if (now->left == nullptr || now->right == nullptr) {
            Node *replace;

            if (now->left == nullptr)
                replace = now->right;
            else
                replace = now->left;

            if (prev == nullptr)
                return true;

            if (now == prev->left)
                prev->left = replace;
            else
                prev->right = replace;

            delete now;
        } else {
            Node *p = nullptr;
            Node *temp;

            temp = now->right;
            while (temp->left != nullptr) {
                p = temp;
                temp = temp->left;
            }

            if (p != nullptr)
                p->left = temp->right;
            else
                now->right = temp->right;

            now->data = temp->data;
            delete temp;
        }
        return true;
    }

    Value& Find(const Key& key) noexcept {
        return const_cast<Value&>(
                static_cast<const BinarySearchTree*>(this)->Find(key)
        );
    }

    const Value& Find(const Key& key) const noexcept {
        Node* prev = nullptr;
        Node* now = root;

        while (now != nullptr) {
            prev = now;
            if (key == now->key)
                return now->value;
            else if (key < now->key)
                now = now->left;
            else
                now = now->right;
        }

        return nullptr;
    }

    template <typename Callback>
    void ForEach(Callback callback) const noexcept {
        LNRTraversal(root, callback);
    }

private:
    class Node {
        Key key;
        Value value;
        Node* left;
        Node* right;
    };

    void DeleteTree(Node* tree_root) noexcept {
        if (tree_root == nullptr)
            return;
        DeleteTree(tree_root->left);
        DeleteTree(tree_root->right);
        delete tree_root;
    }

    template <typename Callback>
    void LNRTraversal(Node* tree_root, Callback callback) const noexcept {
        if (tree_root == nullptr)
            return;
        LNRTraversal(tree_root->left);
        callback(tree_root->value);
        LNRTraversal(tree_root->right);
    }

    Node root;
};