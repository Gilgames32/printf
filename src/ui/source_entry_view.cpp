#include "source_entry_view.hpp"

SourceEntryView::SourceEntryView(QObject *parent) : QAbstractListModel(parent) {
    m_roleNames[NameRole] = "name";
    m_roleNames[PathRole] = "path";
    m_roleNames[ImageResolutionRole] = "resolution";
    m_roleNames[AmountRole] = "amount";
    m_roleNames[ImageSizeRole] = "size";
    m_roleNames[ImageAspectRole] = "aspect";

    m_data = QList<ImageSourceView *>();
}

SourceEntryView::~SourceEntryView() {
    qDeleteAll(m_data);
    m_data.clear();
}

QHash<int, QByteArray> SourceEntryView::roleNames() const { return m_roleNames; }

int SourceEntryView::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_data.count();
}

QVariant SourceEntryView::data(const QModelIndex &index, int role) const {
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
        case ImageResolutionRole: {
            auto [width, height] = m_data.value(row)->get_image_resolution();
            return QVariant::fromValue(QSize(width, height));
        }
        case ImageSizeRole: {
            auto [width, height] = m_data.value(row)->get_image_size();
            return QVariant::fromValue(QSize(width, height));
        }
        case ImageAspectRole:
            return QVariant::fromValue(m_data.value(row)->get_image_aspect_ratio());
        case AmountRole:
            return QVariant::fromValue(m_data.value(row)->get_amount());
        default:
            return QVariant();
    }
}

bool SourceEntryView::setData(const QModelIndex &index, const QVariant &value, int role) {
    int row = index.row();

    // oob check
    if (row < 0 || row >= m_data.count()) {
        return false;
    }

    switch (role) {
        case AmountRole:
            m_data.value(row)->set_amount(value.toInt());
            break;
        case ImageSizeRole: {
            auto [width, height] = value.value<QSize>();
            m_data.value(row)->set_image_size(width, height);
            break;
        }
        default:
            return false;
    }

    emit dataChanged(index, index, {role});
    return true;
}

void SourceEntryView::remove(int index) {
    // oob check
    if (index < 0 || index >= m_data.count()) {
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);
    delete m_data.takeAt(index);
    endRemoveRows();
}

void SourceEntryView::clear() {
    qDeleteAll(m_data);
    m_data.clear();
}

void SourceEntryView::addFiles(const QStringList &files) {
    for (const QString &file : files) {
        auto *input_file = new ImageSourceView(file.toStdString());

        beginInsertRows(QModelIndex(), m_data.count(), m_data.count());
        m_data.append(input_file);
        endInsertRows();
    }
}

void SourceEntryView::setPreset(int index, const QString &presetPath) {
    m_data[index]->load_from_preset(presetPath.toStdString());
    QModelIndex modelIndex = this->index(index, 0);
    emit dataChanged(modelIndex, modelIndex, {ImageSizeRole}); // TODO: update
}
