//
// Created by dell on 22.04.2018.
//

#include "WordCounter.h"

datastructures::WordCounter::WordCounter() {
    word_counter_.clear();
}

datastructures::WordCounter::WordCounter(const std::initializer_list<datastructures::Word> &elements) {
    for (const auto &n:elements){
        if (word_counter_.count(n)==0){
            word_counter_.emplace(n,1);
        } else{
            ++word_counter_.find(n)->second;
        }
    }
}

int datastructures::WordCounter::DistinctWords() {
    return word_counter_.size();
}

int datastructures::WordCounter::TotalWords() {
    int result=0;
    for(const auto &n:word_counter_){
        result+=n.second.getCounter_();
    }
    return result;
}

datastructures::Counts datastructures::WordCounter::operator[](const std::string &s) {
    auto i=word_counter_.find(Word(s));
    if (i!=word_counter_.end()){
        return i->second;
    } else{
        return Counts(0);
    }
}

std::set<datastructures::Word> datastructures::WordCounter::Words() {
    std::set<Word> result;
    for (const auto &n:word_counter_){
        result.emplace(n.first);
    }
    return result;
}

datastructures::Word::Word(std::string word) {
    key_=word;
}

datastructures::Word::Word() {
    key_="";
}

bool datastructures::Word::operator<(const datastructures::Word &w) const {
    return (key_<w.key_);
}

bool datastructures::Word::operator==(const datastructures::Word &w) const {
    return key_==w.key_;
}

datastructures::Counts::Counts() {
    counter_=0;
}

datastructures::Counts::Counts(int counter_) : counter_(counter_) {}

datastructures::Counts &datastructures::Counts::operator++() {
    ++counter_;
    return *this;
}

int datastructures::Counts::getCounter_() const {
    return counter_;
}

bool datastructures::Counts::operator==(const datastructures::Counts &c) const{
    return counter_==c.counter_;
}

bool datastructures::operator==(const int i, const datastructures::Counts &c) {
    return i==c.counter_;
}
