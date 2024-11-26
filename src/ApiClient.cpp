#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>

#include "ApiClient.hpp"
#include "SettingsBackend.hpp"

namespace
{
constexpr auto BASE_URL = "http://api.ipstack.com";
}

ApiClient::ApiClient(QObject *parent)
    : BaseApiClient{parent}
{
    connect(&m_manager, &QNetworkAccessManager::finished, this, &ApiClient::onReply);
}

void ApiClient::find(const QString &phrase)
{
    static SettingsBackend settings;

    const auto url = QString("%1/%2?access_key=%3").arg(BASE_URL, phrase, settings.apiKey());

    QNetworkRequest request{QUrl{url}};
    (void) m_manager.get(request);
}

void ApiClient::onReply(QNetworkReply *reply)
{
    if (QNetworkReply::NetworkError::NoError != reply->error())
    {
        emit error(reply->errorString());
        return;
    }

    const auto rawJson = reply->readAll();

    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(rawJson, &jsonError);
    if (doc.isNull())
    {
        emit error(jsonError.errorString());
        return;
    }

    QJsonObject data = doc.object();
    emit dataReceived(data);
}
