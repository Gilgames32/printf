#include "dataentrymodel.h"

DataEntryModel::DataEntryModel(QObject *parent) : QAbstractListModel(parent) { 
    m_roleNames[NameRole] = "name";
    m_roleNames[HueRole] = "hue";
    m_roleNames[SaturationRole] = "saturation";
    m_roleNames[BrightnessRole] = "brightness";

    m_data = QList<InputFile *>();
}

DataEntryModel::~DataEntryModel() {
    qDeleteAll(m_data);
    m_data.clear();
}

QHash<int, QByteArray> DataEntryModel::roleNames() const { return m_roleNames; }

int DataEntryModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_data.count();
}

QVariant DataEntryModel::data(const QModelIndex &index, int role) const {
    int row = index.row();

    // oob check
    if (row < 0 || row >= m_data.count()) {
        return QVariant();
    }

    // property access
    switch (role) {
        case Qt::DisplayRole:
            return QVariant::fromValue(QString::fromStdString(m_data.value(row)->get_file_name()));
        case NameRole:
            return QVariant::fromValue(QString::fromStdString(m_data.value(row)->get_file_name()));
    }

    // default
    return QVariant();
}

void DataEntryModel::remove(int index) {
    // oob check
    if (index < 0 || index >= m_data.count()) {
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);
    delete m_data.takeAt(index);
    endRemoveRows();
}

void DataEntryModel::clear() {
    qDeleteAll(m_data);
    m_data.clear();
}

void DataEntryModel::addFiles(const QStringList &files) {
    for (const QString &file : files) {
        auto *input_file = new InputFile(file.toStdString());

        beginInsertRows(QModelIndex(), m_data.count(), m_data.count());
        m_data.append(input_file); 
        endInsertRows();
    }
}
