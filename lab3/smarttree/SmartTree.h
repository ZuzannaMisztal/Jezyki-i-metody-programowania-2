//
// Created by dell on 23.03.2018.
//

#ifndef JIMP_EXERCISES_SMARTTREE_H
#define JIMP_EXERCISES_SMARTTREE_H

#include <ostream>
#include <string>
#include <memory>
#include <iostream>
#include <sstream>

namespace datastructures
{

    struct SmartTree
    {
        int value;
        std::unique_ptr <SmartTree> right;
        std::unique_ptr <SmartTree> left;

    };
    std::unique_ptr <SmartTree> CreateLeaf(int value);
    std::unique_ptr <SmartTree> InsertLeftChild(std::unique_ptr<SmartTree> tree, std::unique_ptr<SmartTree> left_subtree);
    std::unique_ptr <SmartTree> InsertRightChild(std::unique_ptr<SmartTree> tree, std::unique_ptr<SmartTree> right_subtree);
    void PrintTreeInOrder(const std::unique_ptr<SmartTree> &unique_ptr, std::ostream *out);
    void PrintTreeInOrderToString(const std::unique_ptr<SmartTree> &unique_ptr, std::string *string_tree);
    std::string DumpTree(const std::unique_ptr<SmartTree> &tree);
    std::unique_ptr <SmartTree> RestoreTree(const std::string &tree);
    std::unique_ptr <SmartTree> RestoreTreeAddonRecursive(const std::string &tree, int *iterator);

}


#endif //JIMP_EXERCISES_SMARTTREE_H
