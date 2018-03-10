//
// Created by dell on 06.03.2018.
//
#include "Palindrome.h"
//#include "../reversestring/ReverseString.cpp"


bool IsPalindrome(std::string str) {
    return str == Reverse(str);
}
