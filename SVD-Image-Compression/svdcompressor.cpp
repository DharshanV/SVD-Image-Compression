#include "svdcompressor.h"

SVDCompressor::SVDCompressor()
{
    this->oImage = NULL;
    this->mImage = NULL;
    compressed = false;
}

bool SVDCompressor::free()
{
    if(!compressed){return false;}
    deallocate();
    cout<<"Deallocated matrices"<<endl;
    compressed = false;
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
    compressed = true;
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

    Matrix<double>* A;
    Matrix<double>* S;
    Matrix<double>* E;
    Matrix<double>* EV;
    Matrix<double>* V;

    Matrix<double>* U;
    Matrix<double>* SIG;
    Matrix<double>* VT;

    for(int i=0;i<3;i++){
        A = RGBMatrices[i].RGBMatrix;
        S = new Matrix<double>(N,N);
        E = new Matrix<double>(N,1);
        EV = new Matrix<double>(N,N);
        V = new Matrix<double>(N,N);

        U = SVDMatrices[i].U;
        SIG = SVDMatrices[i].SIG;
        VT = SVDMatrices[i].VT;

        for(int i=0;i<A->getColumns();i++){
            for(int j=0;j<A->getColumns();j++){
                for(int k=0;k<A->getRows();k++){
                    (*S)[i][j] += (*A)[k][i] * (*A)[k][j];
                }
            }
        }

        jacobi_eigenvalue(N,S->getData(),it_max,EV->getData(),E->getData(),it_num,rot_num);

        int index = 0;
        for(int i=N-1;i>=0;i--){
            if(index>M-1)break;
            (*SIG)[index][index] = sqrt((*E)[i][0]);
            index++;
        }

        for(int i=0;i<A->getColumns();i++){
            for(int j=0;j<A->getColumns();j++){
                (*V)[i][j] = (*EV)[A->getColumns()-j-1][i];
            }
        }

        for(int i=0;i<A->getRows();i++){
            for(int j=0;j<A->getRows();j++){
                for(int k=0;k<A->getColumns();k++){
                    (*U)[i][j] += (1/(*SIG)[j][j])*((*A)[i][k] * (*V)[k][j]);
                }
            }
        }

        *VT = V->transpose();
        delete A;
        delete S;
        delete E;
        delete EV;
        delete V;
    }
}

void SVDCompressor::initMatrices(int M, int N)
{
    cout<<"Allocated matrices"<<endl;
    for(int i=0;i<3;i++){
        RGBMatrices[i].RGBMatrix = new Matrix<double>(M,N);
        SVDMatrices[i].U = new Matrix<double>(M,M);
        SVDMatrices[i].SIG = new Matrix<double>(M,N);
        SVDMatrices[i].VT = new Matrix<double>(N,N);
    }
}

void SVDCompressor::put(int i, int j, QRgb* pixelValue)
{
    double data[3];
    data[0] = static_cast<double>(qRed(*pixelValue));
    data[1] = static_cast<double>(qGreen(*pixelValue));
    data[2] = static_cast<double>(qBlue(*pixelValue));

    for(int k=0;k<3;k++){
        (*(RGBMatrices[k].RGBMatrix))[i][j] = data[k];
    }
}

void SVDCompressor::deallocate()
{
    for(int i=0;i<3;i++){
        delete RGBMatrices[i].RGBMatrix;
        delete SVDMatrices[i].U;
        delete SVDMatrices[i].SIG;
        delete SVDMatrices[i].VT;
    }
}

SVDCompressor::~SVDCompressor()
{
    if(compressed){
        cout<<"Deallocated matrices"<<endl;
        deallocate();
    }
}
