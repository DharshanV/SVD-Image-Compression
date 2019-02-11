#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "QLabel"
#include "QPixmap"
#include "QFileDialog"
#include <string.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    image = NULL;
    imageData = NULL;
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
        //cout<<"[";
        for(int j=0;j<image->width();j++){
            QRgb* pixelData = &rowData[j];
            int index = j + (i*image->width());

            imageData[index].r = qRed(*pixelData);
            imageData[index].g = qGreen(*pixelData);
            imageData[index].b = qBlue(*pixelData);
            //cout<<"R: "<<qRed(pixelData)<<" G: "<<qGreen(pixelData)<<" B: "<<qBlue(pixelData)<<", ";
        }
        //cout<<"]"<<endl;
    }
}
