//
// Created by dell on 20.04.2018.
//
#include <iostream>
#include <regex>
#include "Matrix.h"
using namespace std;
using namespace algebra;

int main(){
//    Matrix m1(1,1);
//    pair<size_t, size_t> size= m1.Size();
//    int **matrix=new int *[2];
//    for (int i=0; i<2; ++i){
//        matrix[i]=new int [2];
//    }
//    Matrix m2("[1 2 3i1; 2 4i2 2]");
//    m2.Print();
//    Matrix m3("[2 1i1 1i1; 0 2 1i4]");
//    m3.Print();
//    Matrix m4= m2.Sub(m2);
//    cout<<"Zuzia"<<endl;
//    m4.Print();
    Matrix m1{{1.0i, 0., 0.}, {0., 1.0i, 0.}, {0., 0., 1.0i}};
    const complex<double> &first = m1.matrix[0][0];
    return 0;
}
