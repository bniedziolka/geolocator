#pragma once

#include <QMetaType>
#include <QString>

struct Geolocation
{
    Q_GADGET
    Q_PROPERTY(QString ip MEMBER ip)
    Q_PROPERTY(QString continent MEMBER continent)
    Q_PROPERTY(QString country MEMBER country)
    Q_PROPERTY(QString region MEMBER region)
    Q_PROPERTY(QString city MEMBER city)
    Q_PROPERTY(QString zip MEMBER zip)
    Q_PROPERTY(double latitude MEMBER latitude)
    Q_PROPERTY(double longitude MEMBER longitude)

public:
    QString ip;
    QString continent;
    QString country;
    QString region;
    QString city;
    QString zip;
    double latitude;
    double longitude;
};

Q_DECLARE_METATYPE(Geolocation);
