#ifndef STATION_H
#define STATION_H

#include "SensorDataProcessor.h"

class WeatherStation
{
public:
    WeatherStation(const char *uid, const char *passw);
    WeatherStation(const WeatherStation &);
    ~WeatherStation() = default;

    WeatherStation &operator=(const WeatherStation &);

    const char *getUID() const;
    const char *getPassw() const;
    const char *assembleURL();

private:
    const char *m_uid;
    const char *m_passw;
    SensorDataProcessor m_sensors;

    const char *generateSalt() const;
    const char *generateHash(const char *salt) const;
};

#endif // STATION_H