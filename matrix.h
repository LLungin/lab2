//
// Created by Lev Lungin on 11.12.2022.
//

#ifndef LAB2_MATRIX_H
#define LAB2_MATRIX_H

#include <iostream>
#include <string>

template<typename T>
class Matrix {
public:
    Matrix(int, int);
    Matrix(T**, int, int);
    Matrix();
    ~Matrix();
    Matrix(const Matrix<T>&);
    Matrix(Matrix<T>&&);

    Matrix<T>& operator=(const Matrix<T>&);

    double& operator()(int x, int y)
    {
        return elem[x][y];
    }

    Matrix<T>& operator+=(const Matrix<T>&);
    Matrix<T>& operator-=(const Matrix<T>&);
    Matrix<T>& operator*=(const Matrix<T>&);
    Matrix<T>& operator*=(double);
    Matrix<T>& operator/=(double);
    Matrix<T>  operator^(int);

    friend std::ostream& operator<<(std::ostream&, const Matrix<T>&);
    friend std::istream& operator>>(std::istream&, Matrix<T>&);

    void SwapRows(int, int);
    Matrix<T> Transpose();

    static Matrix IdentityMatrix(int size);

private:
    int rows_, cols_;
    T **elem;

    void AllocSpace();
    Matrix<T> PowHelper(const Matrix &m, int num);
};

template<typename T>
Matrix<T> operator+(const Matrix<T>&, const Matrix<T>&);

template<typename T>
Matrix<T> operator-(const Matrix<T>&, const Matrix<T>&);

template<typename T>
Matrix<T> operator*(const Matrix<T>&, const Matrix<T>&);

template<typename T>
Matrix<T> operator*(const Matrix<T>&, double);

template<typename T>
Matrix<T> operator*(double, const Matrix<T>&);

template<typename T>
Matrix<T> operator/(const Matrix<T>&, double);

#endif //LAB2_MATRIX_H
