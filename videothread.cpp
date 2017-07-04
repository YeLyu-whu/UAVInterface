#include "videothread.h"
#include <QMessageBox>
#include <QDebug>
using namespace cv;
VideoThread::VideoThread(VideoControl* videoCtrl)
{
_currentState = PLAY_STATE::STOP;
_videoCtrl = videoCtrl;
time.start();
}

VideoControl* VideoThread::getVideoControl()
{
    return _videoCtrl;
}

bool VideoThread::openVideo(QString filePath)
{
    if(getVideoControl()->open(filePath))
    {
        emitNextImage();
        int height = getVideoControl()->getHeight();
        int width = getVideoControl()->getWidth();
        emit changeFrameSize(width,height);
        _currentState = PLAY_STATE::PAUSE;
        return true;
    }
    else
    {
        if(getVideoControl()->isOpenned()==false)
        {
            QMessageBox::critical(NULL,"Video File Open Error","This file cannot be openned",\
                                  QMessageBox::StandardButton::Cancel);
        }
        return false;
    }
}
void VideoThread::closeVideo()
{
    _currentState=PLAY_STATE::STOP;
    getVideoControl()->release();
}

VideoThread::~VideoThread()
{
    closeVideo();
}

Mat VideoThread::getNextMat()
{
    if (!getVideoControl()->getFrame(_curFrame))
    {
        _currentState = PLAY_STATE::STOP;
        return Mat();
    }
    return _curFrame;
}
QImage VideoThread::convertToQImage(Mat&img)
{
    if (_curFrame.channels()== 3){
        cv::cvtColor(img, RGBframe, CV_BGR2RGB);
        _img = QImage((const unsigned char*)(RGBframe.data),
                          RGBframe.cols,RGBframe.rows,QImage::Format_RGB888);
    }
    else
    {
        _img = QImage((const unsigned char*)(_curFrame.data),
                             _curFrame.cols,_curFrame.rows,QImage::Format_Indexed8);
    }
    return _img;
}

void VideoThread::run()
{
    double frameRate = getVideoControl()->props._fps;
    int delay = (1000.0/frameRate);
    while(_currentState==PLAY_STATE::PLAY){
        int dtime = qMax(0,time.elapsed());
        this->msleep(qMax(0,delay-dtime));
        time.start();
        emitNextImage();
        double Msec = getVideoControl()->getPosMsec();
        double posFrame = getVideoControl()->getPosFrames();
        //double frameRatio = getVideoControl()->getPosAviRatio();
        double frameRatio = posFrame/getVideoControl()->getFrameCount();
        emit updateVideoInfo(Msec,posFrame,frameRatio);

    }
}

void VideoThread::pause()
{
    if(_currentState==PLAY_STATE::PLAY)
    {
        _currentState=PLAY_STATE::PAUSE;
    }
}
void VideoThread::play()
{
    if(_currentState=PLAY_STATE::STOP)
    {
        _currentState=PLAY_STATE::PLAY;
        this->start(LowPriority);
    }
    else if(_currentState=PLAY_STATE::PAUSE)
    {
        _currentState=PLAY_STATE::PLAY;
        this->start(LowPriority);
    }
}
void VideoThread::stop()
{
    if(_currentState!=PLAY_STATE::STOP)
    {
        _currentState=PLAY_STATE::STOP;
        setNextFrame(0);
        emitNextImage();
    }
}

void VideoThread::setNextFrame(int frameNum)
{
    getVideoControl()->reset(frameNum);
    emitNextImage();
}

void VideoThread::emitNextImage()
{
    Mat img = getNextMat();
    if(!img.empty())
    {
        _img = convertToQImage(img);
        emit sendImage(_img);
    }

}


