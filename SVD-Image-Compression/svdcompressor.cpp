#include "svdcompressor.h"

SVDCompressor::SVDCompressor()
{
    this->image = NULL;
}

bool SVDCompressor::free()
{
    return true;
}

void SVDCompressor::compress(QImage* image,QLabel* output)
{
    loadToMatrix();

    output->setPixmap(QPixmap::fromImage(*image));
    output->setScaledContents(true);
}

void SVDCompressor::loadToMatrix()
{

}
