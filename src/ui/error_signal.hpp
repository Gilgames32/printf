#pragma once
#include <QtCore>

class ErrorSignal : public QObject {
    Q_OBJECT
private:
    static ErrorSignal* m_instance;

public:
    static ErrorSignal* instance() {
        return m_instance;
    }

    ErrorSignal();

    Q_INVOKABLE void error(const QString& error) {
        emit instance()->onError(error);
    }

    Q_INVOKABLE void info(const QString& info) {
        emit instance()->onInfo(info);
    }

    static void ierror(const QString& error) {
        instance()->error(error);
    }
    static void iinfo(const QString& info) {
        instance()->info(info);
    }

signals:
    void onError(QString error);
    void onInfo(QString info);
};

