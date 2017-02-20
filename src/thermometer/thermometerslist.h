#ifndef THERMOMETERSLIST_H
#define THERMOMETERSLIST_H

#include "thermometer.hpp"
#include <vector>

using namespace std;

class ThermometersList
{
public:
    static ThermometersList *getInstance();
    ~ThermometersList();

    bool registerThermometer(const Thermometer &thermometer);
    bool unregisterThermometer(const Thermometer &thermometer);
    vector<Thermometer> getRegisteredList() const;

private:
    static ThermometersList *instance;
    vector<Thermometer> meters;

    ThermometersList();
};

#endif // THERMOMETERSLIST_H
