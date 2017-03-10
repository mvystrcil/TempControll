#ifndef THERMOMETERSLIST_H
#define THERMOMETERSLIST_H

#include "thermometer.hpp"
#include <vector>

class ThermometersList
{
public:
    static ThermometersList& getInstance();
    static void resetInstance();

    bool registerThermometer(Thermometer* thermometer);
    bool unregisterThermometer(const Thermometer *thermometer);
    vector<Thermometer *> getRegisteredList() const;
    
    virtual ~ThermometersList();

private:
    vector<Thermometer *> meters;

    ThermometersList();
};

#endif // THERMOMETERSLIST_H
