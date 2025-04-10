#pragma once

#include <QtCore>
#include <QtGui>
#include <opencv2/opencv.hpp>
#include <string>

class MaskFilterView : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool enabled MEMBER m_is_enabled NOTIFY isEnabledChanged)
    Q_PROPERTY(QString name READ get_file_name NOTIFY nameChanged)
    Q_PROPERTY(QString filePath READ get_file_path NOTIFY filePathChanged)
    Q_PROPERTY(QString absoluteFilePath READ get_absolute_file_path NOTIFY filePathChanged)

  private:
    bool m_is_enabled;
    std::string m_file_path;
    cv::Mat m_image;

  public:
    explicit MaskFilterView();

    QString get_file_name() const;

    QString get_file_path() const;

    QString get_absolute_file_path() const;

    cv::Mat get_image() const;

    float get_image_aspect_ratio() const;

    void load_from_preset(const std::string& preset_path);

    Q_INVOKABLE void setPreset(const QString& presetPath);

  signals:
    void isEnabledChanged();
    void nameChanged();
    void filePathChanged();
};