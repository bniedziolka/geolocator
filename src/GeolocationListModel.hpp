#pragma once

#include <QtQml/qqmlregistration.h>
#include <QAbstractListModel>

#include "GeolocationRepository.hpp"
#include "Geolocation.hpp"

class GeolocationListModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit GeolocationListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

public slots:
    bool store(Geolocation geolocation);
    bool remove(QString ip);
    void init();

signals:
    void repositoyError();

private:
    void reset();

    GeolocationRepository m_repo;
    std::vector<Geolocation> m_data;
};

