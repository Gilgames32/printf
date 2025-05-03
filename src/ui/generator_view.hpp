#pragma once

#include <QtCore>
#include <QtGui>
#include <opencv2/core.hpp>
#include <document_preset.hpp>
#include <image_source.hpp>

class GeneratorView: public QObject
{
    Q_OBJECT
public:
    explicit GeneratorView();

    Q_INVOKABLE void generate(const DocumentPreset& properties, QList<ImageSource*> sources);
    Q_INVOKABLE void save(const QString& path);
};

