#pragma once

#include <QtCore>
#include <QtGui>
#include <document_preset.hpp>
#include <image_source.hpp>
#include <opencv2/core.hpp>
#include <exiv2/exiv2.hpp>

class GeneratorView : public QObject {
    Q_OBJECT
  public:
    GeneratorView();

    void generate(const DocumentPreset& properties, const QList<ImageSource*>& sources);
    Q_INVOKABLE QFuture<void> asyncGenerate(const DocumentPreset& properties, const QList<ImageSource*>& sources);
    
    void save(const QString& path, const DocumentPreset& properties);
    Q_INVOKABLE QFuture<void> asyncSave(const QString& path, const DocumentPreset& properties);

    // TODO: move these to a separate class
    void add_exif_data(const std::string& path, const Exiv2::ExifData& exif_data);
    Exiv2::ExifData generate_exif_data(const std::string& path, const DocumentPreset& properties);

  signals:
    void generationCompleted();
    void saveCompleted();
};
