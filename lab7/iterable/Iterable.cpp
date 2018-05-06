//
// Created by dell on 05.05.2018.
//

#include <vector>
#include "Iterable.h"

utility::ZipperIterator::ZipperIterator(std::vector<int>::const_iterator left_begin,
                                        std::vector<std::string>::const_iterator right_begin,
                                        std::vector<int>::const_iterator left_end,
                                        std::vector<std::string>::const_iterator right_end) : IterableIterator(left_begin, right_begin, left_end, right_end){}

std::pair<int, std::string> utility::ZipperIterator::Dereference() const {
    int first;
    if (l_b!=l_e){
        first=*l_b;
    } else{
        first=*(l_b-1);
    }
    std::string second;
    if(r_b!=r_e){
        second=*r_b;
    } else{
        second=*(r_b-1);
    }
    return std::pair<int, std::string>(first, second);
}

utility::IterableIterator &utility::ZipperIterator::Next() {
    if (l_b!= l_e && r_b!= r_e) {
        ++l_b;
        ++r_b;
    }
    return *this;
}

bool utility::ZipperIterator::NotEquals(const std::unique_ptr<utility::IterableIterator> &o) const {
    return (l_b != o->GetL_B() or r_b != o->GetR_B());
}

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
    return utility::IterableIteratorWrapper(this->ConstBegin());
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

utility::Zipper::Zipper(std::vector<int> vi, std::vector<std::string> vs){
    int_vector=move(vi);
    string_vector=move(vs);
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

utility::Enumerate::Enumerate(std::vector<std::string> vs) {
    int_vector.clear();
    for (int i = 0; i < vs.size(); ++i) {
        int_vector.emplace_back(i);
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


utility::EnumerateIterator::EnumerateIterator(std::vector<int>::const_iterator left_begin,
                                              std::vector<std::string>::const_iterator right_begin,
                                              std::vector<int>::const_iterator left_end,
                                              std::vector<std::string>::const_iterator right_end) : IterableIterator(left_begin, right_begin, left_end, right_end){}

std::pair<int, std::string> utility::EnumerateIterator::Dereference() const {
    return std::pair<int, std::string>(*l_b, *r_b);
}

utility::IterableIterator &utility::EnumerateIterator::Next() {
    ++l_b;
    ++r_b;
    return *this;
}

bool utility::EnumerateIterator::NotEquals(const std::unique_ptr<utility::IterableIterator> &o) const {
    return (l_b == o->GetL_B() and r_b == o->GetR_B());
}


utility::ProductIterator::ProductIterator(std::vector<int>::const_iterator left_begin,
                                              std::vector<std::string>::const_iterator right_begin,
                                              std::vector<int>::const_iterator left_end,
                                              std::vector<std::string>::const_iterator right_end) : IterableIterator(left_begin, right_begin, left_end, right_end){}

std::pair<int, std::string> utility::ProductIterator::Dereference() const {
    return std::pair<int, std::string>(*l_b, *r_b);
}

utility::IterableIterator &utility::ProductIterator::Next() {
    ++l_b;
    ++r_b;
    return *this;
}

bool utility::ProductIterator::NotEquals(const std::unique_ptr<utility::IterableIterator> &o) const {
    return (l_b == o->GetL_B() and r_b == o->GetR_B());
}


utility::IterableIterator::IterableIterator(std::vector<int>::const_iterator left_begin,
                                            std::vector<std::string>::const_iterator right_begin,
                                            std::vector<int>::const_iterator left_end,
                                            std::vector<std::string>::const_iterator right_end) {
    l_b=left_begin;
    r_b=right_begin;
    l_e=left_end;
    r_e=right_end;
}

std::vector<int>::const_iterator utility::IterableIterator::GetL_B() {
    return l_b;
}

std::vector<std::string>::const_iterator utility::IterableIterator::GetR_B() {
    return r_b;
}

utility::Product::Product(std::vector<int> vi, std::vector<std::string> vs) {
    for(auto v: vi){
       for(auto e: vs){
           int_vector.emplace_back(v);
           string_vector.emplace_back(e);
       }
    }
}

std::unique_ptr<utility::IterableIterator> utility::Product::ConstBegin() const {
    ProductIterator tmp(int_vector.begin(), string_vector.begin(), int_vector.end(), string_vector.end());
    std::unique_ptr<IterableIterator> result = std::make_unique<ProductIterator>(tmp);
    return result;
}

std::unique_ptr<utility::IterableIterator> utility::Product::ConstEnd() const {
    ProductIterator tmp(int_vector.end(), string_vector.end(), int_vector.end(), string_vector.end());
    std::unique_ptr<IterableIterator> result = std::make_unique<ProductIterator>(tmp);
    return result;
}
