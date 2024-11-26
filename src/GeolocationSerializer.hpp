#pragma once

#include <optional>

#include <QJsonObject>

#include "Geolocation.hpp"

class GeolocationSerializer
{
public:
    virtual ~GeolocationSerializer() = default;

    static std::optional<Geolocation> deserialize(const QJsonObject &json);
};
