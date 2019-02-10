#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "QLabel"
#include "QPixmap"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    image = new QImage("C:\\Users\\ddvyu\\Pictures\\SpotBright\\African lion 1920x1080.jpg");
    QPixmap pix = QPixmap::fromImage(*image);
    ui->pictureViewer->setPixmap(pix);
    ui->pictureViewer->setScaledContents(true);
    ui->pictureViewer->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
}

MainWindow::~MainWindow()
{
    delete image;
    delete ui;
}
