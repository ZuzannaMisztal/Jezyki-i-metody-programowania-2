//
// Created by dell on 22.03.2018.
//

#include <iostream>
#include "TinyUrl.h"

    std::unique_ptr<tinyurl::TinyUrlCodec> tinyurl::Init() {
        tinyurl::TinyUrlCodec tmp;
        tmp.hash_to_url.emplace(std::array<char, 6> {'0','0','0','0','0','0'}, "init");
        return std::make_unique<tinyurl::TinyUrlCodec>(tmp);
    }

    void tinyurl::increment(std::array<char, 6> *state, const int position) {
        const char asciicode = (*state)[position];

        if ((asciicode > 47 && asciicode < 57) || (asciicode > 64 && asciicode < 90) ||
            (asciicode > 96 && asciicode < 122)) {
            (*state)[position] = asciicode + 1;
        } else if (asciicode == 57) {
            (*state)[position] = 'A';
        } else if (asciicode == 90) {
            (*state)[position] = 'a';
        } else if (asciicode == 122) {
            (*state)[position] = '0';
            if(position != 0) {
                tinyurl::increment(state, position - 1);
            }
        }
    }

    void tinyurl::NextHash(std::array<char, 6> *state) {
        tinyurl::increment(state, 5);
    }

    std::string tinyurl::Encode(const std::string &url, std::unique_ptr<tinyurl::TinyUrlCodec> *codec) {
            auto it = (*codec)->hash_to_url.end();
            auto hash = it->first;
            NextHash(&hash);
            (*codec)->hash_to_url.emplace(hash, url);
        std::string tmp = "";
        for(int i=0; i<6; i++){
            tmp+=hash[i];
        }
        return tmp;
    }

    std::string tinyurl::Decode(const std::unique_ptr<tinyurl::TinyUrlCodec> &codec, const std::string &hash) {
        std::array<char, 6> tmp;
        for(int i=0; i<6; i++){
            tmp[i] = hash[i];
        }
        return (*codec).hash_to_url[tmp];
    }