#include <memory.h>

#include <gtest/gtest.h>

#include "GeolocationRepository.hpp"

class GeolocationRepositoryTests : public ::testing::Test
{
protected:
    void SetUp() override
    {
        if (false == QSqlDatabase::contains("db"))
        {
            db = QSqlDatabase::addDatabase("QSQLITE", "db");
            db.setDatabaseName(":memory:");
        }
        sut = std::make_unique<GeolocationRepository>("db");
        EXPECT_TRUE(sut->init());
    }

    QSqlDatabase db;
    std::unique_ptr<GeolocationRepository> sut;
};

TEST_F(GeolocationRepositoryTests, SchemaTest)
{
    EXPECT_TRUE(sut->init());
    EXPECT_TRUE(db.tables().contains("geolocations"));
}

TEST_F(GeolocationRepositoryTests, StoreTest)
{
    Geolocation item;
    item.ip = "127.0.0.1";
    item.continent = "Europe";
    item.country = "Poland";
    item.region = "Masovia";
    item.city = "Warsaw";
    item.zip = "00-000";
    item.latitude = 52.237049;
    item.longitude = 21.017532;

    EXPECT_TRUE(sut->store(item));

    const auto values = sut->getAll();
    EXPECT_EQ(values.size(), 1);
    const auto value = values.front();

    EXPECT_EQ(item.ip, value.ip);
    EXPECT_EQ(item.continent, value.continent);
    EXPECT_EQ(item.country, value.country);
    EXPECT_EQ(item.region, value.region);
    EXPECT_EQ(item.city, value.city);
    EXPECT_EQ(item.zip, value.zip);
    EXPECT_NEAR(item.latitude, value.latitude, 0.0001);
    EXPECT_NEAR(item.longitude, value.longitude, 0.0001);
}

TEST_F(GeolocationRepositoryTests, ReplaceTest)
{
    Geolocation item;
    item.ip = "127.0.0.1";
    item.continent = "Europe";
    item.country = "Poland";
    item.region = "Masovia";
    item.city = "Warsaw";
    item.zip = "00-000";
    item.latitude = 52.237049;
    item.longitude = 21.017532;

    EXPECT_TRUE(sut->store(item));

    item.city = "Siedlce";
    EXPECT_TRUE(sut->store(item));

    const auto values = sut->getAll();
    EXPECT_EQ(values.size(), 1);
    const auto value = values.front();

    EXPECT_EQ(item.ip, value.ip);
    EXPECT_EQ(item.continent, value.continent);
    EXPECT_EQ(item.country, value.country);
    EXPECT_EQ(item.region, value.region);
    EXPECT_EQ(item.city, value.city);
    EXPECT_EQ(item.zip, value.zip);
    EXPECT_NEAR(item.latitude, value.latitude, 0.0001);
    EXPECT_NEAR(item.longitude, value.longitude, 0.0001);
}

TEST_F(GeolocationRepositoryTests, DeleteTest)
{
    Geolocation item;
    item.ip = "127.0.0.1";
    item.continent = "Europe";
    item.country = "Poland";
    item.region = "Masovia";
    item.city = "Warsaw";
    item.zip = "00-000";
    item.latitude = 52.237049;
    item.longitude = 21.017532;

    EXPECT_TRUE(sut->store(item));

    item.ip = "255.255.255.0";
    EXPECT_TRUE(sut->store(item));

    auto values = sut->getAll();
    EXPECT_EQ(values.size(), 2);

    EXPECT_TRUE(sut->remove("127.0.0.1"));

    values = sut->getAll();
    EXPECT_EQ(values.size(), 1);

    const auto value = values.front();

    EXPECT_EQ(item.ip, value.ip);
    EXPECT_EQ(item.continent, value.continent);
    EXPECT_EQ(item.country, value.country);
    EXPECT_EQ(item.region, value.region);
    EXPECT_EQ(item.city, value.city);
    EXPECT_EQ(item.zip, value.zip);
    EXPECT_NEAR(item.latitude, value.latitude, 0.0001);
    EXPECT_NEAR(item.longitude, value.longitude, 0.0001);
}
