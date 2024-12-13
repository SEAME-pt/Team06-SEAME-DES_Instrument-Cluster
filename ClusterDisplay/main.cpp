#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "TestBattery.hpp"
#include "TestSpeedSensor.hpp"
#include "BatteryIconObj.hpp"
#include "SpeedometerObj.hpp"

int main(int argc, char *argv[])
{

    TestBattery tb;
    TestSpeedSensor tss;

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    BatteryIconObj  bio(nullptr, &tb);
    SpeedometerObj  so(nullptr, &tss);
    engine.rootContext()->setContextProperty("batteryIconObj", &bio);
    engine.rootContext()->setContextProperty("speedometerObj", &so);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("ClusterDisplay", "Main");

    bio.startUpdating(); // Maybe specific type of pointer?
    so.startUpdating();

    return app.exec();
}
