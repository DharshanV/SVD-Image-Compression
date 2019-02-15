#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "QLabel"
#include "QPixmap"
#include "QFileDialog"
#include <string.h>

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
    imageData = NULL;
    compressor = NULL;
}

void MainWindow::loadImage(const QString* filePath){
    image = new QImage(*filePath);
    QPixmap pix = QPixmap::fromImage(*image);
    ui->pictureViewer->setPixmap(pix);
    ui->pictureViewer->setScaledContents(true);
    double total = static_cast<double>(image->sizeInBytes())/MEGABYTE;
    ui->oFileSize->setText(QString::number(total) + " M");
    imageData = new ImageData[image->width()*image->height()];

}

void MainWindow::on_openButton_released()
{
    QFileDialog fileOpener(this);
    fileOpener.setNameFilter(tr("Images (*.png *.jpg)"));
    fileOpener.setViewMode(QFileDialog::List);
    if(fileOpener.exec()){
        QString fileName = fileOpener.selectedFiles().at(0);
        if(image != NULL){
            delete image;
            delete imageData;
        }
        loadImage(&fileName);
    }
}

MainWindow::~MainWindow()
{
    delete image;
    delete imageData;
    delete ui;
}


void MainWindow::on_compressButton_released()
{
    if(image == NULL){
        return;
    }

    for(int i=0;i<image->height();i++){
        QRgb* rowData = reinterpret_cast<QRgb*>(image->scanLine(i));
        for(int j=0;j<image->width();j++){
            QRgb* pixelData = &rowData[j];
            int index = j + (i*image->width());

            imageData[index].r = qRed(*pixelData);
            imageData[index].g = qGreen(*pixelData);
            imageData[index].b = qBlue(*pixelData);
        }
    }
}
