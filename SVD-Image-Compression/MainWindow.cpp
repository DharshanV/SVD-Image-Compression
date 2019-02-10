#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "QLabel"
#include "QPixmap"
#include "QFileDialog"
#include <string.h>
#define DEBUG
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    image = NULL;
}

void MainWindow::loadImage(const QString* filePath){
    image = new QImage(*filePath);
    QPixmap pix = QPixmap::fromImage(*image);
    ui->pictureViewer->setPixmap(pix);
    ui->pictureViewer->setScaledContents(true);
    double total = static_cast<double>(image->sizeInBytes())/MEGABYTE;
    ui->oFileSize->setText(QString::number(total) + " M");
}

void MainWindow::on_openButton_released()
{
    QFileDialog fileOpener(this);
    fileOpener.setNameFilter(tr("Images (*.png *.jpg)"));
    fileOpener.setViewMode(QFileDialog::List);
    if(fileOpener.exec()){
        QString fileName = fileOpener.selectedFiles().at(0);
        if(image != NULL){
#ifdef DEBUG
            cout<<"Deallocation previous image"<<endl;
#endif
            delete image;
        }
        loadImage(&fileName);
    }
}

MainWindow::~MainWindow()
{
    delete image;
    delete ui;
}

