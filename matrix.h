//
// Created by Lev Lungin on 11.12.2022.
//

#ifndef LAB2_MATRIX_H
#define LAB2_MATRIX_H

#include <iostream>
#include <string>



template<typename T>
class Matrix
{
public:
    Matrix(int);
    Matrix(int, int);
    Matrix(std::initializer_list<std::initializer_list<T>>);
    Matrix(std::initializer_list<T> l);
    Matrix(T**, int, int);
    Matrix();
    ~Matrix();
    Matrix(const Matrix<T>&);
    Matrix(Matrix<T>&&) noexcept;

    Matrix<T>& operator=(const Matrix<T>&);

    T& operator()(int x, int y);

    Matrix<T>& operator+=(const Matrix<T>&);
    Matrix<T>& operator-=(const Matrix<T>&);
    Matrix<T>& operator*=(const Matrix<T>&);
    Matrix<T>& operator*=(double);
    Matrix<T>& operator/=(double);
    Matrix<T>  operator^(int);
    Matrix<T> PowHelper(const Matrix &m, int num);


    friend std::istream& operator>>(std::istream& in, Matrix<T>& m)
    {
        for (int i = 0; i < m.rows_; ++i)
        {
            for (int j = 0; j < m.cols_; ++j)
                in >> m.elem[i][j];
        }
        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, const Matrix<T>& m)
    {
        for (int i = 0; i < m.rows_; ++i)
        {
            for (int j = 0; j < m.cols_; ++j)
                out << m.elem[i][j] << " ";
            out << std::endl;
        }
        return out;
    }

    void SwapRows(int, int);
    Matrix<T> Transpose();

    static Matrix<T> IdentityMatrix(int size);

private:
    int rows_, cols_;
    T **elem;

    void AllocSpace();
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
