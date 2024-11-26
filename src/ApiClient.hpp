#pragma once

#include <QNetworkAccessManager>

#include "BaseApiClient.hpp"

class ApiClient : public BaseApiClient
{
    Q_OBJECT
public:
    explicit ApiClient(QObject *parent = nullptr);

    void find(const QString &phrase) override;

private:
    void onReply(QNetworkReply* reply);

    QNetworkAccessManager m_manager;
};

