#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
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

private:
    void loadImage(const QString* filePath);
    double calcImageSizeInMB(int width,int height,int bitDepth);
private:
    const int MEGABYTE = 1048576;
    Ui::MainWindow *ui;
    QImage* image;
};

#endif // MAINWINDOW_H
