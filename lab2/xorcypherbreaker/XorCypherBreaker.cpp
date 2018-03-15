//
// Created by dell on 15.03.2018.
//

#include "XorCypherBreaker.h"



std::string XorCypherBreaker(const std::vector<char> &cryptogram, int key_length, const std::vector<std::string> &dictionary) {
    for (int i = 97; i < 123; ++i) {
        for (int j = 97; j < 123; ++j) {
            for (int k = 97; k < 123; ++k) {
                int counter = 0;
                int xored;
                std::string decrypted;
                for (char n:cryptogram) {
                    if (counter % 3 == 0) {
                        xored = n ^ i;
                    } else if (counter % 3 == 1) {
                        xored = n ^ j;
                    } else {
                        xored = n ^ k;
                    }
                    char decrypted_char = char(xored);
                    decrypted += decrypted_char;
                    ++counter;
                }
                int occurances = 0;
                for (std::string word:dictionary) {
                    std::string::size_type pos = 0;
                    std::string word1=" ";
                    word1.append(word);
                    word1+=' ';
                    while ((pos = decrypted.find(word1, pos)) != std::string::npos){
                        pos += word1.length();
                        ++occurances;
                    }
                }
                if (occurances >= decrypted.length()/5*0.3) {
                    std::string key;
                    key += char(i);
                    key += char(j);
                    key += char(k);
                    return key;
                }
            }
        }
    }
}


