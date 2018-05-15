//
// Created by dell on 20.04.2018.
//

#ifndef JIMP_EXERCISES_MATRIX_H
#define JIMP_EXERCISES_MATRIX_H


#include <complex>
namespace algebra {
    class Matrix {
    private:
        std::complex<double> **matrix;
        int number_of_rows;
        int number_of_columns;
    public:
        Matrix(int, int);
        Matrix(std::string);
        Matrix (const std::initializer_list<std::vector<std::complex<double>>> &);
        Matrix &operator=(Matrix &&);
        ~Matrix();
        std::pair<size_t, size_t> Size() const;
        void DynamicArray();
        std::string Print() const;
        Matrix Add(const Matrix &)const;
        Matrix Sub(const Matrix &)const;
        Matrix Mul(const Matrix &)const;
        Matrix Pow(int)const;
    };
}
#endif //JIMP_EXERCISES_MATRIX_H
