#include <QtGui>
#include <QtQml>

#include "source_entry_view.hpp"
#include "image_preset_view.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<SourceEntryView>("printf", 1, 0, "SourceEntryView");
    qmlRegisterType<ImagePresetView>("printf", 1, 0, "ImagePresetView");
    qRegisterMetaType<ImageSourceView*>("ImageSourceView*");


    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/Application.qml")));

    return app.exec();
}
