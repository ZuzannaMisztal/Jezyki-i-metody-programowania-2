//
// Created by dell on 22.03.2018.
//

#ifndef JIMP_EXERCISES_TINYURLCODEC_H
#define JIMP_EXERCISES_TINYURLCODEC_H

#include <utility>
#include <string>
#include <array>
#include <memory>
#include <map>



namespace tinyurl{

    struct TinyUrlCodec{
        std::map<std::array<char, 6>,std::string> hash_to_url;
    };
    
    std::unique_ptr<TinyUrlCodec> Init();
    void NextHash(std::array<char, 6> *state);
    std::string Encode(const std::string &url, std::unique_ptr<TinyUrlCodec> *codec);
    std::string Decode(const std::unique_ptr<TinyUrlCodec> &codec, const std::string &hash);
    void increment(std::array<char,6> *state, int position);
}

#endif //JIMP_EXERCISES_TINYURLCODEC_H
