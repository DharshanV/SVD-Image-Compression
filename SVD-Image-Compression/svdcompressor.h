#ifndef SVDCOMPRESSOR_H
#define SVDCOMPRESSOR_H
#include <QLabel>

class SVDCompressor
{
public:
    SVDCompressor();
    void update();
    void compress(QLabel* output);
    void imageChanged();
};

#endif // SVDCOMPRESSOR_H
