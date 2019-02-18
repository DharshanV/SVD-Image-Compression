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

void SVDCompressor::compress(QImage* oImage,QLabel* output,int k)
{
    if(compressed){
        loadToLabel(output,k);
        return;
    }
    this->oImage = oImage;
    if(this->oImage == NULL) return;

    M = oImage->height();
    N = oImage->width();

    initMatrices();
    loadToMatrices();
    loadToLabel(output,k);

    compressed = true;
}

QString SVDCompressor::getFileSize()
{
    return QString::number(static_cast<double>(mImage->sizeInBytes())/1048576);
}

void SVDCompressor::loadToMatrices()
{
    Matrix<double> S(N,N);
    Matrix<double> E(N,1);
    Matrix<double> EV(N,N);
    Matrix<double> V(N,N);

    QElapsedTimer timer;

    timer.start();

    copyToA(oImage,A);

    QFuture<void> thread1 = QtConcurrent::run(solveForSquare,A,&S);
    thread1.waitForFinished();

    QFuture<void> thread2 = QtConcurrent::run(solveForEigen,N,S.getData(),EV.getData(),E.getData());
    thread2.waitForFinished();

    solveForV(A,&EV,&V);

    //SIG
    solveForSigma(A,&E,SIG);

    //U
    QFuture<void> thread5 = QtConcurrent::run(solveForU,A,&V,SIG,U);
    thread5.waitForFinished();

    //VT
    solveForVT(&V,VT);

    cout<<"\nTotal time: "<<timer.elapsed()<<endl;
    timer.invalidate();

    //cout<<(*U)*(*SIG)*(*VT)<<endl;
}

void SVDCompressor::loadToLabel(QLabel* output,int k)
{
    Matrix<double> O(M,N);
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            for(int mod=0;mod<k;mod++){
                O[i][j] += (*U)[i][mod] * (*SIG)[mod][mod] * (*VT)[mod][j];
            }
            int pixelValue = static_cast<int>(O[i][j]);
            mImage->setPixel(j,i,qRgb(pixelValue,pixelValue,pixelValue));
        }
    }
    QPixmap pix = QPixmap::fromImage(*mImage);
    output->setPixmap(pix);
    output->setScaledContents(true);
}

void SVDCompressor::initMatrices()
{
    cout<<"Allocated matrices"<<endl;
    A = new Matrix<double>(M,N);
    U = new Matrix<double>(A->getRows(),A->getRows());
    SIG = new Matrix<double>(A->getRows(),A->getColumns());
    VT = new Matrix<double>(A->getColumns(),A->getColumns());
    mImage = new QImage(M,N,QImage::Format_Grayscale8);
}

void SVDCompressor::deallocate()
{
    cout<<"Deallocated matrices"<<endl;
    delete A;
    delete U;
    delete SIG;
    delete VT;
    delete mImage;
}

SVDCompressor::~SVDCompressor()
{
    if(compressed){
        deallocate();
    }
}

void solveForSquare(Matrix<double>* A,Matrix<double>* S)
{
    cout<<"Solving for AT * A"<<endl;
    for(int i=0;i<A->getColumns();i++){
        for(int j=i;j<A->getColumns();j++){
            for(int k=0;k<A->getRows();k++){
                (*S)[i][j] += ((*A)[k][i]*(*A)[k][j]);
            }
            (*S)[j][i] = (*S)[i][j];
        }
    }
    cout<<"Solved for AT * A\n"<<endl;
}

void copyToA(QImage*oImage, Matrix<double>*A)
{
    cout<<"Starting copy image to A"<<endl;
    int M = oImage->height();
    int N = oImage->width();
    for(int i=0;i<M;i++){
        uchar* rowData = reinterpret_cast<uchar*>(oImage->scanLine(i));
        for(int j=0;j<N;j++){
            uchar* pixelValue = &rowData[j];
            (*A)[i][j] = static_cast<double>(*pixelValue);
        }
    }
    cout<<"Finished copying image to A\n"<<endl;
}

void solveForEigen(int n, double a[], double v[], double d[])
{
    cout<<"Solving for eigen's"<<endl;
    int it_max = 5;
    int it_num;
    int rot_num;
    jacobi_eigenvalue(n,a,it_max,v,d,it_num,rot_num);
    cout<<"Solved for eigen's\n"<<endl;
}

void solveForU(Matrix<double>* A, Matrix<double>* V, Matrix<double>* SIG, Matrix<double>* U)
{
    cout<<"Solving for U"<<endl;
    for(int i=0;i<A->getRows();i++){
        for(int j=0;j<A->getRows();j++){
            for(int k=0;k<A->getColumns();k++){
                if((*SIG)[j][j] != 0.0){
                    (*U)[i][j] += (1/(*SIG)[j][j])*((*A)[i][k] * (*V)[k][j]);
                }
            }
        }
    }
    cout<<"Solved for U\n"<<endl;
}

void solveForV(Matrix<double>* A,Matrix<double>* EV,Matrix<double>* V)
{
    cout<<"Solving for V"<<endl;
    for(int i=0;i<A->getColumns();i++){
        for(int j=0;j<A->getColumns();j++){
            (*V)[i][j] = (*EV)[A->getColumns()-j-1][i];
        }
    }
    cout<<"Sovled for V\n"<<endl;
}

void solveForSigma(Matrix<double>*A, Matrix<double>*E, Matrix<double>*SIG)
{
    cout<<"Solving for sigma"<<endl;
    int index = 0;
    for(int i=A->getColumns()-1;i>=0;i--){
        if(index>A->getRows()-1)break;
        double temp = (*E)[i][0];
        if(temp < 0){
            temp *= -1;
        }
        (*SIG)[index][index] = sqrt(temp);
        index++;
    }
    cout<<"Solved for sigma\n"<<endl;
}

void solveForVT(Matrix<double>*V, Matrix<double>*VT)
{
    cout<<"Solving for VT"<<endl;
    (*VT) = V->transpose();
    cout<<"Solved for VT\n"<<endl;
}
