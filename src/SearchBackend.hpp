#pragma once

#include <memory.h>

#include <QtQml/qqmlregistration.h>
#include <QObject>
#include <QNetworkAccessManager>

#include "BaseApiClient.hpp"
#include "Geolocation.hpp"

class SearchBackend : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(Geolocation geolocation READ geolocation  NOTIFY done FINAL)

public:
    explicit SearchBackend(QObject *parent = nullptr);
    explicit SearchBackend(std::shared_ptr<BaseApiClient> client, QObject *parent = nullptr);

    virtual ~SearchBackend() = default;

    const Geolocation geolocation() const;

public slots:
    void search(QString phrase);

signals:
    void processing();
    void error(QString text);
    void done();

private:
    void onDataReceived(QJsonObject data);
    void onError(QString text);

    std::shared_ptr<BaseApiClient> m_client;
    std::optional<Geolocation> m_geolocation;
};
