#include "videocontrol.h"
#include <QDebug>
#include <QReadWriteLock>
using namespace cv;
VideoControl::VideoControl():_lock(QReadWriteLock::Recursive)
{

}

VideoControl::~VideoControl()
{

}

bool VideoControl::open(QString filePath)
{
    QReadLocker locker(&_lock);
    if(_videoCap.isOpened()) _videoCap.release();
    _videoCap.open(filePath.toStdString());
    qDebug()<<"Video openned Successful."<<_videoCap.isOpened()<<endl;
    if(_videoCap.isOpened())
    {
        //locker.unlock();
        retrievePalyInfos();
        return true;
    }
    else return false;
}

void VideoControl::release()
{
    //if(_videoCap.isOpened()) _videoCap.release();
}

bool VideoControl::isOpenned()
{
    QReadLocker locker(&_lock);
    return _videoCap.isOpened();
}

QVector<QString> VideoControl::getAllInfos()
{
    QReadLocker locker(&_lock);
    QVector<QString> vecHints(10);
    if(_videoCap.isOpened())
    {
        vecHints[0]=(QString("Width %0").arg(_videoCap.get(CAP_PROP_FRAME_WIDTH)));
        vecHints[1]=(QString("Height %0").arg(_videoCap.get(CAP_PROP_FRAME_HEIGHT)));
        vecHints[2]=(QString("Total Frame Count %0").arg(_videoCap.get(CAP_PROP_FRAME_COUNT  )));
        vecHints[3]=(QString("FPS %0").arg(_videoCap.get(CAP_PROP_FPS )));
        vecHints[4]=(QString("Video Code %0").arg(_videoCap.get(CAP_PROP_FOURCC )));
        vecHints[5]=(QString("Mat Format %0").arg(_videoCap.get(CAP_PROP_FORMAT )));
        vecHints[6]=(QString("Current Time %0").arg(_videoCap.get(CAP_PROP_POS_MSEC)));
        vecHints[7]=(QString("Current Frame %0").arg(_videoCap.get(CAP_PROP_POS_FRAMES )));
        //vecHints[8]=(QString("Current Frame Ratio %0").arg(_videoCap.get(CAP_PROP_POS_AVI_RATIO )));
        vecHints[8]=(QString("Current Frame Ratio %0").arg(_videoCap.get(CAP_PROP_POS_FRAMES)/_videoCap.get(CAP_PROP_FRAME_COUNT)));
        vecHints[9]=(QString("Current Mode %0").arg(_videoCap.get(CAP_PROP_MODE )));
    }
    return vecHints;
}

void VideoControl::retrievePalyInfos()
{
    QReadLocker locker(&_lock);
    if(_videoCap.isOpened())
    {
        props._width=_videoCap.get(CAP_PROP_FRAME_WIDTH);
        props._height=_videoCap.get(CAP_PROP_FRAME_HEIGHT);
        props._fps=_videoCap.get(CAP_PROP_FPS );
    }
    else
    {
        props._width = props._height = props._fps=0;
    }

}

void VideoControl::reset(int frameNumber)
{
    QWriteLocker locker(&_lock);
    _videoCap.set(CAP_PROP_POS_FRAMES,frameNumber );
}

bool VideoControl::getFrame(Mat& img)
{
    QWriteLocker locker(&_lock);
    return _videoCap.read(img);
}

bool VideoControl::getFrame(Mat& img,double frameNum)
{
    QWriteLocker locker(&_lock);
    _videoCap.set(CAP_PROP_POS_FRAMES,frameNum);
    return _videoCap.read(img);
}

double VideoControl::getWidth()
{
    QReadLocker locker(&_lock);
    props._width = _videoCap.get(CAP_PROP_FRAME_WIDTH);
    return props._width;
}
double VideoControl::getHeight()
{
    QReadLocker locker(&_lock);
    props._height = _videoCap.get(CAP_PROP_FRAME_HEIGHT);
    return props._height;
}

double VideoControl::getFps()
{
    QReadLocker locker(&_lock);
    props._fps = _videoCap.get(CAP_PROP_FPS);
    return props._fps;
}
double VideoControl::getFrameCount()
{
    QReadLocker locker(&_lock);
    props._frame_count = _videoCap.get(CAP_PROP_FRAME_COUNT);
    return props._frame_count;
}

double VideoControl::getFourcc()
{
    QReadLocker locker(&_lock);
    props._fourcc = _videoCap.get(CAP_PROP_FOURCC);
    return props._fourcc;
}
double VideoControl::getFormat()
{
    QReadLocker locker(&_lock);
    props._format = _videoCap.get(CAP_PROP_FORMAT);
    return props._format;
}
double VideoControl::getPosMsec()
{
    QReadLocker locker(&_lock);
    props._pos_msec = _videoCap.get(CAP_PROP_POS_MSEC);
    return props._pos_msec;
}
double VideoControl::getPosFrames()
{
    QReadLocker locker(&_lock);
    props._pos_frames = _videoCap.get(CAP_PROP_POS_FRAMES);
    return props._pos_frames;
}
double VideoControl::getPosAviRatio()
{
    QReadLocker locker(&_lock);
    props._pos_avi_ratio = _videoCap.get(CAP_PROP_POS_AVI_RATIO);
    return props._pos_avi_ratio;
}
double VideoControl::getMode()
{
    QReadLocker locker(&_lock);
    props._mode = _videoCap.get(CAP_PROP_MODE);
    return props._mode;
}
