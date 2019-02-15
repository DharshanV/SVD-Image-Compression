#include "svdcompressor.h"

SVDCompressor::SVDCompressor()
{
    this->image = NULL;
}

void SVDCompressor::compress(QLabel* output)
{
    loadToMatrix();

    output->setPixmap(QPixmap::fromImage(*image));
    output->setScaledContents(true);
}

void SVDCompressor::setImageLocation(QImage* image)
{
    this->image = image;
}

void SVDCompressor::loadToMatrix()
{

}
