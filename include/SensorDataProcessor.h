#ifndef SENSOR_DATA_PROCESSOR_H
#define SENSOR_DATA_PROCESSOR_H

#include <Wire.h>
#include <BME280_t.h>

class SensorDataProcessor
{
public:
    SensorDataProcessor();
    SensorDataProcessor(const SensorDataProcessor &);
    ~SensorDataProcessor() = default;

    SensorDataProcessor &operator=(const SensorDataProcessor &);

    const char *getBME280DataAsHttpString();
    const char *getPrecipDataAsHttpString();

    // TODO Add other sensor httpstrings

private:

    BME280<> m_bme280;

    // TODO Add other sensors
};

#endif // SENSOR_DATA_PROCESSOR_H