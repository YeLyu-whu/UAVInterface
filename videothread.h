#ifndef VIDEOTHREAD_H
#define VIDEOTHREAD_H
#include <QThread>
#include <QString>
#include "videocontrol.h"
#include <QImage>
#include <QTime>

class VideoThread : public QThread
{
    Q_OBJECT
    enum PLAY_STATE{PLAY,PAUSE,STOP};
public:
    explicit VideoThread(VideoControl* videoCtrl);
    ~VideoThread();
public:
    VideoControl* getVideoControl();
    cv::Mat getNextMat();
    QImage convertToQImage(cv::Mat&img);
    void setNextFrame(int frameNum);
protected:
    void run();
public slots:
    void pause();
    void play();
    void stop();
    bool openVideo(QString filePath);
    void closeVideo();
    void emitNextImage();
public:
    signals:
     void sendImage(const QImage &image);
     void changeFrameSize(int width,int height);
     void updateVideoInfo(double Msec,double posFrame,double frameRatio);
private:

private:
    QTime time;
    PLAY_STATE _currentState;
    cv::Mat _curFrame;
    cv::Mat RGBframe;
    QImage _img;
    VideoControl* _videoCtrl;
};


#endif // VIDEOTHREAD_H
