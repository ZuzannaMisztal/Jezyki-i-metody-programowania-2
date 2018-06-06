//
// Created by dell on 23.05.2018.
//

#include "FactoryMethod.h"

factoryMethod::MyType::MyType() {
    say="hello";
}

std::basic_string<char> factoryMethod::MyType::SayHello() {
    return say;
}
