//
// Created by dell on 23.03.2018.
//
#include <ostream>
#include <memory>
#include <string>
#include <iostream>
#include <sstream>

#include "SmartTree.h"

namespace datastructures {
    std::unique_ptr <SmartTree> CreateLeaf(int value) {
        std::unique_ptr <SmartTree> pointer = std::make_unique<SmartTree>();
        pointer->value = value;
        pointer->left = nullptr;
        pointer->right = nullptr;
        return pointer;
    }

    std::unique_ptr <SmartTree>
    InsertLeftChild(std::unique_ptr <SmartTree> tree, std::unique_ptr <SmartTree> left_subtree) {
        tree->left = move(left_subtree);
        return tree;
    }

    std::unique_ptr <SmartTree>
    InsertRightChild(std::unique_ptr <SmartTree> tree, std::unique_ptr <SmartTree> right_subtree) {
        tree->right = move(right_subtree);
        return tree;
    }

    void PrintTreeInOrder(const std::unique_ptr <SmartTree> &unique_ptr, std::ostream *out) {
        if (unique_ptr != nullptr) {
            PrintTreeInOrder(unique_ptr->left, out);
            *out << unique_ptr->value << ", ";
            PrintTreeInOrder(unique_ptr->right, out);
        }
    }

    void PrintTreeInOrderToString(const std::unique_ptr <SmartTree> &unique_ptr, std::string *string_tree) {
        int n = 32;
        if ((*string_tree).size() != 0) n = (*string_tree)[(*string_tree).size() - 1];
        if (unique_ptr != nullptr) {
            if (n == 93) *string_tree += " ";
            *string_tree += "[";
            *string_tree += std::to_string(unique_ptr->value);
            *string_tree += " ";
            PrintTreeInOrderToString(unique_ptr->left, string_tree);
            PrintTreeInOrderToString(unique_ptr->right, string_tree);
            *string_tree += "]";
        } else {
            if (n == 32) *string_tree += "[none]";
            else *string_tree += " [none]";
        }
    }

    std::string DumpTree(const std::unique_ptr <SmartTree> &tree) {
        std::string string_tree;
        PrintTreeInOrderToString(tree, &string_tree);
        return string_tree;
    }

    std::unique_ptr <SmartTree> RestoreTree(const std::string &tree) {
        int i = 0;
        return RestoreTreeAddonRecursive(tree, &i);
    }


    std::unique_ptr <SmartTree> RestoreTreeAddonRecursive(const std::string &tree, int *i) {
        std::stringstream ss;
        std::string value_from_string;
        int value = 0;
        while (tree[*i] != '[' and tree[*i] != '\0') {
            (*i)++;
        }
        while ((tree[*i] != ' ') and (tree[*i] != ']')) {
            if (tree[*i] == '[') {
                (*i)++;
                continue;
            }
            value_from_string += tree[*i];
            (*i)++;
        }
        if (value_from_string.compare("none") == 0) return nullptr;

        ss << value_from_string;
        ss >> value;

        std::unique_ptr <SmartTree> leaf = CreateLeaf(value);
        while (tree[*i] != '[' and tree[*i] != '\0') {
            (*i)++;
        }
        leaf->left = RestoreTreeAddonRecursive(tree, i);
        while (tree[*i] != '[' and tree[*i] != '\0') {
            (*i)++;
        }
        leaf->right = RestoreTreeAddonRecursive(tree, i);
        return leaf;
    }
}