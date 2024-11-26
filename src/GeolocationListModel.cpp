#include <QStandardPaths>
#include <QDir>

#include "GeolocationListModel.hpp"

GeolocationListModel::GeolocationListModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_repo("db")
{
}

void GeolocationListModel::init()
{
    if (false == m_repo.init())
    {
        emit repositoyError();
    }
    else
    {
        reset();
    }
}

void GeolocationListModel::reset()
{
    beginResetModel();
    m_data = m_repo.getAll();
    endResetModel();
}

int GeolocationListModel::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

QVariant GeolocationListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    return QVariant::fromValue(m_data[index.row()]);
}

QHash<int, QByteArray> GeolocationListModel::roleNames() const
{
    return {{Qt::UserRole + 1, "item"}};
}

bool GeolocationListModel::store(Geolocation geolocation)
{
    const auto result = m_repo.store(geolocation);
    if (result)
    {
        reset();
    }
    return result;
}

bool GeolocationListModel::remove(QString ip)
{
    const auto result = m_repo.remove(ip);
    if (result)
    {
        reset();
    }
    return result;
}
