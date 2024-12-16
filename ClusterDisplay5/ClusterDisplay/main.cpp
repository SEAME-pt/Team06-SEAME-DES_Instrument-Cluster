#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "TestBattery.hpp"
#include "TestSpeedSensor.hpp"

int main(int argc, char *argv[])
{


    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    TestBattery     tb;
    TestSpeedSensor tss;
    return app.exec();
}
