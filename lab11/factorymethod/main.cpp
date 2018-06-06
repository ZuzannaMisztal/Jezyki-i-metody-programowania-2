//
// Created by dell on 23.05.2018.
//
#include "FactoryMethod.h"

using namespace factoryMethod;

int main(){
    int x=suma<int>(2,3);
    double a=suma<double>(2.1,2.3);
    int *p=&x;
    int y=Value(p);
    auto k=std::make_unique<int>(x);
    auto z=Value(move(k));
    return 0;
}