//
// Created by dell on 22.04.2018.
//

#ifndef JIMP_EXERCISES_WORDCOUNTER_H
#define JIMP_EXERCISES_WORDCOUNTER_H

#include <string>
#include <map>
#include <set>

namespace datastructures {
    class Word{
    private:
        std::string key_;
    public:
        Word();
        Word(std::string word);
        bool operator<(const Word &) const;
        bool operator==(const Word &) const;
    };

    class Counts{
    private:
        int counter_;
    public:
        Counts(int counter_);
        Counts();
        Counts &operator++();
        int getCounter_() const;
        bool operator==(const Counts &) const;

        friend bool operator==(const int, const Counts &);
    };

    bool operator==(const int, const Counts &);

    class WordCounter{
    private:
        std::map<datastructures::Word,datastructures::Counts> word_counter_;
    public:
        WordCounter(const std::initializer_list<datastructures::Word> &);
        WordCounter();
        int DistinctWords();
        int TotalWords();
        Counts operator[](const std::string &);
        std::set<Word> Words();
    };
}

#endif //JIMP_EXERCISES_WORDCOUNTER_H
