/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *pictureViewer;
    QLabel *modifiedImage;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *oFileSize;
    QPushButton *openButton;
    QPushButton *oFullscreenButton;
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLabel *mFileSize;
    QPushButton *saveButton;
    QPushButton *mFullScreenButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(843, 369);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pictureViewer = new QLabel(centralWidget);
        pictureViewer->setObjectName(QStringLiteral("pictureViewer"));
        pictureViewer->setGeometry(QRect(10, 10, 400, 300));
        pictureViewer->setAlignment(Qt::AlignCenter);
        modifiedImage = new QLabel(centralWidget);
        modifiedImage->setObjectName(QStringLiteral("modifiedImage"));
        modifiedImage->setGeometry(QRect(430, 10, 400, 300));
        modifiedImage->setAlignment(Qt::AlignCenter);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 310, 180, 51));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        oFileSize = new QLabel(layoutWidget);
        oFileSize->setObjectName(QStringLiteral("oFileSize"));

        gridLayout->addWidget(oFileSize, 0, 1, 1, 1);

        openButton = new QPushButton(layoutWidget);
        openButton->setObjectName(QStringLiteral("openButton"));

        gridLayout->addWidget(openButton, 1, 0, 1, 1);

        oFullscreenButton = new QPushButton(layoutWidget);
        oFullscreenButton->setObjectName(QStringLiteral("oFullscreenButton"));

        gridLayout->addWidget(oFullscreenButton, 1, 1, 1, 1);

        layoutWidget_2 = new QWidget(centralWidget);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(430, 310, 192, 51));
        gridLayout_2 = new QGridLayout(layoutWidget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        mFileSize = new QLabel(layoutWidget_2);
        mFileSize->setObjectName(QStringLiteral("mFileSize"));

        gridLayout_2->addWidget(mFileSize, 0, 1, 1, 1);

        saveButton = new QPushButton(layoutWidget_2);
        saveButton->setObjectName(QStringLiteral("saveButton"));

        gridLayout_2->addWidget(saveButton, 1, 0, 1, 1);

        mFullScreenButton = new QPushButton(layoutWidget_2);
        mFullScreenButton->setObjectName(QStringLiteral("mFullScreenButton"));

        gridLayout_2->addWidget(mFullScreenButton, 1, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "SVD Image Compression", nullptr));
        pictureViewer->setText(QApplication::translate("MainWindow", "ORIGINAL IMAGE HERE", nullptr));
        modifiedImage->setText(QApplication::translate("MainWindow", "MODEFIED IMAGE HERE", nullptr));
        label->setText(QApplication::translate("MainWindow", "Original File Size:", nullptr));
        oFileSize->setText(QString());
        openButton->setText(QApplication::translate("MainWindow", "Open", nullptr));
        oFullscreenButton->setText(QApplication::translate("MainWindow", "Fullscreen", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Compressed File Size:", nullptr));
        mFileSize->setText(QString());
        saveButton->setText(QApplication::translate("MainWindow", "Save", nullptr));
        mFullScreenButton->setText(QApplication::translate("MainWindow", "Fullscreen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
