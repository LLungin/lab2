//
// Created by Lev Lungin on 11.12.2022.
//

#ifndef LAB2_MATRIX_H
#define LAB2_MATRIX_H

#include <iostream>
#include <string>

class Matrix {
public:
    Matrix(int, int);
    Matrix(double**, int, int);
    Matrix();
    ~Matrix();
    Matrix(const Matrix&);

    Matrix& operator=(const Matrix&);

    double& operator()(int x, int y)
    {
        return elem[x][y];
    }

    Matrix& operator+=(const Matrix&);
    Matrix& operator-=(const Matrix&);
    Matrix& operator*=(const Matrix&);
    Matrix& operator*=(double);
    Matrix& operator/=(double);
    Matrix  operator^(int);

    friend std::ostream& operator<<(std::ostream&, const Matrix&);
    friend std::istream& operator>>(std::istream&, Matrix&);

    void SwapRows(int, int);
    Matrix Transpose();

    static Matrix IdentityMatrix(int size);
    static Matrix solve(Matrix, Matrix);

private:
    int rows_, cols_;
    double **elem;

    void AllocSpace();
    Matrix PowHelper(const Matrix &m, int num);
};

Matrix operator+(const Matrix&, const Matrix&);
Matrix operator-(const Matrix&, const Matrix&);
Matrix operator*(const Matrix&, const Matrix&);
Matrix operator*(const Matrix&, double);
Matrix operator*(double, const Matrix&);
Matrix operator/(const Matrix&, double);

#endif //LAB2_MATRIX_H
