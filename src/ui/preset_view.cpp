#include "preset_view.hpp"


PresetView::PresetView(QObject *parent) : QAbstractListModel(parent) { 
    m_path = QString();
    
    m_roleNames[NameRole] = "name";
    m_roleNames[PathRole] = "path";

    m_data = QList<std::pair<std::string, std::string>>();
}

PresetView::~PresetView() {
    m_data.clear();
}

QHash<int, QByteArray> PresetView::roleNames() const { return m_roleNames; }

void PresetView::fetch_entries() {
    beginResetModel();
    
    m_data.clear();
    m_data.append(std::make_pair("None", "")); // TODO is this default path good?
    
    auto presets = jsonprobe::probe_presets(m_path.toStdString(), "name");
    for (const auto& preset : presets) {
        m_data.append(preset);
    }

    endResetModel();
}

int PresetView::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_data.count();
}

QVariant PresetView::data(const QModelIndex &index, int role) const {
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



QString PresetView::get_path() const {
    return m_path;
}

void PresetView::set_path(const QString &path) {
    if (m_path != path) {
        m_path = path;

        fetch_entries();

        emit pathChanged();
    }
}

QString PresetView::getPath(int index) {
    // oob check
    if (index < 0 || index >= m_data.count()) {
        return QString();
    }

    return QString::fromStdString(m_data.value(index).second);
}

