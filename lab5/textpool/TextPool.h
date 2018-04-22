//
// Created by dell on 14.04.2018.
//

#ifndef JIMP_EXERCISES_TEXTPOOL_H
#define JIMP_EXERCISES_TEXTPOOL_H


#include <experimental/string_view>
#include <initializer_list>
#include <string>
#include <set>

namespace pool {
    class TextPool {
    public:
        std::set<std::string> pula;
    public:
        //konstruktor domyślny
        TextPool() = default;
        TextPool(const TextPool &) = delete;
        TextPool(TextPool &&)= default;
        TextPool &operator=(TextPool &&);
        TextPool (const std::initializer_list<std::string> &elements);;

        std::experimental::string_view Intern(const std::string &str);
        size_t StoredStringCount() const;
    };
}


#endif //JIMP_EXERCISES_TEXTPOOL_H
