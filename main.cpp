#include "matrix.h"

using std::ostream;
using std::istream;
using std::endl;


// Конструкторы указанные в задании и те, что я считаю нужными и удобными
template<typename T> // матрица вида: "rows" строк и 1 столбец
Matrix<T>::Matrix(int rows) : rows_(rows), cols_(1)
{
    AllocSpace();
    for (int i = 0; i < rows_; ++i)
    {
        for (int j = 0; j < cols_; ++j)
            elem[i][j] = 0;
    }
}

template<typename T> // матрица вида: "rows" строк и "cols" столбцов
Matrix<T>::Matrix(int rows, int cols) : rows_(rows), cols_(cols)
{
    AllocSpace();
    for (int i = 0; i < rows_; ++i)
    {
        for (int j = 0; j < cols_; ++j)
            elem[i][j] = 0;
    }
}

template<typename T> // матрица принимающая в качестве аргумента лист листов
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> l): rows_(l.size()), cols_(l.begin()->size())
{
    AllocSpace();

    int i = 0;
    int j = 0;
    for (auto row :l)
    {
        j = 0;
        for (auto element : row)
        {
            elem[i][j] = element;
            j++;
        }
        i++;
    }
}

template<typename T> // матрица принимающая в качестве аргумента лист и делающая его строкой
Matrix<T>::Matrix(std::initializer_list<T> l): rows_(1), cols_(l.size())
{
    AllocSpace();

    int i = 0;
    for (auto element :l)
    {
        elem[0][i] = element;
        i++;
    }
}

template<typename T> // матрица принимающая размер и двумерный массив (что-то типо конструктора копирования)
Matrix<T>::Matrix(T** new_elem, int rows, int cols) : rows_(rows), cols_(cols)
{
    AllocSpace();
    for (int i = 0; i < rows_; ++i)
    {
        for (int j = 0; j < cols_; ++j)
            elem[i][j] = new_elem[i][j];
    }
}

template<typename T> // непараметризованный конструктор матрицы
Matrix<T>::Matrix() : rows_(1), cols_(1)
{
    AllocSpace();
    elem[0][0] = 0;
}

template<typename T> // деструктор
Matrix<T>::~Matrix()
{
    for (int i = 0; i < rows_; ++i)
        delete[] elem[i];
    delete[] elem;
}

template<typename T> // конструктор копирования
Matrix<T>::Matrix(const Matrix<T>& m): rows_(m.rows_), cols_(m.cols_)
{
    AllocSpace();
    for (int i = 0; i < rows_; ++i)
    {
        for (int j = 0; j < cols_; ++j)
            elem[i][j] = m.elem[i][j];
    }
}

template<typename T> // конструктор перемещения
Matrix<T>::Matrix(Matrix<T>&& m)
noexcept{
    for (int i = 0; i < rows_; ++i)
        delete[] elem[i];
    delete[] elem;
    elem = m.elem;
    rows_ = m.rows_;
    cols_ = m.cols_;
}

template<typename T> // динамическое выделение памяти
void Matrix<T>::AllocSpace()
{
    elem = new T*[rows_];
    for (int i = 0; i < rows_; ++i)
        elem[i] = new T[cols_];
}

template<typename T> // перезагрузка оператора присваивания
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

template<typename T> // перезагрузка оператора поиска
T& Matrix<T>::operator()(int x, int y)
{
    return elem[x][y];
}

// перезагрузка операторов с обработкой исключений
template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& m)
{
    if (rows_ != m.rows_ || cols_ != m.cols_)
        throw std::out_of_range("Incompatible matrixes.");

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
    if (rows_ != m.rows_ || cols_ != m.cols_)
        throw std::out_of_range("Incompatible matrixes.");

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

    if (cols_ != m.rows_)
        throw std::out_of_range("Incompatible matrixes.");

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

template<typename T> // возведение в степень
Matrix<T> Matrix<T>::operator^(int num)
{
    Matrix<T> temp(*this);

    if (num == 1) // для первой степени
        return temp;

    if (temp.rows_ == temp.cols_)
    {
        if (num == 0) // для нулевой степени
            return IdentityMatrix(temp.rows_);
        else if (num % 2 == 0) // для четной степени
            return PowHelper(temp * temp, num / 2);
        else // для нечетной степени
            return temp * PowHelper(temp * temp, (num - 1) / 2);
    }
}

template<typename T> // чтобы менять местами строки
void Matrix<T>::SwapRows(int row1, int row2)
{
    T *temp = elem[row1];
    elem[row1] = elem[row2];
    elem[row2] = temp;
}

template<typename T> // транспонирование матрицы
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


template<typename T> // создание нулевой матрицы
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


// перезагрузка операторов
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
Matrix<T> operator/(const Matrix<T>& m, double num)
{
    Matrix<T> temp(m);
    return (temp /= num);
}


// перезагрузка операторов ввода и вывода
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
        for (int j = 0; j < m.cols_; ++j)
            out << m.elem[i][j] << " ";
        out << endl;
    }
    return out;
}


// тесты
int main()
{
    Matrix<int> m1(4);
    Matrix<int> m2(4, 6);
    Matrix<int> m5 = { {1, 2, 3}, {4, 5, 6} };
    Matrix<int> m6 = { {1, 2, 3, 4, 5, 6} };
    Matrix<int> m7={1, 2, 3, 4, 5, 6};
    std::initializer_list<std::initializer_list<int>> list1 = { {1}, {2}, {3}, {4}, {5}, {6} };
    Matrix<int> m8(list1);
    std::cout << m1 << m2 << m5 << m6 << m7 << m8 << std::endl;

    Matrix<int> a(3,3);
    Matrix<int> b(4,4);
    a(0, 2) = 13;
    Matrix<int> c = a + b;
    std::cout << c;

    return 0;
}