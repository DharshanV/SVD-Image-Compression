#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <string>
using namespace std;

template<typename T> class Matrix;
template<typename T>
class MatrixRow
{
public:
    MatrixRow(Matrix<T>* m,int s);
    T& operator[](int j);
private:
    Matrix<T>* mat;
    int i;
};

template<typename T>
class ConstMatrixRow
{
public:
    ConstMatrixRow(const Matrix<T>* m,int s);
    T operator[](int j) const;

private:
    const Matrix<T>* mat;
    int i;
};

template<typename T>
class Matrix
{
public:
    Matrix(int rows,int columns);

    Matrix(const Matrix<T>& other);

    Matrix<T>& operator=(const Matrix<T>& other);

    Matrix(int rows,int columns,T value);

    ~Matrix();
    Matrix<T>& operator+=(const Matrix<T>& right);
    T& operator()(int i,int j);
    //T operator()(int i,int j) const;
    MatrixRow<T> operator[](int i);
    //ConstMatrixRow<T> operator[](int i) const;
    T* getData(){return elements;}

    void put(int i,int j,T value){
        elements[rows * i + j] = value;
    }

    Matrix<T> transpose(){
        Matrix<T> temp(this->columns,this->rows);
        for(int i=0;i<rows;i++){
            for(int j=0;j<columns;j++){
                temp[j][i] = this->operator()(i,j);
            }
        }
        return temp;
    }

    int getRows() const;
    int getColumns() const;

private:
    int rows;
    int columns;
    T* elements;
};

template<typename T>
Matrix<T>::Matrix(int rows, int columns) {
    this->rows = rows;
    this->columns = columns;
    elements = new T[rows * columns]();
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& other) {
    this->rows = other.rows;
    this->columns = other.columns;
    delete[] elements;
    elements = new T[rows*columns];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            elements[i*columns + j] = other(i, j);
        }
    }
}

template<typename T>
Matrix<T>::Matrix(int rows, int columns, T value) {
    this->rows = rows;
    this->columns = columns;
    elements = new T[rows*columns];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            elements[i*columns + j] = value;
        }
    }
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
    if (&other == this) {
        return *this;
    }
    this->rows = other.rows;
    this->columns = other.columns;
    delete[] elements;
    elements = new T[rows*columns];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            elements[i*columns + j] = other(i, j);
        }
    }
    return *this;
}

template<typename T>
Matrix<T> operator+(const Matrix<T>& left, const Matrix<T>& right)
{
    Matrix<T> result = left;
    if (left.getColumns() != right.getColumns() ||
            left.getRows() != right.getRows())
    {
    }
    result += right;
    return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& right) {
    for (int i = 0; i < right.getRows(); i++) {
        for (int j = 0; j < right.getColumns(); j++) {
            (*this)(i, j) += right(i, j);
        }
    }
    return *this;
}

template<typename T>
Matrix<T> operator*(const Matrix<T>& left, const Matrix<T>& right)
{
    if (left.getColumns() != right.getRows()) {
    }
    Matrix<T> temp(left.getRows(), right.getColumns(), 0);
    for (int i = 0; i < left.getRows(); i++)
    {
       for (int j = 0; j < right.getColumns(); j++)
       {
          for (int k = 0; k < right.getRows(); k++)
          {
             temp(i, j) += left(i, k) * right(k, j);
          }
       }
    }

    return temp;
}

template<typename T>
Matrix<T> operator*(double left,Matrix<T>& right) {
    Matrix<T> temp(right);
    for (int i = 0; i < right.getRows(); i++) {
        for (int j = 0; j < right.getColumns(); j++) {
            temp(i, j) *= left;
        }
    }
    return temp;
}

template<typename T>
Matrix<T> operator*(Matrix<T>& left, double right) {
    Matrix<T> temp(left);
    for (int i = 0; i < left.getRows(); i++) {
        for (int j = 0; j < left.getColumns(); j++) {
            temp(i, j) *= right;
        }
    }
    return temp;
}


template<typename T>
ostream& operator<<(ostream& left, const Matrix<T>& right) {
    for (int i = 0; i < right.getRows(); i++) {
        for (int j = 0; j < right.getColumns(); j++) {
            left << right[i][j] << " ";
        }
        cout << endl;
    }
    return left;
}

template<typename T>
inline T& Matrix<T>::operator()(int i, int j)
{
    if (0 <= i && i < rows && 0 <= j && j < columns) {
        return elements[i*columns + j];
    }
}

//template<typename T>
//inline T Matrix<T>::operator()(int i, int j) const
//{
//    if (0 <= i && i < rows && 0 <= j && j < columns) {
//        return elements[i*columns + j];
//    }
//}

template<typename T>
inline MatrixRow<T> Matrix<T>::operator[](int i)
{
    return MatrixRow<T>(this, i);
}

//template<typename T>
//inline ConstMatrixRow<T> Matrix<T>::operator[](int i) const
//{
 //   return ConstMatrixRow<T>(this, i);
//}

template<typename T>
inline  int Matrix<T>::getRows() const
{
    return rows;
}

template<typename T>
inline int Matrix<T>::getColumns() const
{
    return columns;
}

template<typename T>
inline MatrixRow<T>::MatrixRow(Matrix<T>* m, int s) : mat(m), i(s) { }

template<typename T>
inline T& MatrixRow<T>::operator[](int j)
{
    return (*mat)(i, j);
}

template<typename T>
inline ConstMatrixRow<T>::ConstMatrixRow(const Matrix<T>* m, int s)
    : mat(m), i(s) { }

template<typename T>
inline T ConstMatrixRow<T>::operator[](int j) const
{
    return (*mat)(i, j);
}

template<typename T>
inline Matrix<T> operator*(T left, const Matrix<T>& right)
{
    return right * left;
}

template<typename T>
Matrix<T>::~Matrix<T>() {
    delete[] elements;
}
#endif
