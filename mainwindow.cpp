#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "filemanagement.h"
//#include <QLabel>
//#include <QPixmap>
//#include <lvideowidget.h>
//#include <QDockWidget>
//#include <QVBoxLayout>
//#include <QMessageBox>
//#include "videothread.h"
//#include <GLTools.h>	// OpenGL toolkit
//#include <GLMatrixStack.h>
//#include <GLFrame.h>
//#include <GLFrustum.h>
//#include <GLBatch.h>
//#include <GLGeometryTransform.h>
//#include <GL/glut.h>
#include "lglwidget.h"
#include <QString>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
//    QPixmap pixmap = FileManagement::readImage("C:\\Users\\lvye\\Desktop\\unnamed.jpg");
//    QLabel* frame = new QLabel(this);
//    this->setCentralWidget(frame);
//    frame->setPixmap(pixmap);
//    frame->show();
//    QString vFilePath = "D:\\MyData\\手机视频\\1408806760613.mp4";
//    //QString vFilePath ="K:/UAVDataCapturing/DJI_0208.MP4";
//    //VideoCapture capture = FileManagement::readVideo(vFilePath);
//    //qDebug()<<capture.isOpened()<<endl;

//    QVBoxLayout* mlayout = new QVBoxLayout();
//    ui->centralWidget->setLayout(mlayout);
//    LVideoWidget* lvw = new LVideoWidget(this);
//    mlayout->addWidget(lvw);
//    lvw->openVideo(vFilePath);

//    LGLWidget* w = new LGLWidget(this);
//    w->resize(400,300);
//    this->setCentralWidget(w);
//    w->show();
    //w.show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
