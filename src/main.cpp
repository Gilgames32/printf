#include <QtGui>
#include <QtQml>

#include "document_properties_view.hpp"
#include "generator_view.hpp"
#include "mask_filter_view.hpp"
#include "preset_view.hpp"
#include "preview_provider.hpp"
#include "source_entry_view.hpp"
#include "error_signal.hpp"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    qmlRegisterType<SourceEntryView>("printf", 1, 0, "SourceEntryView");
    qmlRegisterType<PresetView>("printf", 1, 0, "PresetView");
    qmlRegisterType<DocumentPropertiesView>("printf", 1, 0, "DocumentPropertiesView");
    qmlRegisterType<GeneratorView>("printf", 1, 0, "GeneratorView");
    qmlRegisterType<ErrorSignal>("printf", 1, 0, "ErrorSignal");
    
    qRegisterMetaType<MaskFilterView>("MaskFilterView");
    qRegisterMetaType<ImageSourceView>("ImageSourceView");
    qRegisterMetaType<DocumentPreset>("DocumentPreset");
    qRegisterMetaType<ImageSource>("ImageSource");
    qRegisterMetaType<IFilterView>("IFilterView");

    QQmlApplicationEngine engine;
    engine.addImageProvider("previewprovider", PreviewProvider::instance());
    engine.load(QUrl(QStringLiteral("qrc:/qml/Application.qml")));

    return app.exec();
}
