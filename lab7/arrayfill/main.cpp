//
// Created by dell on 18.04.2018.

#include <vector>
#include <ArrayFill.h>
using namespace arrays;

int main(){
    std::vector<int> vs;
//    UniformFill filler(2);
    SquaredFill filler(2);
    FillArray(1024, filler, &vs);
    return 0;
}