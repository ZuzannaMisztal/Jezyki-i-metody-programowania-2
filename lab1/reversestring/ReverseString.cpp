//
// Created by dell on 05.03.2018.
//

#include "ReverseString.h"


std::string Reverse(std::string str) {
    if (str[0]=='\0'){
        return (std::string());
    }
    char letter=str[0];
    return Reverse(str.substr(1))+letter;
}
