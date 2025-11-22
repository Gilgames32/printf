#pragma once

#include <QtCore>
#include <QtGui>
#include <string>
#include <document_preset.hpp>

class DocumentPropertiesView : public QObject {
    Q_OBJECT
    Q_PROPERTY(double resolution MEMBER m_resolution NOTIFY resolutionChanged)
    Q_PROPERTY(double rollWidth MEMBER m_roll_width NOTIFY rollWidthChanged)
    Q_PROPERTY(double margin MEMBER m_margin NOTIFY marginChanged)
    Q_PROPERTY(bool correctQuantity MEMBER m_correct_quantity NOTIFY correctQuantityChanged)
    Q_PROPERTY(double gutter MEMBER m_gutter NOTIFY gutterChanged)
    Q_PROPERTY(bool guides MEMBER m_guides NOTIFY guidesChanged)
    Q_PROPERTY(int lineWidth MEMBER m_line_width NOTIFY lineWidthChanged)
    Q_PROPERTY(double bleed MEMBER m_bleed NOTIFY bleedChanged)
    Q_PROPERTY(double minHeight MEMBER m_min_height NOTIFY minHeightChanged)
    Q_PROPERTY(double maxHeight MEMBER m_max_height NOTIFY maxHeightChanged)

  private:
    double m_resolution;
    double m_roll_width;
    double m_margin;
    bool m_correct_quantity;
    double m_gutter;
    bool m_guides;
    int m_line_width;
    double m_bleed;
    double m_min_height;
    double m_max_height;

  public:
    DocumentPropertiesView();

    void load_from_preset(const std::string& preset_path, const std::string& subcategory = "");

    Q_INVOKABLE void setPreset(const QString& presetPath, const QString& subcategory = "");

    Q_INVOKABLE DocumentPreset getDocumentProperties() const;

  signals:
    void resolutionChanged();
    void rollWidthChanged();
    void marginChanged();
    void correctQuantityChanged();
    void gutterChanged();
    void guidesChanged();
    void lineWidthChanged();
    void bleedChanged();
    void minHeightChanged();
    void maxHeightChanged();
};