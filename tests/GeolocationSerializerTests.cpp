#include <memory.h>

#include <gtest/gtest.h>

#include <QJsonDocument>

#include "GeolocationSerializer.hpp"

class GeolocationSerializerTests : public ::testing::Test
{
};

TEST_F(GeolocationSerializerTests, DeserializeTest)
{
    const auto raw = R"(
{
  "ip": "134.201.250.155",
  "type": "ipv4",
  "continent_code": "NA",
  "continent_name": "North America",
  "country_code": "US",
  "country_name": "United States",
  "region_code": "CA",
  "region_name": "California",
  "city": "Los Angeles",
  "zip": "90013",
  "latitude": 34.0456390380859,
  "longitude": -118.241638183594,
  "msa": "31100",
  "dma": "803",
  "radius": null,
  "ip_routing_type": null,
  "connection_type": null,
  "location": {
    "geoname_id": 5368361,
    "capital": "Washington D.C.",
    "languages": [
      {
        "code": "en",
        "name": "English",
        "native": "English"
      }
    ],
    "country_flag": "https://assets.ipstack.com/flags/us.svg",
    "country_flag_emoji": "🇺🇸",
    "country_flag_emoji_unicode": "U+1F1FA U+1F1F8",
    "calling_code": "1",
    "is_eu": false
  }
}
    )";

    QJsonDocument doc = QJsonDocument::fromJson(raw);
    QJsonObject json = doc.object();

    const auto sut = GeolocationSerializer::deserialize(json);
    EXPECT_TRUE(sut.has_value());

    EXPECT_EQ(sut->ip, "134.201.250.155");
    EXPECT_EQ(sut->continent, "North America");
    EXPECT_EQ(sut->country, "United States");
    EXPECT_EQ(sut->region, "California");
    EXPECT_EQ(sut->city, "Los Angeles");
    EXPECT_EQ(sut->zip, "90013");
    EXPECT_NEAR(sut->latitude, 34.0456390380859, 0.0001);
    EXPECT_NEAR(sut->longitude, -118.241638183594, 0.0001);

}

TEST_F(GeolocationSerializerTests, DeserializeTest_MissingField)
{
    const auto raw = R"(
{
  "ip": "134.201.250.155",
  "type": "ipv4",
  "continent_code": "NA",
  "continent_name": "North America",
  "country_code": "US",
  "country_name": "United States",
  "region_code": "CA",
  "region_name": "California",
  "city": "Los Angeles",
  "latitude": 34.0456390380859,
  "longitude": -118.241638183594,
  "msa": "31100",
  "dma": "803",
  "radius": null,
  "ip_routing_type": null,
  "connection_type": null,
  "location": {
    "geoname_id": 5368361,
    "capital": "Washington D.C.",
    "languages": [
      {
        "code": "en",
        "name": "English",
        "native": "English"
      }
    ],
    "country_flag": "https://assets.ipstack.com/flags/us.svg",
    "country_flag_emoji": "🇺🇸",
    "country_flag_emoji_unicode": "U+1F1FA U+1F1F8",
    "calling_code": "1",
    "is_eu": false
  }
}
    )";

    QJsonDocument doc = QJsonDocument::fromJson(raw);
    QJsonObject json = doc.object();

    const auto sut = GeolocationSerializer::deserialize(json);
    EXPECT_FALSE(sut.has_value());

}
