//
// Created by dell on 06.03.2018.
//

#include "DoubleBasePalindromes.h"
//#include "../reversestring/ReverseString.cpp"


uint64_t DoubleBasePalindromes(int max_value_exclusive) {
    uint64_t sum=0;
    for (int i=1; i<max_value_exclusive; i++){
        std::string s = std::to_string(i); //zmiana z int na string
        if (s== Reverse(s)){
            if (ChangeBase(i)== Reverse(ChangeBase(i))){
                sum+=i;
            }
        }
    }
    return sum;
}

std::string ChangeBase(int a) {
    std::string result;
    while (a>0){
        result+=std::to_string(a%2);
        a=a/2;
    }
    return result;
}

