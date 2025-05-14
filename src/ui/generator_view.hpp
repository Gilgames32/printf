#pragma once

#include <QtCore>
#include <QtGui>
#include <document_preset.hpp>
#include <image_source.hpp>

class GeneratorView : public QObject {
    Q_OBJECT
  public:
    GeneratorView();

    void generate(const DocumentPreset& properties, const QList<std::shared_ptr<ImageSource>>& sources);
    Q_INVOKABLE QFuture<void> asyncGenerate(const DocumentPreset& properties, const QList<std::shared_ptr<ImageSource>>& sources);

    void save(const QString& path, const DocumentPreset& properties);
    Q_INVOKABLE QFuture<void> asyncSave(const QString& path, const DocumentPreset& properties);

  signals:
    void generationCompleted();
    void saveCompleted();
};
