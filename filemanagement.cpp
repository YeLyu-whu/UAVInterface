#include "filemanagement.h"
#include <QImageReader>
#include <QPixmap>
#include <QMediaPlaylist>
using namespace cv;
FileManagement::FileManagement()
{

}

FileManagement::~FileManagement()
{

}

QPixmap FileManagement::readImage(QString filePath)
{
    QPixmap pixmap;
    pixmap.load(filePath);
    return pixmap;
}

VideoCapture FileManagement::readVideo(QString filePath)
{
    VideoCapture video(filePath.toStdString());
    return video;
}
