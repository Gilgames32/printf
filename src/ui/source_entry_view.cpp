#include "source_entry_view.hpp"

SourceEntryView::SourceEntryView(QObject *parent) : QAbstractListModel(parent) {
    m_data = QList<ImageSourceView *>();
}

SourceEntryView::~SourceEntryView() {
    qDeleteAll(m_data);
    m_data.clear();
}

QHash<int, QByteArray> SourceEntryView::roleNames() const { return { { Qt::UserRole, "entry" } }; }

int SourceEntryView::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_data.count();
}

QVariant SourceEntryView::data(const QModelIndex &index, int role) const {
    // oob check
    if (!index.isValid() || index.row() >= m_data.size())
        return QVariant();

    if (role == Qt::UserRole)
        return QVariant::fromValue(m_data.at(index.row()));

    return QVariant();
}

void SourceEntryView::remove(int index) {
    // oob check
    if (index < 0 || index >= m_data.size()) {
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
