#pragma once

#include <QImage>
#include <QBuffer>
#include <QQuickImageProvider>

class PreviewProvider : public QQuickImageProvider {
public:
    static PreviewProvider* instance() {
        static PreviewProvider instance;
        return &instance;
    }

    PreviewProvider() : QQuickImageProvider(QQuickImageProvider::Image) {
        m_image = QImage(100, 100, QImage::Format_RGBA8888);
        m_image.fill(Qt::blue);
    }

    void setImage(const QImage& image) {
        m_image = image;
        qDebug() << "Setting image to provider";
    }

    QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize) override {
        Q_UNUSED(id);
        Q_UNUSED(size);
        Q_UNUSED(requestedSize);
        return m_image;
    }

private:
    QImage m_image;
};

