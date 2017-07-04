#ifndef SRTFILE_H
#define SRTFILE_H
#include <QFile>
#include <QPointF>
#include <QTime>
#include <QDate>
class SRTFile : public QFile
{
    Q_OBJECT
public:
    SRTFile();
    SRTFile(QString filePath);
    ~SRTFile();

    void retrieveSRTData(int id);
private:
    struct props
    {
        int id;
        QTime t1;
        QTime t2;
        QPointF ptHome;
        QDate date;
        QTime curTime;
        QPointF ptGPS;
        float Hb;
        float Hs;
        int ISO;
        int TV;
        QString EV;
        QString IR;
    }_prop;
};



#endif // SRTFILE_H
