#ifndef SPEEDOMETEROBJ_HPP
#define SPEEDOMETEROBJ_HPP

#include <QObject>
#include <QQmlEngine>
#include "TestSpeedSensor.hpp"

# define SPEED_UPDATE_RATE 100

class SpeedometerObj : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(double speed READ speed WRITE setSpeed NOTIFY speedChanged FINAL)

public:
    explicit SpeedometerObj(QObject *parent = nullptr, TestSpeedSensor* speedSensor = nullptr);
    ~SpeedometerObj();

    double     speed(void) const;
    void    setSpeed(int newSpeed);
    void    startUpdating();

signals:
    void    speedChanged(double);

private:
    TestSpeedSensor*    _speedSensor;
    double     m_speed;

    void    _fetchSpeed(void);
};

#endif // SPEEDOMETEROBJ_HPP
