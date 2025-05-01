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

  private:
    double m_resolution;
    double m_roll_width;
    double m_margin;
    bool m_correct_quantity;

  public:
    explicit DocumentPropertiesView();

    void load_from_preset(const std::string& preset_path);

    Q_INVOKABLE void setPreset(const QString& presetPath);

    Q_INVOKABLE DocumentPreset getDocumentProperties() const;

  signals:
    void resolutionChanged();
    void rollWidthChanged();
    void marginChanged();
    void correctQuantityChanged();
};