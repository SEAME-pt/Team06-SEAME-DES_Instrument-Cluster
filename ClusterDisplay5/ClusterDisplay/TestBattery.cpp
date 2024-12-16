#include "TestBattery.hpp"

# include <chrono>
# include <iostream>
# include <QDebug>

TestBattery::TestBattery(): m_percentage(100.0f)
{
    qDebug("TestBattery constructor called");
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, [this]() {_updatePercentage();});
    m_timer->start(1000);
}
TestBattery::~TestBattery(){}

float   TestBattery::getPercentage()
{
    std::lock_guard<std::mutex>   guard(percentageMutex);
    return m_percentage;
}

void    TestBattery::_updatePercentage(void)
{
    qDebug("updatePercentage called.");
    std::lock_guard<std::mutex>   guard(percentageMutex);
    m_percentage -= 1;
}
