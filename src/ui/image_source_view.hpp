#pragma once

#include <QtCore>
#include <QtGui>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

#include "image_source.hpp"
#include "ifilter_view.hpp"
#include "mask_filter_view.hpp"

class ImageSourceView : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString name READ get_file_name NOTIFY nameChanged)
    Q_PROPERTY(QString filePath READ get_file_path NOTIFY filePathChanged)
    Q_PROPERTY(QSize resolution READ get_image_resolution NOTIFY resolutionChanged)
    Q_PROPERTY(double aspectRatio READ get_image_aspect_ratio NOTIFY aspectRatioChanged)
    Q_PROPERTY(int amount MEMBER m_amount NOTIFY amountChanged)
    Q_PROPERTY(double width READ get_width NOTIFY widthChanged)
    Q_PROPERTY(double height READ get_height NOTIFY heightChanged)
    Q_PROPERTY(MaskFilterView* mask READ get_mask_filter_view NOTIFY maskFilterViewChanged)

  private:
    std::string m_file_path;
    cv::Mat m_image;
    int m_amount;
    double m_width = 100;
    double m_height = 100;
    MaskFilterView mask_filter_view;

  public:
    ImageSourceView(const std::string& path, int amount = 20); // TODO: config

    QString get_file_name() const;

    QString get_file_path() const;

    QSize get_image_resolution() const;

    double get_image_aspect_ratio() const;

    double get_width() const;

    double get_height() const;

    cv::Mat get_image() const;

    void load_from_preset(const std::string& preset_path);

    std::shared_ptr<ImageSource> get_image_source() const;

    MaskFilterView* get_mask_filter_view();

    Q_INVOKABLE void setPreset(const QString& presetPath);
    Q_INVOKABLE void setSizeToWidth(double width, bool keepAspectRatio = true);
    Q_INVOKABLE void setSizeToHeight(double height, bool keepAspectRatio = true);

  signals:
    void nameChanged();
    void filePathChanged();
    void resolutionChanged();
    void aspectRatioChanged();
    void amountChanged();
    void widthChanged();
    void heightChanged();
    void maskFilterViewChanged();
};