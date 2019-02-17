#ifndef SVDCOMPRESSOR_H
#define SVDCOMPRESSOR_H
#include <QLabel>
#include <QImage>
#include "jacobi_eigenvalue.h"
#include "matrix.h"
#include <QRgb>

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
private:
    QImage* oImage;
    QImage* mImage;
    struct RGB{
        Matrix<unsigned char>* RGBMatrix;
    };
    struct SVD{
        Matrix<double>* SVDMatrix;
    };
    RGB RGBMatrices[3];
    SVD SVDMatrices[3];
};

#endif // SVDCOMPRESSOR_H
