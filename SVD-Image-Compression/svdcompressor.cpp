#include "svdcompressor.h"

SVDCompressor::SVDCompressor()
{
    this->oImage = NULL;
    this->mImage = NULL;
}

bool SVDCompressor::free()
{
    for(int i=0;i<3;i++){
        Matrix<unsigned char>* temp = RGBMatrices[i].RGBMatrix;
        //delete temp;
    }
    return true;
}

void SVDCompressor::compress(QImage* oImage,QLabel* output)
{
    this->oImage = oImage;
    if(this->oImage == NULL) return;

    loadToMatrices();
    //solve for eigenValues and eigenvectors for each RGB matrix
    //output->setPixmap(QPixmap::fromImage(*mImage));
    //output->setScaledContents(true);
}

void SVDCompressor::loadToMatrices()
{
    int N = oImage->width();
    int M = oImage->height();
    this->initMatrices(M,N);

    for(int i=0;i<M;i++){
        QRgb* rowData = reinterpret_cast<QRgb*>(oImage->scanLine(i));
        for(int j=0;j<N;j++){
            this->put(i,j,&rowData[j]);
        }
    }
}

void SVDCompressor::initMatrices(int M, int N)
{
    for(int i=0;i<3;i++){
        RGBMatrices[i].RGBMatrix = new Matrix<unsigned char>(M,N);
        SVDMatrices[i].SVDMatrix = new Matrix<double>(M,N);
    }
}

void SVDCompressor::put(int i, int j, QRgb* pixelValue)
{
    unsigned char data[3];
    data[0] = static_cast<unsigned char>(qRed(*pixelValue));
    data[1] = static_cast<unsigned char>(qGreen(*pixelValue));
    data[2] = static_cast<unsigned char>(qBlue(*pixelValue));

    for(int k=0;k<3;k++){
        (*(RGBMatrices[k].RGBMatrix))[i][j] = data[k];
    }
}

SVDCompressor::~SVDCompressor()
{
    for(int i=0;i<3;i++){
        delete RGBMatrices[i].RGBMatrix;
        delete SVDMatrices[i].SVDMatrix;
    }
}
