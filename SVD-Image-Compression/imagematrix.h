#ifndef IMAGEMATRIX_H
#define IMAGEMATRIX_H
#include "matrix.h"
#include <QRgb>
class ImageMatrix
{
public:
    ImageMatrix(int M,int N);
    ~ImageMatrix();

    void put(int i,int j,QRgb* rgbValue);
private:
    struct RGB{
        Matrix<unsigned char>* RGBMatrix;
    };
    struct SVD{
        Matrix<double>* SVDMatrix;
    };
    RGB RGBMatrices[3];
    SVD SVDMatrices[3];
};

#endif // IMAGEMATRIX_H

ImageMatrix::ImageMatrix(int M,int N)
{
    for(int i=0;i<3;i++){
        RGBMatrices[i].RGBMatrix = new Matrix<unsigned char>(M,N);
        SVDMatrices[i].SVDMatrix = new Matrix<double>(M,N);
    }
}

ImageMatrix::~ImageMatrix(){
    for(int i=0;i<3;i++){
        delete RGBMatrices[i].RGBMatrix;
        delete SVDMatrices[i].SVDMatrix;
    }
}

void ImageMatrix::put(int i, int j, QRgb* rgbValue)
{

}
