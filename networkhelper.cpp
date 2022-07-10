#include "networkhelper.h"

NetworkHelper::NetworkHelper(QObject *parent) : QObject(parent)
{
}

void NetworkHelper::tryGetUploaderVideoNum(QString uploaderUid)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager;
    QNetworkRequest request;
    request.setUrl(QUrl(QString("https://api.bilibili.com/x/space/navnum?mid=" + uploaderUid)));
    manager->get(request); // 请求获取视频数量
    connect(manager, &QNetworkAccessManager::finished, this, &NetworkHelper::returnUploaderVideoNum);
}

void NetworkHelper::tryGetUploaderVideoAtIndex(QString uploaderUid, int videoIndex)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager;
    QNetworkRequest request;
    QString url = "https://api.bilibili.com/x/space/arc/search?mid=" + uploaderUid + "&ps=1&tid=0&pn=" + QString::number(videoIndex) + "&keyword=&order=pubdate&jsonp=jsonp";
    request.setUrl(QUrl(url));
    manager->get(request);  // 请求获取视频列表
    connect(manager, &QNetworkAccessManager::finished, this, &NetworkHelper::returnUploaderVideoAtIndex);

}

void NetworkHelper::returnUploaderVideoNum(QNetworkReply* reply)
{
    // 读取返回的JSON
    QByteArray array = reply->readAll();
    QJsonParseError error;
    QJsonValue value;
    QJsonDocument data = QJsonDocument::fromJson(array, &error);
    if (!data.isNull()) {
        QJsonObject obj = data.object();
        value = obj["data"].toObject()["video"].toInt();
    }

    reply->close();
    reply->abort();
    reply->deleteLater();

    QString url = reply->url().toString();
    url = url.mid(url.indexOf("mid=") + 4);
    url.replace("/", "");
    emit gotUploaderVideoNum(url.toInt(), value.toInt());
}

void NetworkHelper::returnUploaderVideoAtIndex(QNetworkReply* reply)
{
    // 读取返回的JSON
    QByteArray array = reply->readAll();

    QJsonParseError error;
    QJsonValue value;
    QJsonDocument data = QJsonDocument::fromJson(array, &error);

    if (!data.isNull()) {
        QJsonObject obj = data.object();
        value = obj["data"].toObject()["list"].toObject()["vlist"].toArray().at(0).toObject()["bvid"].toString();
    }

    reply->close();
    reply->abort();
    reply->deleteLater();

    QString url = reply->url().toString();
    url = url.mid(url.indexOf("mid=") + 4).left(url.indexOf("&"));
    emit gotUploaderVideoAtIndex(url.toInt(), value.toString());
}
