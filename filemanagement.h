#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include <QString>
#include <QImage>
#include <QPixmap>
#include <QMediaPlayer>
#include "opencv2/video.hpp"
#include "opencv.hpp"

class FileManagement
{
public:
    FileManagement();
    ~FileManagement();

public:
    static cv::VideoCapture readVideo(QString filePath);
    static QPixmap readImage(QString filePath);
private:

};

#endif // FILEMANAGEMENT_H
