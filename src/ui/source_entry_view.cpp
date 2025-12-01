#include "source_entry_view.hpp"
#include "pdf_source_view.hpp"

SourceEntryView::SourceEntryView(QObject *parent) : QAbstractListModel(parent) { m_data = QList<ImageSourceView *>(); }

SourceEntryView::~SourceEntryView() {
    qDeleteAll(m_data);
    m_data.clear();
}

QHash<int, QByteArray> SourceEntryView::roleNames() const { return {{Qt::UserRole, "entry"}}; }

int SourceEntryView::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_data.count();
}

QVariant SourceEntryView::data(const QModelIndex &index, int role) const {
    // oob check
    if (!index.isValid() || index.row() >= m_data.size()) return QVariant();

    if (role == Qt::UserRole) return QVariant::fromValue(m_data.at(index.row()));

    return QVariant();
}

int SourceEntryView::get_count() const { return m_data.count(); }

void SourceEntryView::remove(int index) {
    // oob check
    if (index < 0 || index >= m_data.size()) {
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);
    delete m_data.takeAt(index);
    endRemoveRows();
    emit amountChanged();
}

void SourceEntryView::clear() {
    beginRemoveRows(QModelIndex(), 0, m_data.count() - 1);
    qDeleteAll(m_data);
    m_data.clear();
    endRemoveRows();
    emit amountChanged();
}

void SourceEntryView::addFiles(const QStringList &files) {
    for (const QString &file : files) {
        ImageSourceView *input_file;
        if (file.endsWith(".pdf", Qt::CaseInsensitive)) {
            input_file = new PDFSourceView();
            input_file->load(file.toStdString()); // TODO configurable default amount
        }
        else {
            input_file = new ImageSourceView();
            input_file->load(file.toStdString());
        }
        
        beginInsertRows(QModelIndex(), m_data.count(), m_data.count());
        m_data.append(input_file);
        endInsertRows();
    }
    emit amountChanged();
}

QList<std::shared_ptr<ImageSource>> SourceEntryView::getImageSources(const DocumentPreset &preset) {
    QList<std::shared_ptr<ImageSource>> sources;
    for (auto &source : m_data) {
        sources.append(source->get_image_source(preset));
    }
    return sources;
}
