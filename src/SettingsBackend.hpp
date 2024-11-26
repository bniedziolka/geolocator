#pragma once

#include <QtQml/qqmlregistration.h>
#include <QObject>
#include <QSettings>

class SettingsBackend : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString apiKey READ apiKey WRITE setApiKey NOTIFY apiKeyChanged FINAL)

public:
    explicit SettingsBackend(QObject *parent = nullptr);
    virtual ~SettingsBackend() = default;

    QString apiKey();
    void setApiKey(QString value);

signals:
    void apiKeyChanged();

private:
    QSettings m_settings{"geolocationsoft", "geolocation"};
};

