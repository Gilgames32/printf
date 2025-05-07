#pragma once

#include <QtCore>
#include <QtGui>
#include <document_preset.hpp>
#include <image_source.hpp>
#include <opencv2/core.hpp>

class GeneratorView : public QObject {
    Q_OBJECT
  public:
    GeneratorView();

    Q_INVOKABLE void generate(const DocumentPreset& properties, const QList<ImageSource*>& sources);
    Q_INVOKABLE QFuture<void> asyncGenerate(const DocumentPreset& properties, const QList<ImageSource*>& sources);
    Q_INVOKABLE void save(const QString& path);

  signals:
    void generationCompleted();
};
