#ifndef LGLWIDGET_H
#define LGLWIDGET_H
#include <QWidget>
//#include <QGLWidget>
#include <qgl.h>

class LGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    LGLWidget(QWidget*parent=NULL);
    ~LGLWidget();
protected:
//    void initializeGL();
//    void resizeGL(int w,int h);
//    void paintGL();

//    void keyPressEvent(QKeyEvent *event);
   private:
    bool bfullsceen;
};

#endif // LGLWIDGET_H
