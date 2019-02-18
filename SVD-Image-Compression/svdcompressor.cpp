#include "svdcompressor.h"
SVDCompressor::SVDCompressor()
{
    this->oImage = NULL;
    this->mImage = NULL;
    compressed = false;
    M = N = 0;
}

void SVDCompressor::free()
{
    if(compressed){
        deallocate();
        compressed = false;
    }
}

void SVDCompressor::compress(QImage* oImage,QLabel* output)
{
    this->oImage = oImage;
    if(this->oImage == NULL) return;
    output = NULL;
    M = oImage->height();
    N = oImage->width();

    initMatrices();
    loadToMatrices();

    compressed = true;
}

void SVDCompressor::loadToMatrices()
{
    Matrix<double> S(N,N);
    Matrix<double> E(N,1);
    Matrix<double> EV(N,N);
    Matrix<double> V(N,N);

    cout<<"Starting copy image to A"<<endl;
    for(int i=0;i<M;i++){
        uchar* rowData = reinterpret_cast<uchar*>(oImage->scanLine(i));
        for(int j=0;j<N;j++){
            uchar* pixelValue = &rowData[j];
            (*A)[i][j] = static_cast<double>(*pixelValue);
        }
    }
    cout<<"Finished copying image to A\n"<<endl;

    cout<<"Doing AT * A"<<endl;
    solveForSquare(A,&S);
    cout<<"Finished doing AT * A\n"<<endl;

    cout<<"Solving for eigen's"<<endl;
    jacobi_eigenvalue(N,S.getData(),it_max,EV.getData(),E.getData(),it_num,rot_num);
    cout<<"Finished solving for eigen's"<<endl;

    for(int i=0;i<A->getColumns();i++){
        for(int j=0;j<A->getColumns();j++){
            V[i][j] = EV[A->getColumns()-j-1][i];
        }
    }

    //SIG
    int index = 0;
    for(int i=A->getColumns()-1;i>=0;i--){
        if(index>A->getRows()-1)break;
        double temp = E[i][0];
        if(temp < 0){
            temp *= -1;
        }
        (*SIG)[index][index] = sqrt(temp);
        index++;
    }

    //U
    for(int i=0;i<A->getRows();i++){
        for(int j=0;j<A->getRows();j++){
            for(int k=0;k<A->getColumns();k++){
                if((*SIG)[j][j] != 0.0){
                    (*U)[i][j] += (1/(*SIG)[j][j])*((*A)[i][k] * V[k][j]);
                }
            }
        }
    }

    //VT
    (*VT) = V.transpose();

//    cout<<*A<<endl;
//    cout<<"---------------------"<<endl;
//    cout<<(*U)*(*SIG)*(*VT)<<endl;
//    cout<<*U<<endl;
//    cout<<"---------------------"<<endl;
//    cout<<*SIG<<endl;
//    cout<<"---------------------"<<endl;
//    cout<<*VT<<endl;
}

void SVDCompressor::initMatrices()
{
    cout<<"Allocated matrices"<<endl;
    A = new Matrix<double>(M,N);
    U = new Matrix<double>(A->getRows(),A->getRows());
    SIG = new Matrix<double>(A->getRows(),A->getColumns());
    VT = new Matrix<double>(A->getColumns(),A->getColumns());
}

void SVDCompressor::deallocate()
{
    cout<<"Deallocated matrices"<<endl;
    delete A;
    delete U;
    delete SIG;
    delete VT;
}

void solveForSquare(Matrix<double>* A,Matrix<double>* S)
{
    for(int i=0;i<A->getColumns();i++){
        for(int j=0;j<A->getColumns();j++){
            for(int k=0;k<A->getRows();k++){
                (*S)[i][j] += ((*A)[k][i]*(*A)[k][j]);
            }
        }
    }
}

SVDCompressor::~SVDCompressor()
{
    if(compressed){
        deallocate();
    }
}

void solveForEigen(int n, double a[], int it_max, double v[], double d[], int&it_num, int&rot_num)
{
    jacobi_eigenvalue(n,a,it_max,v,d,it_num,rot_num);
}
