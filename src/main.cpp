#include <QtGui>
#include <QtQml>

#include "source_entry_view.hpp"
#include "preset_view.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<SourceEntryView>("printf", 1, 0, "SourceEntryView");
    qmlRegisterType<PresetView>("printf", 1, 0, "PresetView");
    qRegisterMetaType<ImageSourceView*>("ImageSourceView*");


    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/Application.qml")));

    return app.exec();
}
