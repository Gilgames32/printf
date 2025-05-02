#pragma once

#include <QImage>
#include <QQuickImageProvider>

class PreviewProvider : public QQuickImageProvider {
  private:
    QImage m_image;

  public:
    PreviewProvider();

    static PreviewProvider* instance();

    void setImage(const QImage& image);

    QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize) override;
};
