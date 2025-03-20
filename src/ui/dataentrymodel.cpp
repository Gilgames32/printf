#include "dataentrymodel.h"

DataEntryModel::DataEntryModel(QObject *parent) : QAbstractListModel(parent) { 
    m_roleNames[NameRole] = "name";
    m_roleNames[PathRole] = "path";
    m_roleNames[ImageSizeRole] = "imageSize";
    m_roleNames[AmountRole] = "amount";

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
        case NameRole:
            return QVariant::fromValue(QString::fromStdString(m_data.value(row)->get_file_name()));
        case PathRole:
            return QVariant::fromValue(QString::fromStdString(m_data.value(row)->get_file_path()));
        case ImageSizeRole: {
            auto [width, height] = m_data.value(row)->get_image_size();
            return QVariant::fromValue(QSize(width, height));
        }
        case AmountRole:
            return QVariant::fromValue(m_data.value(row)->get_amount());
        default:
            return QVariant();
    }
}

bool DataEntryModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    int row = index.row();

    // oob check
    if (row < 0 || row >= m_data.count()) {
        return false;
    }

    switch (role) {
        case AmountRole:
            m_data.value(row)->set_amount(value.toInt());
            break;
        default:
            return false;
    }

    emit dataChanged(index, index, {role});
    return true;
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
