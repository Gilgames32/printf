#pragma once

#include <QtCore>
#include <QtGui>

#include "image_source_view.hpp"

class SourceEntryView : public QAbstractListModel {
    Q_OBJECT
  public:
    enum RoleNames {
        NameRole = Qt::UserRole + 0,
        PathRole = Qt::UserRole + 1,
        ImageResolutionRole = Qt::UserRole + 2,
        AmountRole = Qt::UserRole + 3,
        ImageSizeRole = Qt::UserRole + 4,
        ImageAspectRole = Qt::UserRole + 5,
    };

    explicit SourceEntryView(QObject *parent = 0);
    ~SourceEntryView();

  protected:
    virtual QHash<int, QByteArray> roleNames() const override;

  private:
    // TODO: shared pointer
    // so that deleting while its generating wont result in bugs
    QList<ImageSourceView *> m_data;
    QHash<int, QByteArray> m_roleNames;

  public:
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);

    Q_INVOKABLE void remove(int index);
    Q_INVOKABLE void clear();
    Q_INVOKABLE void addFiles(const QStringList &files);
    Q_INVOKABLE void setPreset(int index, const QString &presetPath);
};
