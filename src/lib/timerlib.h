#ifndef TIMERLIB_H
#define TIMERLIB_H

#include <string>
#include <functional>
#include <iostream>
#include <mutex>

typedef std::function<void (void)> TimeoutCallback;

class TimerLib
{
private:
  
public:
  TimerLib();

    // https://thebytekitchen.com/2013/01/14/harder-to-c-aligned-memory-allocation-4/
    bool registerHandler(TimeoutCallback callback, int timeout);
    
    
    //void addHandler(std::function<void(void)> callback);
    //void addHandler(std::function<void(void)> callback);
    //bool registerHandler(std::function<void(int)> callback);
};

#endif // TIMERLIB_H
