//
// Created by dell on 15.03.2018.
//

#ifndef JIMP_EXERCISES_XORCYPHERBREAKER_H
#define JIMP_EXERCISES_XORCYPHERBREAKER_H


#include <string>
#include <vector>
#include <algorithm>

using std::find;

std::string XorCypherBreaker(const std::vector<char> &cryptogram,
                             int key_length,
                             const std::vector<std::string> &dictionary);

#endif //JIMP_EXERCISES_XORCYPHERBREAKER_H
