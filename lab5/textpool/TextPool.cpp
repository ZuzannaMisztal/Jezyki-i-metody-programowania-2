//
// Created by dell on 14.04.2018.
//

#include "TextPool.h"

std::experimental::string_view pool::TextPool::Intern(const std::string &str) {
    auto n=pula.emplace(str);
    return std::experimental::string_view(*n.first);
}

size_t pool::TextPool::StoredStringCount() const {
    return pula.size();
}

pool::TextPool::TextPool(const std::initializer_list<std::string> &elements) : pula{elements}{}

pool::TextPool &pool::TextPool::operator=(pool::TextPool &&other) {
    if (this!=&other) {
        this->pula=std::move(other.pula);
    }
    return *this;
}