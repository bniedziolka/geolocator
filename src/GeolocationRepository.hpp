#pragma once

#include <vector>

#include <QSqlDatabase>

#include "Geolocation.hpp"

class GeolocationRepository
{
public:
    explicit GeolocationRepository(const QString connectionName);
    virtual ~GeolocationRepository() = default;

    bool init();

    std::vector<Geolocation> getAll() ;

    bool store(Geolocation geolocation);

    bool remove(QString ip);

private:
    QSqlDatabase m_db;
};
