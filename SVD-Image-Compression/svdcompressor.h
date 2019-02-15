#ifndef SVDCOMPRESSOR_H
#define SVDCOMPRESSOR_H
#include <QLabel>
#include <QImage>
#include "jacobi_eigenvalue.h"

class SVDCompressor
{
public:
    SVDCompressor();
    bool free();
    void compress(QImage* image,QLabel* output);
private:
    void loadToMatrix();
private:
    QImage* image;
    //Matrix* RImageMatrix;
};

#endif // SVDCOMPRESSOR_H
