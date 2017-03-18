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
    bool unregisterAllThermometers();
    vector<Thermometer *> getRegisteredList() const;
    
    virtual ~ThermometersList();

private:
    static vector<Thermometer *> meters;

    ThermometersList();
};

#endif // THERMOMETERSLIST_H
