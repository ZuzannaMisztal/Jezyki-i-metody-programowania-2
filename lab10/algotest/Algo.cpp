//
// Created by dell on 16.05.2018.
//

#include "Algo.h"

std::set<std::string> algo::Keys(const std::map<std::string, int> &m) {
    std::set<std::string> result;
    std::transform(m.begin(), m.end(), std::inserter(result, result.end()), [](std::pair<std::string, int> p)->std::string{return p.first;});
    return result;
}

std::vector<int> algo::Values(const std::map<std::string, int> &m) {
    std::vector<int> result;
    std::transform(m.begin(), m.end(), std::back_inserter(result), [](std::pair<std::string, int> pair_)->int{return pair_.second;});
    return result;
}

std::vector<std::string> algo::MapToString(const std::vector<double> &v) {
    std::vector<std::string> result;
    std::transform(v.begin(), v.end(), std::back_inserter(result), [](double d)->std::string{return std::to_string(d);});
    return result;
}

std::vector<int> algo::DivisableBy(const std::vector<int> &m, int divisor) {
    std::vector<int> result;
    std::copy_if(m.begin(), m.end(), std::back_inserter(result), [divisor](int i){return (i%divisor==0);});
    return result;
}



void algo::SortInPlace(std::vector<int> *v) {

}

std::vector<int> algo::Sort(const std::vector<int> &v) {
    return std::vector<int>();
}

void algo::SortByFirstInPlace(std::vector<std::pair<int, int>> *v) {

}

void algo::SortBySecondInPlace(std::vector<std::pair<int, int>> *v) {

}

void algo::SortByThirdInPlace(std::vector<std::tuple<int, int, int>> *v) {

}

std::string algo::Join(const std::string &joiner, const std::vector<double> &v) {
    return std::string();
}

int algo::Sum(const std::vector<int> &v) {
    return 0;
}

int algo::Product(const std::vector<int> &v) {
    return 0;
}

bool algo::Contains(const std::vector<int> &v, int element) {
    return (std::find(v.begin(), v.end(), element)!=v.end());
}

bool algo::ContainsKey(const std::map<std::string, int> &v, const std::string &key) {
    return v.find(key)!=v.end();
}

bool algo::ContainsValue(const std::map<std::string, int> &v, int value) {
    std::vector<int> to_find = Values(v);
    return (std::find(to_find.begin(), to_find.end(), value)!=to_find.end());
}

std::vector<std::string> algo::RemoveDuplicates(const std::vector<std::string> &v) {
    return std::vector<std::string>();
}

void algo::RemoveDuplicatesInPlace(std::vector<std::string> *v) {

}

void algo::InitializeWith(int initial_value, std::vector<int> *v) {

}

std::vector<int> algo::InitializedVectorOfLength(int length, int initial_value) {
    return std::vector<int>();
}

void algo::CopyInto(const std::vector<int> &v, int n_elements, std::vector<int> *out) {

}

int algo::HowManyShortStrings(const std::vector<std::string> &v, int inclusive_short_length) {
    return 0;
}
