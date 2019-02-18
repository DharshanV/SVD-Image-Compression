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
    bool compressed;
    QImage* oImage;
    QImage* mImage;
    Matrix<double>* A;
    Matrix<double>* U;
    Matrix<double>* SIG;
    Matrix<double>* VT;
};

void copyToA(QImage* oImage,Matrix<double>* A);
void solveForSquare(Matrix<double>* A,Matrix<double>* S);
void solveForEigen(int n, double a[], double v[],double d[]);
void solveForU(Matrix<double>* A,Matrix<double>* V,Matrix<double>* SIG,Matrix<double>* U);
void solveForV(Matrix<double>* A,Matrix<double>* EV,Matrix<double>* V);
void solveForSigma(Matrix<double>* A,Matrix<double>* E,Matrix<double>* SIG);
void solveForVT(Matrix<double>* V,Matrix<double>* VT);

#endif // SVDCOMPRESSOR_H
