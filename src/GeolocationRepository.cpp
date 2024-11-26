#include <QSqlQuery>
#include <QSqlError>

#include "GeolocationRepository.hpp"

namespace
{
constexpr auto SCHEMA = R"(
    CREATE TABLE IF NOT EXISTS geolocations (
        ip TEXT PRIMARY KEY,
        domain TEXT,
        continent TEXT NOT NULL,
        country TEXT NOT NULL,
        region TEXT NOT NULL,
        city TEXT NOT NULL,
        zip TEXT NOT NULL,
        latitude NUMERIC NOT NULL,
        longitude NUMERIC NOT NULL
    )
)";
}

GeolocationRepository::GeolocationRepository(const QString connectionName)
    : m_db(QSqlDatabase::database(connectionName))
{
}

bool GeolocationRepository::init()
{
    bool result = m_db.open();
    if (result)
    {
        QSqlQuery query(m_db);
        query.prepare(SCHEMA);
        result = query.exec();
    }
    return result;
}

std::vector<Geolocation> GeolocationRepository::getAll()
{
    std::vector<Geolocation> data{};


    QSqlQuery query{m_db};
    query.prepare("SELECT * FROM geolocations");
    query.exec();
    while (query.next())
    {
        Geolocation geolocation;
        geolocation.ip = query.value("ip").toString();
        geolocation.continent = query.value("continent").toString();
        geolocation.country = query.value("country").toString();
        geolocation.region = query.value("region").toString();
        geolocation.city = query.value("city").toString();
        geolocation.zip = query.value("zip").toString();
        geolocation.latitude = query.value("latitude").toDouble();
        geolocation.longitude = query.value("longitude").toDouble();
        data.push_back(geolocation);
    }
    return data;
}

bool GeolocationRepository::store(Geolocation geolocation)
{
    QSqlQuery query{m_db};
    query.prepare(QString{"INSERT OR REPLACE INTO geolocations (ip, continent, country, region, city, zip, latitude, longitude) "
                          "VALUES ('%1', '%2', '%3', '%4', '%5', '%6', %7, %8)"}
                      .arg(geolocation.ip, geolocation.continent, geolocation.country, geolocation.region, geolocation.city, geolocation.zip)
                      .arg(geolocation.latitude).arg(geolocation.longitude));
    return query.exec();
}

bool GeolocationRepository::remove(QString ip)
{
    QSqlQuery query{m_db};
    query.prepare(QString{"DELETE FROM geolocations WHERE ip='%1'"}.arg(ip));
    return query.exec();
}
