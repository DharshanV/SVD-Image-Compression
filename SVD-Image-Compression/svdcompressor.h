#ifndef SVDCOMPRESSOR_H
#define SVDCOMPRESSOR_H
#include <QLabel>
#include <QImage>
#include "jacobi_eigenvalue.h"
#include "matrix.h"
#include <QRgb>
#include <math.h>
#include <QtConcurrent/QtConcurrent>

using namespace std;
class SVDCompressor
{
public:
    SVDCompressor();
    ~SVDCompressor();
    void free();
    void compress(QImage* oImage,QLabel* output);
private:
    void loadToMatrices();
    void initMatrices();
    void deallocate();
    Matrix<double>& getSquareMatrix();
private:
    int M, N;
    int it_max = 10;
    int it_num;
    int rot_num;
    bool compressed;
    QImage* oImage;
    QImage* mImage;
    Matrix<double>* A;
    Matrix<double>* U;
    Matrix<double>* SIG;
    Matrix<double>* VT;
};

void solveForSquare(Matrix<double>* A,Matrix<double>* S);
void solveForEigen(int n, double a[], int it_max, double v[],
                   double d[], int &it_num, int &rot_num);

#endif // SVDCOMPRESSOR_H
