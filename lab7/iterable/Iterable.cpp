//
// Created by dell on 05.05.2018.
//

#include <vector>
#include "Iterable.h"

utility::IterableIterator::IterableIterator(std::vector<int>::const_iterator left_begin,
                                            std::vector<std::string>::const_iterator right_begin,
                                            std::vector<int>::const_iterator left_end,
                                            std::vector<std::string>::const_iterator right_end) {
    l_b=left_begin;
    r_b=right_begin;
    l_e=left_end;
    r_e=right_end;
    l_current=left_begin;
    r_current=right_begin;
}


// Zipper Iterator

utility::ZipperIterator::ZipperIterator(std::vector<int>::const_iterator left_begin,
                                        std::vector<std::string>::const_iterator right_begin,
                                        std::vector<int>::const_iterator left_end,
                                        std::vector<std::string>::const_iterator right_end) : IterableIterator(left_begin, right_begin, left_end, right_end){}

std::pair<int, std::string> utility::ZipperIterator::Dereference() const {
    int first;
    if (l_current!=l_e){
        first=*l_current;
    } else{
        first=*(l_current-1);
    }
    std::string second;
    if(r_current!=r_e){
        second=*r_current;
    } else{
        second=*(r_current-1);
    }
    return std::pair<int, std::string>(first, second);
}

utility::IterableIterator &utility::ZipperIterator::Next() {
    if (l_current!= l_e && r_current!= r_e) {
        ++l_current;
        ++r_current;
    }
    return *this;
}

bool utility::ZipperIterator::NotEquals(const std::unique_ptr<utility::IterableIterator> &o) const {
    return (l_current != o->GetL_Current() or r_current != o->GetR_Current());
}



//Enumerate Iterator

utility::EnumerateIterator::EnumerateIterator(std::vector<int>::const_iterator left_begin,
                                              std::vector<std::string>::const_iterator right_begin,
                                              std::vector<int>::const_iterator left_end,
                                              std::vector<std::string>::const_iterator right_end) : IterableIterator(left_begin, right_begin, left_end, right_end){}

std::pair<int, std::string> utility::EnumerateIterator::Dereference() const {
    return std::pair<int, std::string>(*l_current, *r_current);
}

utility::IterableIterator &utility::EnumerateIterator::Next() {
    ++l_current;
    ++r_current;
    return *this;
}

bool utility::EnumerateIterator::NotEquals(const std::unique_ptr<utility::IterableIterator> &o) const {
    return !(l_current == o->GetL_Current() and r_current == o->GetR_Current());
}



//Product Iterator

utility::ProductIterator::ProductIterator(std::vector<int>::const_iterator left_begin,
                                          std::vector<std::string>::const_iterator right_begin,
                                          std::vector<int>::const_iterator left_end,
                                          std::vector<std::string>::const_iterator right_end) : IterableIterator(left_begin, right_begin, left_end, right_end){}

std::pair<int, std::string> utility::ProductIterator::Dereference() const {
    return std::pair<int, std::string>(*l_current, *r_current);
}

utility::IterableIterator &utility::ProductIterator::Next() {
    if (l_current!=l_e) {
        ++r_current;
        if (r_current==r_e) {
            ++l_current;
            r_current = r_b;
        }
    }
    if (l_current==l_e){
        r_current=r_e;
    }
    return *this;
}

bool utility::ProductIterator::NotEquals(const std::unique_ptr<utility::IterableIterator> &o) const {
    return !(l_current == o->GetL_Current() and r_current == o->GetR_Current());
}



//Iterable Iterator Wrapper

utility::IterableIteratorWrapper::IterableIteratorWrapper(std::unique_ptr<utility::IterableIterator> iterator) {
    it=move(iterator);
}


bool utility::IterableIteratorWrapper::operator!=(const utility::IterableIteratorWrapper &other) const {
    return it->NotEquals(other.it);
}

std::pair<int, std::string> utility::IterableIteratorWrapper::operator*() const{
    return it->Dereference();
}

utility::IterableIteratorWrapper &utility::IterableIteratorWrapper::operator++() {
    it->Next();
    return *this;
}

utility::IterableIteratorWrapper utility::Iterable::cbegin() const {
    std::unique_ptr<IterableIterator> p = ConstBegin();
    return IterableIteratorWrapper(move(p));
}

utility::IterableIteratorWrapper utility::Iterable::cend() const {
    return utility::IterableIteratorWrapper(this->ConstEnd());
}

utility::IterableIteratorWrapper utility::Iterable::begin() const {
    return utility::IterableIteratorWrapper(this->cbegin());
}

utility::IterableIteratorWrapper utility::Iterable::end() const {
    return utility::IterableIteratorWrapper(this->cend());
}


//Zipper

utility::Zipper::Zipper(std::vector<int> vi, std::vector<std::string> vs){
    int_vector=move(vi);
    string_vector=move(vs);
    int not_equal=int_vector.size()-string_vector.size();
    if (not_equal>0){
        std::string to_emplace=string_vector[string_vector.size()-1];
        for (int i=0; i<not_equal; ++i){
            string_vector.emplace_back(to_emplace);
        }
    }
    if (not_equal<0){
        int to_emplace=int_vector[int_vector.size()-1];
        for (int i=0; i<-not_equal; ++i){
            int_vector.emplace_back(to_emplace);
        }
    }
}

std::unique_ptr<utility::IterableIterator> utility::Zipper::ConstBegin() const {
    ZipperIterator tmp(int_vector.begin(), string_vector.begin(), int_vector.end(), string_vector.end());
    std::unique_ptr<IterableIterator> result = std::make_unique<ZipperIterator>(tmp);
    return result;
}

std::unique_ptr<utility::IterableIterator> utility::Zipper::ConstEnd() const {
    ZipperIterator tmp(int_vector.end(), string_vector.end(), int_vector.end(), string_vector.end());
    std::unique_ptr<IterableIterator> result = std::make_unique<ZipperIterator>(tmp);
    return result;
}


//Enumerate

utility::Enumerate::Enumerate(std::vector<std::string> vs) {
    int_vector.clear();
    for (int i = 0; i < vs.size(); ++i) {
        int_vector.emplace_back(i+1);
    }
    string_vector = move(vs);
}

std::unique_ptr<utility::IterableIterator> utility::Enumerate::ConstBegin() const {
    EnumerateIterator tmp(int_vector.begin(), string_vector.begin(), int_vector.end(), string_vector.end());
    std::unique_ptr<IterableIterator> result = std::make_unique<EnumerateIterator>(tmp);
    return result;
}

std::unique_ptr<utility::IterableIterator> utility::Enumerate::ConstEnd() const {
    EnumerateIterator tmp(int_vector.end(), string_vector.end(), int_vector.end(), string_vector.end());
    std::unique_ptr<IterableIterator> result = std::make_unique<EnumerateIterator>(tmp);
    return result;
}


//Product

utility::Product::Product(std::vector<int> vi, std::vector<std::string> vs){
    int_vector=std::move(vi);
    string_vector=std::move(vs);
}

std::unique_ptr<utility::IterableIterator> utility::Product::ConstBegin() const {
    ProductIterator tmp(int_vector.begin(), string_vector.begin(), int_vector.end(), string_vector.end());
    std::unique_ptr<IterableIterator> result = std::make_unique<ProductIterator>(tmp);
    return move(result);
}

std::unique_ptr<utility::IterableIterator> utility::Product::ConstEnd() const {
    ProductIterator tmp(int_vector.end(), string_vector.end(), int_vector.end(), string_vector.end());
    std::unique_ptr<IterableIterator> result = std::make_unique<ProductIterator>(tmp);
    return move(result);
}


//Getters

std::vector<int>::const_iterator utility::IterableIterator::GetL_Current() {
    return l_current;
}

std::vector<std::string>::const_iterator utility::IterableIterator::GetR_Current() {
    return r_current;
}