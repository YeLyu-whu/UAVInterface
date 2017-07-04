#include "srtfile.h"
#include <QTextStream>

SRTFile::SRTFile()
{

}

SRTFile::SRTFile(QString filePath):QFile(filePath)
{

}

SRTFile::~SRTFile()
{

}

void SRTFile::retrieveSRTData(int id)
{
    QTextStream out(this);
   // out.
}
