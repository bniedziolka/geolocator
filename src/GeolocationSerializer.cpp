#include "GeolocationSerializer.hpp"

std::optional<Geolocation> GeolocationSerializer::deserialize(const QJsonObject &json)
{
    if (json.contains("ip")
        && json.contains("continent_name")
        && json.contains("country_name")
        && json.contains("region_name")
        && json.contains("city")
        && json.contains("zip")
        && json.contains("latitude")
        && json.contains("longitude"))
    {
        Geolocation geolocation;
        geolocation.ip = json["ip"].toString("-");
        geolocation.continent = json["continent_name"].toString("-");
        geolocation.country = json["country_name"].toString("-");
        geolocation.region = json["region_name"].toString("-");
        geolocation.city = json["city"].toString("-");
        geolocation.zip = json["zip"].toString("-");
        geolocation.latitude = json["latitude"].toDouble();
        geolocation.longitude = json["longitude"].toDouble();
        return geolocation;
    }

    return std::nullopt;
}
