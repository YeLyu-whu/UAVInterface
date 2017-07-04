#include "lvideowidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QThread>
#include "videocontrol.h"
#include <QDebug>
#include <QSizePolicy>
using namespace cv;
LVideoWidget::LVideoWidget(QWidget *parent) : QWidget(parent)
{
    wFrame= nullptr;
    wProgressBar= nullptr;
    wScrollArea= nullptr;
    wInfoPanel= nullptr;
    wPlayButton= nullptr;
    wPauseButton= nullptr;
    wStopButton= nullptr;
    vthread= nullptr;
    vcontrol= nullptr;
    wInfoPanel = nullptr;
    MainLayout = nullptr;
    vcontrol = new VideoControl();
    vthread = new VideoThread(vcontrol);
    constructInterface();
    connect(vthread,SIGNAL(sendImage(QImage)),this,SLOT(showImage(QImage)));
    connect(vthread,SIGNAL(changeFrameSize(int,int)),this,SLOT(changeFrameSize(int,int)));
    connect(this,SIGNAL(hasOpennedVideo()),this,SLOT(constructInfoPanel()));
    connect(this,SIGNAL(hasClosedVideo()),this,SLOT(deleteInfoPanel()));

}

LVideoWidget::~LVideoWidget()
{
    closeVideo();
    if(vcontrol!=nullptr) delete vcontrol;
    if(vthread!=nullptr) delete vthread;
    qDebug()<<"Video Widget Deleted."<<endl;
}

void LVideoWidget::constructInterface()
{
    MainLayout = new QVBoxLayout();
    this->setLayout(MainLayout);
    wScrollArea = new QScrollArea();
    wScrollArea->setBackgroundRole(QPalette::Dark);
    wFrame = new QLabel();
    wScrollArea->setWidget(wFrame);
    MainLayout->addWidget(wScrollArea);

    wStatus = new QLabel(this);
    wStatus->setText(QString("Stopped"));
    wStatus->setStyleSheet("QLabel {  color : red; }");
    MainLayout->addWidget(wStatus);
    /*create progress bar*/
    wProgressBar = new ClickableProgressBar(this);
    wProgressBar->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);  // 对齐方式
    connect(wProgressBar,SIGNAL(sendPosRatio(double)),this,SLOT(changeVideoPos(double)));
    MainLayout->addWidget(wProgressBar);
    /*create button*/
    QWidget* tW = new QWidget(this);
    QHBoxLayout* hBoxLayout = new QHBoxLayout();
    wPlayButton = new QPushButton("Play",this);
    wPauseButton= new QPushButton("Pause",this);
    wStopButton = new QPushButton("Stop",this);
    tW->setLayout(hBoxLayout);
    hBoxLayout->addWidget(wPlayButton);
    hBoxLayout->addWidget(wPauseButton);
    hBoxLayout->addWidget(wStopButton);
    MainLayout->addWidget(tW);
    connect(wPlayButton,SIGNAL(clicked()),this,SLOT(play()));
    connect(wPauseButton,SIGNAL(clicked()),this,SLOT(pause()));
    connect(wStopButton,SIGNAL(clicked()),this,SLOT(stop()));

    //constructInfoPanel(wInfoPanel);

   // wInfoPanel->show();
   // QProgressBar* wProgressBar;
}

void LVideoWidget::changeVideoPos(double framePosRatio)
{
    int total_count = vcontrol->getFrameCount();
    int framePos = qMin<int>(total_count,qMax<int>(0,(int)total_count*framePosRatio));
    vthread->setNextFrame(framePos);
}

void LVideoWidget::changeFrameSize(int width,int height)
{
    if(wFrame)
        wFrame->resize(width,height);
}

void LVideoWidget::deleteInfoPanel()
{
    if(wInfoPanel)
    {wInfoPanel->deleteLater();wInfoPanel=nullptr;}

}

void LVideoWidget::updateInfoPanel(double Msec,double posFrame,double frameRatio)
{
    if(wInfoPanel!=nullptr)
    {
        vecHints[6]->setText(QString("Current Time %0").arg(Msec));
        vecHints[7]->setText(QString("Current Frame %0").arg(posFrame));
        vecHints[8]->setText(QString("Current Frame Ratio %0").arg(frameRatio));
    }
    if(wProgressBar)
    {
        wProgressBar->setValue(frameRatio*10000);
        double dProgress = frameRatio*100;
        wProgressBar->setFormat(QString("Current Frame Position:%1%").arg(QString::number(dProgress, 'f', 2)));
    }

}

void LVideoWidget::constructInfoPanel()
{

    /*create docker widget*/
    wInfoPanel=new QDockWidget();
    QWidget *mainWidget = new QWidget(wInfoPanel);
    wInfoPanel->setWidget(mainWidget);
    QVBoxLayout* layout = new QVBoxLayout();
    mainWidget->setLayout(layout);

    connect(vthread,SIGNAL(updateVideoInfo(double,double,double)),this,SLOT(updateInfoPanel(double,double,double)));
    if(wInfoPanel!=nullptr&&isOpenned())
    {
        QVector<QString> strAllInfos = this->vthread->getVideoControl()->getAllInfos();
        for(int i=0;i<strAllInfos.size();i++)
        {
            vecHints.push_back(new QLabel(strAllInfos[i],wInfoPanel));
        }

        for(int i=0;i<strAllInfos.size();i++)
        {
            layout->addWidget(vecHints[i]);
        }
    }
    wInfoPanel->show();
}
bool LVideoWidget::openVideo(QString fileName)
{
    if(this->vthread->openVideo(fileName))
    {
        emit hasOpennedVideo();
        return true;
    }
    else
        return false;
}

bool LVideoWidget::isOpenned()
{
    return this->vthread->getVideoControl()->isOpenned();
}

void LVideoWidget::closeVideo()
{
    this->vthread->closeVideo();
    qDebug()<<"Video Closed."<<endl;
    emit hasClosedVideo();
}

void LVideoWidget::play()
{
    vthread->play();
    wStatus->setText(QString("Playing"));
    wStatus->setStyleSheet("QLabel {  color : green; }");
}
void LVideoWidget::stop()
{
    vthread->stop();
    wStatus->setText(QString("Stopped"));
    wStatus->setStyleSheet("QLabel {  color : red; }");
    wProgressBar->setProgressBarValue(0);
}
void LVideoWidget::pause()
{
    vthread->pause();
    wStatus->setText(QString("Paused"));
    wStatus->setStyleSheet("QLabel {  color : orange; }");
}

void LVideoWidget::showImage(const QImage&img)
{
    if(!img.isNull())
    {
        wFrame->setPixmap(QPixmap::fromImage(img));
        wFrame->show();
    }
}
