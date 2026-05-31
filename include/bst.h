// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <vector>
#include <utility>

template <typename T>
class BST {
 private:
    struct Node {
        T value;
        int count;
        Node* left;
        Node* right;
        explicit Node(T val) : value(val), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void destroyTree(Node* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    Node* insertNode(Node* node, T value) {
        if (!node) {
            return new Node(value);
        }
        if (value < node->value) {
            node->left = insertNode(node->left, value);
        } else if (value > node->value) {
            node->right = insertNode(node->right, value);
        } else {
            node->count++;
        }
        return node;
    }

    int getDepth(Node* node) const {
        if (!node) return -1;
        int leftDepth = getDepth(node->left);
        int rightDepth = getDepth(node->right);
        return 1 + std::max(leftDepth, rightDepth);
    }

    int searchNode(Node* node, T value) const {
        if (!node) return 0;
        if (value == node->value) return node->count;
        if (value < node->value) {
            return searchNode(node->left, value);
        } else {
            return searchNode(node->right, value);
        }
    }

    void extract(Node* node, std::vector<std::pair<T, int>>& container) const {
        if (node) {
            extract(node->left, container);
            container.push_back({node->value, node->count});
            extract(node->right, container);
        }
    }

 public:
    BST() : root(nullptr) {}
    ~BST() { destroyTree(root); }

    void insert(T value) {
        root = insertNode(root, value);
    }

    int depth() const {
        if (!root) return 0;
        return getDepth(root);
    }

    int search(T value) const {
        return searchNode(root, value);
    }

    void getAll(std::vector<std::pair<T, int>>& container) const {
        extract(root, container);
    }
};

#endif  // INCLUDE_BST_H_
