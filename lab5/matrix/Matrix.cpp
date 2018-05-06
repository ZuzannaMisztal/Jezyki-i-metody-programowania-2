//
// Created by dell on 20.04.2018.
//

#include <vector>
#include <algorithm>
#include <iostream>
#include "Matrix.h"

algebra::Matrix::Matrix(int rows, int columns) {
    number_of_rows=rows;
    number_of_columns=columns;
    DynamicArray();
}

void algebra::Matrix::DynamicArray() {
    this->matrix = new std::complex<double> *[this->number_of_rows];
    for (int i=0; i < this->number_of_rows; ++i){
        this->matrix[i]=new std::complex<double> [this->number_of_columns];
    }
    std::complex<double> complex_zero = 0.;
int n = 3;
    for(int i=0; i<number_of_rows; i++){
        for(int j=0; j<number_of_columns; j++){
            this->matrix[i][j] = complex_zero;
        }
    }
}

algebra::Matrix::~Matrix() {
    for (int i=0; i<number_of_rows; ++i){
        delete[] matrix[i];
    }
    delete[] matrix;
}

std::pair<size_t, size_t> algebra::Matrix::Size() const{
    std::pair<size_t, size_t> size;
    size.first=(size_t)number_of_rows;
    size.second=(size_t)number_of_columns;
    return size;
}

algebra::Matrix::Matrix(std::string matlab) {
    number_of_rows= static_cast<int>(std::count(matlab.begin(), matlab.end(), ';') + 1);
    size_t end_of_the_row= matlab.find(';');
    std::string matlab_row=matlab.substr(0,end_of_the_row);
    number_of_columns= static_cast<int>(std::count(matlab_row.begin(), matlab_row.end(), ' '))+1;
    DynamicArray();

    int i=1;
    if (matlab[1]==' '){
        ++i;
    }
    int current_row=0;
    int current_column=0;
    std::string number;
    for (;i<matlab.length(); ++i){
        if (matlab[i] != 'i' && matlab[i] != ' ' && matlab[i] != ';'&& matlab[i] !=']'){
            number+=matlab[i];
        }
        else if (matlab[i]=='i'){
            number+=',';
        }
        else if (matlab[i]==' '){
            std::istringstream is('(' + number + ')');
            std::complex<double> c;
            is >> c;
//            std::cout<<c<<std::endl;
            matrix[current_row][current_column]=c;
            ++current_column;
            number="";
        }
        else if (matlab[i]==';'){
            std::istringstream is('(' + number + ')');
            std::complex<double> c;
            is >> c;
//            std::cout<<c<<std::endl;
            matrix[current_row][current_column]=c;
            if (matlab[i+1]==' '){
                ++i;
            }
            ++current_row;
            current_column=0;
            number="";
        }
        else if (matlab[i]==']'){
            std::istringstream is('(' + number + ')');
            std::complex<double> c;
            is >> c;
//            std::cout<<c<<std::endl;
            matrix[current_row][current_column]=c;
        }
    }
}

std::string algebra::Matrix::Print() const {
    std::stringstream s;
    s<<"[";
    bool f=true;
    for (int i=0; i<number_of_rows; ++i){
        if (f){
            f= false;
        } else{
            s<<"; ";
        }
        bool first=true;
        for (int j=0; j<number_of_columns; ++j){
            if (!first) {
                s << ", ";
            } else{
                first= false;
            }
            s<< (matrix[i][j]).real() << "i" << (matrix[i][j]).imag();
        }
    }
    s<<"]";
    return s.str();
}

algebra::Matrix algebra::Matrix::Add(const algebra::Matrix &m) const{
    algebra::Matrix result(number_of_rows,number_of_columns);
    if (this->Size()==m.Size()){
        for (int i=0; i<number_of_rows; ++i){
            for (int j=0; j<number_of_columns; ++j){
                result.matrix[i][j]=matrix[i][j]+m.matrix[i][j];
            }
        }
    }
    return result;
}

algebra::Matrix algebra::Matrix::Sub(const algebra::Matrix &m) const{
    algebra::Matrix result(number_of_rows,number_of_columns);
    if (this->Size()==m.Size()){
        for (int i=0; i<number_of_rows; ++i){
            for (int j=0; j<number_of_columns; ++j){
                result.matrix[i][j]=matrix[i][j]-m.matrix[i][j];
            }
        }
    }
    return result;
}

algebra::Matrix algebra::Matrix::Mul(const algebra::Matrix &m) const {
    algebra::Matrix result(number_of_rows, m.number_of_columns);
        if (number_of_columns==m.number_of_rows){
            for (int i=0; i<number_of_rows; ++i){
                for (int j=0; j<m.number_of_columns; ++j){
                    std::complex<double> n= 0.;
                    for (int k=0; k<number_of_columns; ++k){
                        n+=matrix[i][k]*m.matrix[k][j];
                    }
                    result.matrix[i][j]=n;
                }
            }
        }
    return result;
}

algebra::Matrix algebra::Matrix::Pow(int n) const {
    if (n==0 && number_of_rows==number_of_columns){
        algebra::Matrix result(number_of_rows, number_of_columns);
        for (int i=0; i<number_of_rows; ++i){
            result.matrix[i][i]=1;
        }
        return result;
    }
    if (n>0 && number_of_rows==number_of_columns){
        algebra::Matrix result=*this;
        for (int i=1; i<n; ++i){
            result=result.Mul(*this);
        }
        return result;
    }
    return algebra::Matrix(1, 1);
}

algebra::Matrix::Matrix(const std::initializer_list<std::vector<std::complex<double>>> &vectors) {
    number_of_rows=(int)vectors.size();
    number_of_columns=(int)(vectors.begin())->size();
    DynamicArray();
    int current_row=0;
    int current_column=0;
    for (auto row_it=vectors.begin(); row_it<vectors.end(); ++row_it){
        for (auto col_it=row_it->begin(); col_it<row_it->end(); ++col_it){
            matrix[current_row][current_column]=*col_it;
            current_column+=1;
        }
        current_row+=1;
        current_column=0;
    }
}

