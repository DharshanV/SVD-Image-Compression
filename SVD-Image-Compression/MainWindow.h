#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include "svdcompressor.h"
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_openButton_released();

    void on_compressButton_released();

private:
    void loadImage(const QString* filePath);
    void loadImageSize(QImage* i,QLabel* label);
    void loadImageToLable(QImage* i,QLabel* label);
    bool imageExists();

private:
    const int MEGABYTE = 1048576;
    Ui::MainWindow *ui;
    QImage* image;
    SVDCompressor* compressor;
};

#endif // MAINWINDOW_H
