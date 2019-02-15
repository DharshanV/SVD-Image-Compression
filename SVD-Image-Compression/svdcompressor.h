#ifndef SVDCOMPRESSOR_H
#define SVDCOMPRESSOR_H
#include <QLabel>
#include <QImage>

class SVDCompressor
{
public:
    SVDCompressor();
    void update();
    void compress(QLabel* output);
    void imageChanged();
    void setImageLocation(QImage* image);
private:
    void loadToMatrix();
private:
    QImage* image;
    //Matrix* RImageMatrix;
};

#endif // SVDCOMPRESSOR_H
