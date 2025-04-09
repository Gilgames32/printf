#pragma once

#include <string>
#include <opencv2/opencv.hpp>
#include <QtCore>
#include <QtGui>

class ImageSourceView : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString name READ get_file_name NOTIFY nameChanged)
    Q_PROPERTY(QString filePath READ get_file_path NOTIFY filePathChanged)
    Q_PROPERTY(QSize resolution READ get_image_resolution NOTIFY resolutionChanged)
    Q_PROPERTY(float aspectRatio READ get_image_aspect_ratio NOTIFY aspectRatioChanged)
    Q_PROPERTY(int amount MEMBER m_amount NOTIFY amountChanged)
    Q_PROPERTY(int width MEMBER m_width NOTIFY widthChanged)
    Q_PROPERTY(int height MEMBER m_height NOTIFY heightChanged)

private:
    std::string m_file_path;
    cv::Mat m_image;
    int m_amount;
    int m_width = 100;
    int m_height = 100;

public:
    explicit ImageSourceView(const std::string& path);

    QString get_file_name() const;

    QString get_file_path() const;

    QSize get_image_resolution() const;

    float get_image_aspect_ratio() const;

    cv::Mat get_image() const;

    void load_from_preset(const std::string& preset_path);

    Q_INVOKABLE void setPreset(const QString &presetPath);

signals:
    void nameChanged();
    void filePathChanged();
    void resolutionChanged();
    void aspectRatioChanged();
    void amountChanged();
    void widthChanged();
    void heightChanged();
};