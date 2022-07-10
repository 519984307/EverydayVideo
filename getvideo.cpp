#include "getvideo.h"

GetVideo::GetVideo(QObject *parent) : QObject(parent)
{
    networkHelper = new NetworkHelper;
    connect(networkHelper, &NetworkHelper::gotUploaderVideoNum, this, [=](int uid, int uploaderVideoNum) {
        if (uploaderVideoNum > 0) {
            uploaderList.append(QString::number(uid));
            uploaderVideoNumMap.insert(uid, uploaderVideoNum);
            int weight = uploaderWeightMap.value(uid);
            if (weight >= 0) {
                totalWeight += weight;
            } else {
                weight *= -1;
                weight *= uploaderVideoNum;
                totalWeight += weight;
                if (uploaderWeightMap.find(uid) != uploaderWeightMap.end()) {
                    uploaderWeightMap.find(uid).value() = weight;
                }
            }
        }
        replyNum++;
        if (replyNum == postNum && fileReadingFinished) {
            if (!videoPlayed) {
                playRandomVideo();
                videoPlayed = true;
            }
        }
    });

    initVideoList();
}

void GetVideo::initVideoList()
{
    // 打开文件
    QFile file(qApp->applicationDirPath().replace("/", "\\") + "\\PlayList.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "无法打开文件", "无法打开\"PlayList.txt\"");
        QApplication::quit();
    }

    // 读取文件
    while(!file.atEnd()) {
        QString line = QString(file.readLine()).remove("\n");
        if (line.startsWith("AV", Qt::CaseInsensitive) || line.startsWith("BV", Qt::CaseInsensitive)) {
            totalWeight += 100;
            videoList.append(line);
        } else if (line.startsWith("UP", Qt::CaseInsensitive)) {
            line = line.mid(2);
            int weight = -100;
            QString uid = line;
            QString weightStr;

            if (line.contains(" ")) {
                uid = line.left(line.indexOf(" "));
                weightStr = line.mid(line.lastIndexOf(" "));
                // 获取UP主权重
                if (weightStr.at(weightStr.length() - 1) == 'V') {
                    weight = weightStr.left(weightStr.length() - 1).toInt() * -1; // 负数代表权重与视频数量相关
                } else {
                    weight = weightStr.toInt();
                }
            }

            networkHelper->tryGetUploaderVideoNum(uid);
            postNum++;
            uploaderWeightMap.insert(uid.toInt(), weight);
            if (weight > 0) totalWeight += weight;
        }
    }
    fileReadingFinished = true;
    if (replyNum == postNum && !videoPlayed) {
        playRandomVideo();
        videoPlayed = true;
    }
}

void GetVideo::playRandomVideo()
{
    if (totalWeight <= 0) {
        QApplication::quit();
        return;
    }

    // 随机选取视频并播放
    int randomIndex = totalWeight != 1 ? QRandomGenerator::global()->bounded(1, totalWeight) : 1;
    if (randomIndex <= videoList.length() * 100) {
        QDesktopServices::openUrl(QUrl("https://www.bilibili.com/video/" + videoList.at(QRandomGenerator::global()->bounded(0, videoList.length() - 1))));
        QApplication::quit();
    } else if (uploaderList.length() > 0) {
        randomIndex -= videoList.length() * 100;

        int i = 0;
        while (uploaderList.length() > i ? randomIndex > uploaderWeightMap.value(uploaderList[i].toInt()) : false) {
            randomIndex -= uploaderWeightMap.value(uploaderList[i].toInt());
            i++;
        }

        connect(networkHelper, &NetworkHelper::gotUploaderVideoAtIndex, this, [=](int uid, QString bvid) {
            QDesktopServices::openUrl(QUrl("https://www.bilibili.com/video/" + bvid));
            QApplication::quit();
        });
        int videoNum = uploaderVideoNumMap.value(uploaderList[i].toInt());
        int videoIndex = videoNum > 1 ? QRandomGenerator::global()->bounded(1, videoNum) : 1;
        networkHelper->tryGetUploaderVideoAtIndex(uploaderList[i], videoIndex);
    } else {
        QApplication::quit();
    }
}
