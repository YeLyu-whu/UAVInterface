#ifndef LVIDEOWIDGET_H
#define LVIDEOWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QScrollArea>
#include <QDockWidget>
#include <QPushButton>
#include "opencv.hpp"
#include "videothread.h"
#include <QVBoxLayout>
#include "clickableprogressbar.h"



class LVideoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LVideoWidget(QWidget *parent = 0);
    ~LVideoWidget();
public:
    bool openVideo(QString fileName);
    bool isOpenned();
    void closeVideo();
    void constructInterface();
private:


private:
    QLabel* wFrame;
    QLabel* wStatus;
    ClickableProgressBar* wProgressBar;
    QScrollArea* wScrollArea;
    QDockWidget* wInfoPanel;
    QPushButton* wPlayButton;
    QPushButton* wPauseButton;
    QPushButton* wStopButton;
    VideoThread* vthread;
    VideoControl* vcontrol;
    QVector<QLabel*> vecHints;
    QVBoxLayout* MainLayout;
signals:
    void hasOpennedVideo();
    void hasClosedVideo();
public slots:
    void play();
    void stop();
    void pause();
    void showImage(const QImage&img);
    void changeFrameSize(int width,int height);
    void constructInfoPanel();
    void updateInfoPanel(double Msec,double posFrame,double frameRatio);
    void deleteInfoPanel();

    void changeVideoPos(double framePosRatio);
};

#endif // LVIDEOWIDGET_H
