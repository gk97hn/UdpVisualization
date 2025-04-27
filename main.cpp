#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "backend/BackendManager.h"
#include "backend/models/UdpSocketModel.h"

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);
    BackendManager backendManager;
    UdpSocketModel udpModel;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("backend", &backendManager);
    engine.rootContext()->setContextProperty("udpModel", &udpModel);

   engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
