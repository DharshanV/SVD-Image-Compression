#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "QLabel"
#include "QPixmap"
#include "QFileDialog"
#include <string.h>

#ifndef DEBUG
#define DEBUG 1
#endif

#if DEBUG
#define LOG(x) do { std::cerr << x<<endl; } while (0)
#else
#define LOG(X)
#endif

/*
 *     double a[N*N] = {
        5,3,0,
        3,5,0,
        0,0,0};
      double d[N];
      int it_max = 100;
      int it_num;
      int n = N;
      int rot_num;
      double v[N*N];

      jacobi_eigenvalue ( n, a, it_max, v, d, it_num, rot_num );
      for(int i=0;i<n;i++){
          cout<<"Eigen value "<<i<<" :"<< d[i]<<endl;
      }
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    image = NULL;
    compressor = new SVDCompressor();
}

void MainWindow::loadImage(const QString* filePath){
    image = new QImage(*filePath);
    *image = image->convertToFormat(QImage::Format_Grayscale8);
    loadImageToLable(image,ui->pictureViewer);
    loadImageSize(image,ui->oFileSize);
}

void MainWindow::loadImageSize(QImage* i,QLabel* label)
{
    double total = static_cast<double>(i->sizeInBytes())/MEGABYTE;
    label->setText(QString::number(total) + " M");
}

void MainWindow::loadImageToLable(QImage* i, QLabel* label)
{
    QPixmap pix = QPixmap::fromImage(*i);
    label->setPixmap(pix);
    label->setScaledContents(true);
}

bool MainWindow::imageExists()
{
    if(image == NULL) return false;
    return true;
}

void MainWindow::on_openButton_released()
{
    QFileDialog fileOpener(this);
    fileOpener.setNameFilter(tr("Images (*.png *.jpg)"));
    fileOpener.setViewMode(QFileDialog::List);

    if(!fileOpener.exec()){
        return;
    }

    QString fileName = fileOpener.selectedFiles().at(0);
    if(imageExists()){
        compressor->free();
        LOG("Original image deallocated");
        delete image;
    }
    loadImage(&fileName);
}

MainWindow::~MainWindow()
{
    delete image;
    delete compressor;
    delete ui;
}


void MainWindow::on_compressButton_released()
{
    if(image == NULL){
        return;
    }
//    for(int i=0;i<image->height();i++){
//        uchar* rowData = reinterpret_cast<uchar*>(image->scanLine(i));
//        for(int j=0;j<image->width();j++){
//            uchar* pixelValue = &rowData[j];
//            cout<<*pixelValue<<" ";
//        }
//        cout<<endl;
//    }
//    cout<<endl<<endl;;
    compressor->compress(image,ui->modifiedImage);
}

void changingImagePixle(){
//    for (int y = 0; y < image->height()-5; ++y) {
//        for (int x = 0; x < image->width()-5; ++x) {
//            image->setPixel(x,y,qRgb(185,185,185));
//        }
//    }

//    for (int y = 0; y < image->height(); ++y) {
//        uchar* rowData = reinterpret_cast<uchar*>(image->scanLine(y));
//        for (int x = 0; x < image->width(); ++x) {
//            uchar* pixelValue = &rowData[x];
//            cout<<(int)*pixelValue<<" ";
//        }
//        cout<<endl;
//    }
//    loadImageToLable(image,ui->pictureViewer);
}
