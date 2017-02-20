#ifndef THERMOMETERSLIST_H
#define THERMOMETERSLIST_H

#include "thermometer.hpp"
#include <vector>

using namespace std;

class ThermometersList
{
public:
    static ThermometersList& getInstance();
    static void resetInstance();

    bool registerThermometer(const Thermometer &thermometer);
    bool unregisterThermometer(const Thermometer &thermometer);
    vector<Thermometer> getRegisteredList() const;

private:
    vector<Thermometer> meters;

    ThermometersList();
    ~ThermometersList();
};

#endif // THERMOMETERSLIST_H
