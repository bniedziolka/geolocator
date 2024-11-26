#pragma once

#include <QObject>
#include <QJsonObject>

class BaseApiClient : public QObject
{
    Q_OBJECT
public:
    explicit BaseApiClient(QObject *parent = nullptr);

    virtual void find(const QString &phrase) = 0;

signals:
    void dataReceived(QJsonObject data);
    void error(QString text);
};

