#pragma once

#include <QtCore>
#include <QtGui>

#include "jsonprobe.hpp"

class PresetView : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(QString path READ get_path WRITE set_path NOTIFY pathChanged)

  public:
    enum RoleNames {
        NameRole = Qt::UserRole + 0,
        PathRole = Qt::UserRole + 1,
    };

    explicit PresetView(QObject *parent = 0);
    ~PresetView();

  protected:
    virtual QHash<int, QByteArray> roleNames() const override;

  private:
    QString m_path;
    QList<std::pair<std::string, std::string>> m_data;
    QHash<int, QByteArray> m_roleNames;

    void fetch_entries();

  public:
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    QString get_path() const;
    void set_path(const QString &path);

    Q_INVOKABLE QString getPath(int index);

  signals:
    void pathChanged();
};
