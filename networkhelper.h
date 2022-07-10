#ifndef NETWORKHELPER_H
#define NETWORKHELPER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>

class NetworkHelper : public QObject
{
    Q_OBJECT
public:
    explicit NetworkHelper(QObject *parent = nullptr);

    void tryGetUploaderVideoNum(QString uploaderUid);
    void tryGetUploaderVideoAtIndex(QString uploaderUid, int videoIndex);

protected:
    void returnUploaderVideoNum(QNetworkReply* reply);
    void returnUploaderVideoAtIndex(QNetworkReply* reply);

signals:
    void gotUploaderVideoNum(int uid, int uploaderVideoNum);
    void gotUploaderVideoAtIndex(int uid, QString bvid);

};

#endif // NETWORKHELPER_H
