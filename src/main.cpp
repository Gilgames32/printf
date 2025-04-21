#include <QtGui>
#include <QtQml>

#include "source_entry_view.hpp"
#include "preset_view.hpp"
#include "mask_filter_view.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<SourceEntryView>("printf", 1, 0, "SourceEntryView");
    qmlRegisterType<PresetView>("printf", 1, 0, "PresetView");
    qmlRegisterType<MaskFilterView>("printf", 1, 0, "MaskFilterView");

    qRegisterMetaType<ImageSourceView*>("ImageSourceView*");
    //qRegisterMetaType<MaskFilterView>("MaskFilterView");


    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/Application.qml")));

    return app.exec();
}
