//
// Created by dell on 02.06.2018.
//

#ifndef JIMP_EXERCISES_TREE_H
#define JIMP_EXERCISES_TREE_H

//#include <memory>
//
//namespace tree{
//    template<typename T>
//    class Tree {
//    private:
//        T data_;
//        std::shared_ptr<Tree<T>> left_child_;
//        std::shared_ptr<Tree<T>> right_child_;
//        size_t size;
//    public:
//        Tree(const T &data=T()) {
//            data_=data;
//            left_child_= nullptr;
//            right_child_=nullptr;
//            size=1;
//        }
////        void Insert(const T &elem){
////            std::unique_ptr<T> tmp = nullptr;
////            while(true){
////                if(elem<data_){
////                    if(left_child_==nullptr){
////                        left_child_ = std::make_unique<Tree<T>>(elem);
////                        ++size;
////                        break;
////                    }
////                    else{
////                        left_child_->Insert(elem);
////                    }
////                }
////                if(elem>=data_){
////                    if(right_child_==nullptr){
////                        right_child_ = std::make_unique<Tree<T>>(elem);
////                        ++size;
////                        break;
////                    }
////                    else{
////                        right_child_->Insert(elem);
////                    }
////                }
////            }
////        }
//
//        void Insert(const T &element){
//            if (element<data_){
//                if (left_child_== nullptr){
//                    left_child_=std::make_shared<Tree<T>>(Tree(element));
//                    ++size;
//                } else{
//                    left_child_->Insert(element);
//                }
//            } else{
//                if (right_child_== nullptr){
//                    right_child_=std::make_shared<Tree<T>>(Tree(element));
//                    ++size;
//                } else{
//                    right_child_->Insert(element);
//                }
//            }
//        }
//        T Value()const{
//            return data_;
//        }
//
//        size_t Depth()const{
//            if (left_child_== nullptr and right_child_== nullptr){
//                return 1;
//            }
//            if (left_child_->Depth()>=right_child_->Depth()){
//                return 1+left_child_->Depth();
//            } else{
//                return 1+right_child_->Depth();
//            }
//        }
//        size_t Size()const{
//            return size;
//        }
//    };
//}
//


#include <memory>
namespace tree
{
    template <typename T>
    class Tree {
        std::shared_ptr<T> value_;
        size_t size;
    public:
        Tree() : left_{nullptr}, right_{nullptr}{};
        explicit Tree(const T & value): right_{nullptr}, left_{nullptr}, value_{std::make_shared<T>(value)}, size(1){};

        T Value() const {
            return *value_;
        }

        std::shared_ptr<Tree<T>> Left() const {
            return left_;
        }

        std::shared_ptr<Tree<T>> Right() const {
            return right_;
        }



        void Insert(const T & element) {
            ++size;
            if(element<*value_) {
                if (left_== nullptr) {
                    left_ = std::make_shared<Tree<T>>(Tree(element));
                }
                else {
                    left_->Insert(element);
                }

            }
            else {
                if(right_== nullptr) {
                    right_ = std::make_shared<Tree<T>>(Tree(element));
                } else {
                    right_ ->Insert(element);
                }
            }
        }

        bool Find(const T &element) {
            if (value_ == element) return true;
            if(value_>element) {
                if(left_== nullptr) return false;
                else {
                    left_ ->Find(element);
                }
            }
            else {
                if(right_== nullptr) return false;
                else {
                    right_ ->Find(element);
                }
            }
        }

        size_t Size() {
            return size;
        }

        size_t Depth() {
            if(!left_&&!right_) return 1;
            if(!left_) return 1 + right_->Depth();
            if(!right_) return 1+ left_->Depth();
            return std::max(right_->Depth(),left_->Depth())+1;
        }

        std::shared_ptr<Tree<T>> Root() {
            return std::make_shared<Tree<T>>(*this);
        }

        std::shared_ptr<Tree<T>> left_;
        std::shared_ptr<Tree<T>> right_;
    };
}

#endif //JIMP_EXERCISES_TREE_H
