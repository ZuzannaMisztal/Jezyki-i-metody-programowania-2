//
// Created by dell on 06.06.2018.
//

#include "../tree/Tree.h"
#include "PreOrderTreeIterators.h"
#include "PostOrderTreeIterators.h"
#include <vector>
#ifndef JIMP_EXERCISES_TREEITERATORS_H
#define JIMP_EXERCISES_TREEITERATORS_H

namespace tree {


    //IN-ORDER
    template<typename T>
    class InOrderTreeIterator {
    public:
        explicit InOrderTreeIterator(std::shared_ptr<Tree<T>> root) {
            PlaceInOrder(root);
            index = 0;
        }

        void PlaceInOrder(std::shared_ptr<Tree<T>> tree) {
            if (tree->left_) PlaceInOrder(tree->left_);
            order_.push_back(tree);
            if (tree->right_) PlaceInOrder(tree->right_);
        }

        InOrderTreeIterator<T> End() {
            index = order_.size();
            return *this;
        }

        InOrderTreeIterator<T> operator++() {
            index++;
            return *this;
        }

        T operator*() {
            return order_[index]->Value();

        }

        bool operator!=(const InOrderTreeIterator &other) const {
            return other.index != index;
        }

    private:
        std::vector<std::shared_ptr<Tree<T>>> order_;
        int index;
    };

    template<typename T>
    class InOrderTreeView {
    public:
        explicit InOrderTreeView(Tree<T> *tree) : root_{std::make_shared<Tree<T>>(*tree)} {};

        InOrderTreeIterator<T> begin() {
            return InOrderTreeIterator<T>(root_);
        }

        InOrderTreeIterator<T> end() {
            return InOrderTreeIterator<T>(root_).End();
        }

    private:
        std::shared_ptr<Tree<T>> root_;
    };

    template<typename T>
    InOrderTreeView<T> InOrder(Tree<T> *tree) {
        return InOrderTreeView<T>(tree);
    }


}

#endif //JIMP_EXERCISES_TREEITERATORS_H