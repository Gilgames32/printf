#pragma once

#include <QtCore>
#include <QtGui>

#include "jsonprobe.hpp"

class ImagePresetView : public QAbstractListModel {
    Q_OBJECT
  public:
    enum RoleNames {
        NameRole = Qt::UserRole + 0,
        PathRole = Qt::UserRole + 1,
    };

    explicit ImagePresetView(QObject *parent = 0);
    ~ImagePresetView();

  protected:
    virtual QHash<int, QByteArray> roleNames() const override;

  private:
    QList<std::pair<std::string, std::string>> m_data;
    QHash<int, QByteArray> m_roleNames;

  public:
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    Q_INVOKABLE QString getPath(int index);
};
