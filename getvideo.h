#ifndef GETVIDEO_H
#define GETVIDEO_H

#include <QObject>
#include <QApplication>
#include <QSettings>
#include <QMessageBox>
#include <QFile>
#include <QDesktopServices>
#include <QUrl>
#include <QRandomGenerator>
#include "networkhelper.h"

class GetVideo : public QObject
{
    Q_OBJECT
public:
    explicit GetVideo(QObject *parent = nullptr);

    void playVideo();

protected:
    void initVideoList();
    void playRandomVideo();

    int totalWeight = 0;
    QStringList videoList;
    QStringList uploaderList;
    QMap<int, int> uploaderWeightMap;
    QMap<int, int> uploaderVideoNumMap;

    NetworkHelper* networkHelper;

private:
    int postNum = 0;
    int replyNum = 0;
    bool fileReadingFinished = false;
    bool videoPlayed = false;

};

#endif // GETVIDEO_H
