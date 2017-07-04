#include "OpenGL/lglwidget.h"


LGLWidget::LGLWidget(QWidget*parent):QGLWidget(parent)
{

}

LGLWidget::~LGLWidget()
{

}

//void LGLWidget::initializeGL()
//{
//    glClearColor(0,0,0,0);
//    glShadeModel(GL_SMOOTH);
//    glClearDepth(1.0);
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LEQUAL);
//    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
//}
//void LGLWidget::resizeGL(int w,int h)
//{
//    h=(h<=0?1:h);
//    glViewport(0,0,w,h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    //gluPerspective(45.0,GLfloat(w)/GLfloat(h),0.1,100.0);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//}
//void LGLWidget::paintGL()
//{
//    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//    glLoadIdentity();
//}

//void LGLWidget::keyPressEvent(QKeyEvent *event)
//{}
