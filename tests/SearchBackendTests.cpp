#include <memory.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <QSignalSpy>

#include "SearchBackend.hpp"

namespace
{
class MockApiClient : public BaseApiClient
{
public:
    MOCK_METHOD(void, find, (const QString&), (override));
};
}

class SearchBackendTests : public ::testing::Test
{
protected:
    void SetUp() override
    {
        client = std::make_shared<MockApiClient>();
        sut = std::make_unique<SearchBackend>(client);
    }

    std::shared_ptr<MockApiClient> client;
    std::unique_ptr<SearchBackend> sut;
};

TEST_F(SearchBackendTests, SearchTest_Error)
{
    const QString errorMsg = "Error message";

    EXPECT_CALL(*client, find(::testing::_)).WillOnce([&](const QString phrease) {
        emit client->error(errorMsg);
    });


    QSignalSpy spy{sut.get(), &SearchBackend::error};

    sut->search("asd");
    EXPECT_EQ(spy.count(), 1);
    EXPECT_EQ(spy.takeFirst().at(0).toString(), errorMsg);
}

TEST_F(SearchBackendTests, SearchTest_Phrase)
{
    const QString phrase = "127.0.0.1";
    EXPECT_CALL(*client, find(phrase)).Times(1);

    sut->search(phrase);
}

TEST_F(SearchBackendTests, SearchTest_ErrorIfSuccessFieldInJson)
{
    const QString errorMsg = "Error message";

    EXPECT_CALL(*client, find(::testing::_)).WillOnce([&](const QString phrease) {
        emit client->dataReceived({{"success", false}, {"error", QJsonObject{{"info", errorMsg}}}});
    });

    QSignalSpy spy{sut.get(), &SearchBackend::error};
    sut->search("asd");
    EXPECT_EQ(spy.count(), 1);
    EXPECT_EQ(spy.takeFirst().at(0).toString(), errorMsg);
}

TEST_F(SearchBackendTests, SearchTest_DataReceived)
{
    QJsonObject data{
        {"ip", ""},
        {"continent_name", ""},
        {"country_name", ""},
        {"region_name", ""},
        {"city", ""},
        {"zip", ""},
        {"latitude", 0.0},
        {"longitude", 0.0},
    };

    EXPECT_CALL(*client, find(::testing::_)).WillOnce([&](const QString phrease) {
        emit client->dataReceived(data);
    });

    QSignalSpy spy{sut.get(), &SearchBackend::done};
    sut->search("asd");
    EXPECT_EQ(spy.count(), 1);
}

TEST_F(SearchBackendTests, SearchTest_IncompleteDataReceived)
{
    QJsonObject data{};

    EXPECT_CALL(*client, find(::testing::_)).WillOnce([&](const QString phrease) {
        emit client->dataReceived(data);
    });

    QSignalSpy spy{sut.get(), &SearchBackend::error};
    sut->search("asd");
    EXPECT_EQ(spy.count(), 1);
}
