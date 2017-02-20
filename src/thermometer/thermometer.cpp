#include "thermometer.hpp"

Thermometer::Thermometer(const string &name)
{
    this->name = name;
	this->temperature = 0;
    this->updatePeriod = 0;
}

Thermometer::~Thermometer()
{
}

string Thermometer::getThermometerName() const
{
    return this->name;
}

int Thermometer::getTemperature() const
{
	return this->temperature;
}

bool Thermometer::updateTemperature(const int temperature)
{
    this->temperature = temperature;
}

bool Thermometer::operator ==(const Thermometer& other) const
{
    if(this->getThermometerName().compare(other.getThermometerName()) == 0)
    {
        return true;
    }

    return false;
}
