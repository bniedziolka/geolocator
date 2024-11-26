#include "SearchBackend.hpp"
#include <QNetworkReply>

#include "ApiClient.hpp"
#include "GeolocationSerializer.hpp"

SearchBackend::SearchBackend(QObject *parent)
    : SearchBackend{std::make_shared<ApiClient>(), parent}
{}

SearchBackend::SearchBackend(std::shared_ptr<BaseApiClient> client, QObject *parent)
    : QObject{parent}
    , m_client{client}
{
    connect(m_client.get(), &BaseApiClient::dataReceived, this, &SearchBackend::onDataReceived);
    connect(m_client.get(), &BaseApiClient::error, this, &SearchBackend::onError);
}

const Geolocation SearchBackend::geolocation() const
{
    return m_geolocation.value_or(Geolocation{});
}

void SearchBackend::search(QString phrase)
{
    emit processing();

    m_geolocation = std::nullopt;

    if (phrase.isEmpty())
    {
        emit error("Empy phrase");
        return;
    }

    m_client->find(phrase);
}

void SearchBackend::onDataReceived(QJsonObject data)
{
    if (data.contains("success") && (false == data["success"].toBool()))
    {
        QJsonObject errorObj = data["error"].toObject();
        emit error(errorObj["info"].toString());
        return;
    }

    if (data.contains("detail"))
    {
        emit error(data["detail"].toString());
        return;
    }

    m_geolocation = GeolocationSerializer::deserialize(data);
    if (m_geolocation.has_value())
    {
        emit done();
    }
    else
    {
        emit error("JSON parsing error");
    }
}

void SearchBackend::onError(QString text)
{
    emit error(text);
}
