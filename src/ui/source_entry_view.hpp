#pragma once

#include <QtCore>
#include <QtGui>

#include "image_source_view.hpp"

class SourceEntryView : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(int count READ get_count NOTIFY amountChanged)
    
  public:
    explicit SourceEntryView(QObject *parent = 0);
    ~SourceEntryView();

  protected:
    virtual QHash<int, QByteArray> roleNames() const override;

  private:
    // TODO: shared pointer
    // so that deleting while its generating wont result in bugs
    QList<ImageSourceView *> m_data;

  public:
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    int get_count() const;

    Q_INVOKABLE void remove(int index);
    Q_INVOKABLE void clear();
    Q_INVOKABLE void addFiles(const QStringList &files);

  signals:
    void amountChanged();
};
