//
// Created by dell on 06.03.2018.
//

#include "Palindrome.h"

std::string reverse1(std::string str) {
    if (str[0]=='\0'){
        return (std::string());
    }
    char letter=str[0];
    return reverse1(str.substr(1))+letter;
}

bool is_palindrome(std::string str) {
    return str == reverse1(str);
}
