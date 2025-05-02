#include <QtGui>
#include <QtQml>

#include "source_entry_view.hpp"
#include "preset_view.hpp"
#include "mask_filter_view.hpp"
#include "document_properties_view.hpp"
#include "generator_view.hpp"
#include "preview_provider.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<SourceEntryView>("printf", 1, 0, "SourceEntryView");
    qmlRegisterType<PresetView>("printf", 1, 0, "PresetView");
    qmlRegisterType<MaskFilterView>("printf", 1, 0, "MaskFilterView");
    qmlRegisterType<DocumentPropertiesView>("printf", 1, 0, "DocumentPropertiesView");
    qmlRegisterType<GeneratorView>("printf", 1, 0, "GeneratorView");

    qRegisterMetaType<ImageSourceView*>("ImageSourceView*");
    qRegisterMetaType<DocumentPreset>("DocumentPreset");
    qRegisterMetaType<ImageSource*>("ImageSource*");

    QQmlApplicationEngine engine;
    engine.addImageProvider("previewprovider", PreviewProvider::instance());
    engine.load(QUrl(QStringLiteral("qrc:/qml/Application.qml")));

    return app.exec();
}
