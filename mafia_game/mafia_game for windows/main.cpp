#include <QGuiApplication>
#include <QQmlApplicationEngine>


#include <QQmlContext>
#include "backend.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    Backend backend; //  نصنع العقل
    engine.rootContext()->setContextProperty("backend", &backend);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("mafia", "Main");

    return app.exec();
}
