#include "preview_provider.hpp"

PreviewProvider::PreviewProvider() : QQuickImageProvider(QQuickImageProvider::Image) {}

void PreviewProvider::setImage(const QImage& image) { m_image = image; }

QImage PreviewProvider::requestImage(const QString& id, QSize* size, const QSize& requestedSize) {
    Q_UNUSED(id);
    Q_UNUSED(size);
    Q_UNUSED(requestedSize);
    return m_image;
}

PreviewProvider* PreviewProvider::instance() {
    static PreviewProvider* instance = new PreviewProvider();
    return instance;
}