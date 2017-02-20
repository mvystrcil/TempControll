#ifndef THERMOMETERSTATISTICS_H
#define THERMOMETERSTATISTICS_H

class ThermometerStatistics
{
public:
    ThermometerStatistics(int updateTimeout=30);

    int getUpdateTimeout() const;
    bool setUpdateTimeout(const int updateTimeout);
    bool startStatsColl() const;

private:
    int updateTimeout;

    void updateAllThermometers() const;
};

#endif // THERMOMETERSTATISTICS_H
