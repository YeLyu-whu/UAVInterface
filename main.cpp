#include "mainwindow.h"
#include <QApplication>
//#include <GLTools.h>	// OpenGL toolkit
//#define FREEGLUT_STATIC
//#include <GL/glut.h>

int main(int argc, char *argv[])
{
//    GLenum err = glewInit();
//    if (GLEW_OK != err)
//    {
//        QString str;
//        str.sprintf("GLEW Error: %s\n", glewGetErrorString(err));
//        qDebug()<<str<<endl;
//        return 1;
//    }
    QApplication a(argc, argv);
    MainWindow* w = new MainWindow();
    w->show();
    return a.exec();
}
