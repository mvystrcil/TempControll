#ifndef THERMOMETERSTATISTICS_H
#define THERMOMETERSTATISTICS_H

#include "../lib/timerlib.h"

class ThermometerStatistics
{
public:
    ThermometerStatistics(int updateTimeout=30);

    int getUpdateTimeout() const;
    bool setUpdateTimeout(const int timeout);
    
    bool startStatsColl();
    bool stopStatsColl() const;

private:
    int updateTimeout;
    //TimerLib timer;

    void updateAllThermometers();
};

#endif // THERMOMETERSTATISTICS_H
