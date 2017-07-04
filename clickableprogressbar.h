#ifndef CLICKABLEPROGRESSBAR_H
#define CLICKABLEPROGRESSBAR_H
#include <QWidget>
#include <QProgressBar>
#include <QEvent>
#include <QMouseEvent>
#include <QPoint>
class ClickableProgressBar:public QProgressBar
{
    Q_OBJECT
public:
    ClickableProgressBar(QWidget* parent = 0);
    ~ClickableProgressBar();
public:
    void mousePressEvent(QMouseEvent*event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void setProgressBarValue(double ratio);
    int getWidth();
    int getHeight();
    double getPosRatio(QPoint pos,double vmin=0,double vmax=1);
    int getPosFromRatio(double ratio);

signals:
    void sendPosRatio(double ratio);
private:
    bool bLMouseDown;
    QPoint pos;
};

#endif // CLICKABLEPROGRESSBAR_H
