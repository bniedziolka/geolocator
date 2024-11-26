#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QSqlDatabase>
#include <QStandardPaths>
#include <QDir>

#include "Geolocation.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qRegisterMetaType<Geolocation>("Geolocation");

    auto db = QSqlDatabase::addDatabase("QSQLITE", "db");
    db.setDatabaseName(QStandardPaths::writableLocation(QStandardPaths::RuntimeLocation).append(QDir::separator()).append("geostorage.db"));

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/geolocator/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);



    return app.exec();
}

