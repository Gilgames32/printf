#include "image_preset_view.hpp"


ImagePresetView::ImagePresetView(QObject *parent) : QAbstractListModel(parent) { 
    m_roleNames[NameRole] = "name";
    m_roleNames[PathRole] = "path";

    m_data = QList<std::pair<std::string, std::string>>();
    m_data.append(std::pair<std::string, std::string>("None", "")); // TODO is this default path good?

    auto presets = jsonprobe::probe_presets("presets/image", "name");
    for (const auto& preset : presets) {
        m_data.append(preset);
    }
}

ImagePresetView::~ImagePresetView() {
    m_data.clear();
}

QHash<int, QByteArray> ImagePresetView::roleNames() const { return m_roleNames; }

int ImagePresetView::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_data.count();
}

QVariant ImagePresetView::data(const QModelIndex &index, int role) const {
    int row = index.row();

    // oob check
    if (row < 0 || row >= m_data.count()) {
        return QVariant();
    }

    // property access
    switch (role) {
        case Qt::DisplayRole:
        case NameRole:
            return QVariant::fromValue(QString::fromStdString(m_data.value(row).first));
        case PathRole:
            return QVariant::fromValue(QString::fromStdString(m_data.value(row).second));
        default:
            return QVariant();
    }
}

QString ImagePresetView::getPath(int index) {
    // oob check
    if (index < 0 || index >= m_data.count()) {
        return QString();
    }

    return QString::fromStdString(m_data.value(index).second);
}

