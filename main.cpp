#include "matrix.h"

using std::ostream;
using std::istream;
using std::endl;


template<typename T>
Matrix<T>::Matrix(int rows, int cols) : rows_(rows), cols_(cols)
{
    AllocSpace();
    for (int i = 0; i < rows_; ++i)
    {
        for (int j = 0; j < cols_; ++j)
            elem[i][j] = 0;
    }
}

template<typename T>
Matrix<T>::Matrix(T** new_elem, int rows, int cols) : rows_(rows), cols_(cols)
{
    AllocSpace();
    for (int i = 0; i < rows_; ++i)
    {
        for (int j = 0; j < cols_; ++j)
            elem[i][j] = new_elem[i][j];
    }
}

template<typename T>
Matrix<T>::Matrix() : rows_(1), cols_(1)
{
    AllocSpace();
    elem[0][0] = 0;
}

template<typename T>
Matrix<T>::~Matrix()
{
    for (int i = 0; i < rows_; ++i)
        delete[] elem[i];
    delete[] elem;
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& m): rows_(m.rows_), cols_(m.cols_)
{
    AllocSpace();
    for (int i = 0; i < rows_; ++i)
    {
        for (int j = 0; j < cols_; ++j)
            elem[i][j] = m.elem[i][j];
    }
}

template<typename T>
Matrix<T>::Matrix(Matrix<T>&& m)
noexcept{
    for (int i = 0; i < rows_; ++i)
        delete[] elem[i];
    delete[] elem;
    elem = m.elem;
    rows_ = m.rows_;
    cols_ = m.cols_;
}

template<typename T>
void Matrix<T>::AllocSpace()
{
    elem = new T*[rows_];
    for (int i = 0; i < rows_; ++i)
        elem[i] = new T[cols_];
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m)
{
    if (this == &m)
        return *this;

    if (rows_ != m.rows_ || cols_ != m.cols_)
    {
        for (int i = 0; i < rows_; ++i)
            delete[] elem[i];
        delete[] elem;

        rows_ = m.rows_;
        cols_ = m.cols_;
        AllocSpace();
    }

    for (int i = 0; i < rows_; ++i)
    {
        for (int j = 0; j < cols_; ++j)
            elem[i][j] = m.elem[i][j];
    }
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& m)
{
    for (int i = 0; i < rows_; ++i)
    {
        for (int j = 0; j < cols_; ++j)
            elem[i][j] += m.elem[i][j];
    }
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& m)
{
    for (int i = 0; i < rows_; ++i)
    {
        for (int j = 0; j < cols_; ++j)
            elem[i][j] -= m.elem[i][j];
    }
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& m)
{
    Matrix temp(rows_, m.cols_);
    for (int i = 0; i < temp.rows_; ++i)
    {
        for (int j = 0; j < temp.cols_; ++j)
        {
            for (int k = 0; k < cols_; ++k)
                temp.elem[i][j] += (elem[i][k] * m.elem[k][j]);
        }
    }

    if (rows_ != m.rows_ || cols_ != m.cols_)
    {
        throw std::out_of_range("Incompatible matrixes.");
    }

    return (*this = temp);
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(double num)
{
    for (int i = 0; i < rows_; ++i)
    {
        for (int j = 0; j < cols_; ++j)
            elem[i][j] *= num;
    }
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator/=(double num)
{
    for (int i = 0; i < rows_; ++i)
    {
        for (int j = 0; j < cols_; ++j)
            elem[i][j] /= num;
    }
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::PowHelper(const Matrix<T>& m, int num)
{
    if (num == 0)
        return IdentityMatrix(m.rows_);
    else if (num == 1)
        return m;
    else if (num % 2 == 0) // для четной степени
        return PowHelper(m * m, num / 2);
    else // для нечетной степени
        return m * PowHelper(m * m, (num - 1) / 2);
}

template<typename T>
Matrix<T> Matrix<T>::operator^(int num)
{
    Matrix temp(*this);
    return PowHelper(temp, num);
}

template<typename T>
void Matrix<T>::SwapRows(int row1, int row2)
{
    double *temp = elem[row1];
    elem[row1] = elem[row2];
    elem[row2] = temp;
}
template<typename T>
Matrix<T> Matrix<T>::Transpose()
{
    Matrix temp(cols_, rows_);
    for (int i = 0; i < rows_; ++i)
    {
        for (int j = 0; j < cols_; ++j)
            temp.elem[j][i] = elem[i][j];
    }
    return temp;
}


template<typename T>
Matrix<T> Matrix<T>::IdentityMatrix(int size)
{
    Matrix temp(size, size);
    for (int i = 0; i < temp.rows_; ++i)
    {
        for (int j = 0; j < temp.cols_; ++j)
        {
            if (i == j)
                temp.elem[i][j] = 1;
            else
                temp.elem[i][j] = 0;
        }
    }
    return temp;
}


template<typename T>
Matrix<T> operator+(const Matrix<T>& m1, const Matrix<T>& m2)
{
    Matrix<T> temp(m1);
    return (temp += m2);
}

template<typename T>
Matrix<T> operator-(const Matrix<T>& m1, const Matrix<T>& m2)
{
    Matrix<T> temp(m1);
    return (temp -= m2);
}

template<typename T>
Matrix<T> operator*(const Matrix<T>& m1, const Matrix<T>& m2)
{
    Matrix<T> temp(m1);
    return (temp *= m2);
}

template<typename T>
Matrix<T> operator*(const Matrix<T>& m, double num)
{
    Matrix<T> temp(m);
    return (temp *= num);
}

template<typename T>
Matrix<T> operator*(double num, const Matrix<T>& m)
{
    return (m * num);
}

template<typename T>
Matrix<T> operator/(const Matrix<T>& m, double num)
{
    Matrix<T> temp(m);
    return (temp /= num);
}



template<typename T>
istream& operator>>(istream& in, Matrix<T>& m)
{
    for (int i = 0; i < m.rows_; ++i)
    {
        for (int j = 0; j < m.cols_; ++j)
            in >> m.elem[i][j];
    }
    return in;
}

template<typename T>
ostream& operator<<(ostream& out, const Matrix<T>& m)
{
    for (int i = 0; i < m.rows_; ++i)
    {
        out << m.elem[i][0];
        for (int j = 1; j < m.cols_; ++j)
            out << " " << m.elem[i][j];
        out << endl;
    }
    return out;
}
