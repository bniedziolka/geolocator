#include "SettingsBackend.hpp"

SettingsBackend::SettingsBackend(QObject *parent)
    : QObject{parent}
{}

QString SettingsBackend::apiKey()
{
    return m_settings.value("apiKey").toString();
}

void SettingsBackend::setApiKey(QString value)
{
    m_settings.setValue("apiKey", value);
    emit apiKeyChanged();
}
