//
// Created by Lev Lungin on 11.12.2022.
//

#ifndef LAB2_MATRIX_H
#define LAB2_MATRIX_H

#include <iostream>


// шаблон класса
template<typename T>
class Matrix
{
public:
    Matrix(int);
    Matrix(int, int);
    template<typename S>
    Matrix(std::initializer_list<std::initializer_list<S>>);
    template<typename S>
    Matrix(std::initializer_list<S> l);
    template<typename S>
    Matrix(S**, int, int);
    Matrix();
    ~Matrix();
    Matrix(const Matrix<T>&);
    template<typename S>
    Matrix(const Matrix<S>&);
    Matrix(Matrix<T>&&) noexcept;

    Matrix<T>& operator=(const Matrix<T>&);
    template<typename S>
    Matrix<T>& operator=(const Matrix<S>&);

    T& operator()(int x, int y);
    T at(int x, int y) const;

    template<typename S>
    Matrix<T>& operator+=(const Matrix<S>&);
    template<typename S>
    Matrix<T>& operator-=(const Matrix<S>&);
    template<typename S>
    Matrix<T>& operator*=(const Matrix<S>&);
    Matrix<T>& operator*=(double);
    Matrix<T>& operator/=(double);
    Matrix<T> Pow(int);

    // У меня какая-то проблема с линкером поэтому потоки ввода и вывода я прописываю в шаблоне
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

    // методы получения данных из прайвата для переменных типа Matrix<S> у которых нет доступа к прайвату
    T get_rows() const
    {
        return rows_;
    }

    T get_cols() const
    {
        return cols_;
    }


// Поля класса
private:
    int rows_, cols_;
    T **elem;

    void AllocSpace();
};

template<typename T, typename S>
Matrix<T> operator+(const Matrix<T>&, const Matrix<S>&);

template<typename T, typename S>
Matrix<T> operator-(const Matrix<T>&, const Matrix<T>&);

template<typename T, typename S>
Matrix<T> operator*(const Matrix<T>&, const Matrix<T>&);

template<typename T>
Matrix<T> operator*(const Matrix<T>&, double);

template<typename T>
Matrix<T> operator/(const Matrix<T>&, double);

#endif //LAB2_MATRIX_H
