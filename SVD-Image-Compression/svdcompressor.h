#ifndef SVDCOMPRESSOR_H
#define SVDCOMPRESSOR_H
#include <QLabel>
#include <QImage>
#include "jacobi_eigenvalue.h"
#include "matrix.h"
#include <QRgb>
#include <math.h>

using namespace std;
class SVDCompressor
{
public:
    SVDCompressor();
    ~SVDCompressor();
    bool free();
    void compress(QImage* oImage,QLabel* output);
private:
    void loadToMatrices();
    void initMatrices(int M,int N);
    void put(int i,int j,QRgb* pixelValue);
    void deallocate();
    Matrix<double>& getSquareMatrix();
private:
    int it_max = 100;
    int it_num;
    int rot_num;
    bool compressed;
    QImage* oImage;
    QImage* mImage;
    struct RGB{
        Matrix<double>* RGBMatrix;
    };
    struct SVD{
        Matrix<double>* U;
        Matrix<double>* SIG;
        Matrix<double>* VT;
    };
    RGB RGBMatrices[3];
    SVD SVDMatrices[3];
};

#endif // SVDCOMPRESSOR_H
