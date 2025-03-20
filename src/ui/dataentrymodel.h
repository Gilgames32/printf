#pragma once

#include <QtCore>
#include <QtGui>

#include "inputfile.hpp"

class DataEntryModel : public QAbstractListModel {
    Q_OBJECT
  public:
    enum RoleNames {
        NameRole = Qt::UserRole + 0,
        HueRole = Qt::UserRole + 1,
        SaturationRole = Qt::UserRole + 2,
        BrightnessRole = Qt::UserRole + 3
    };

    explicit DataEntryModel(QObject *parent = 0);
    ~DataEntryModel();

  protected:
    virtual QHash<int, QByteArray> roleNames() const override;

  private:
    // TODO: shared pointer
    // so that deleting while its generating wont result in bugs
    QList<InputFile *> m_data;
    QHash<int, QByteArray> m_roleNames;

  public:
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    Q_INVOKABLE void remove(int index);
    Q_INVOKABLE void clear();
    Q_INVOKABLE void addFiles(const QStringList &files);
};
