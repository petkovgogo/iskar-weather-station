#ifndef SENSOR_DATA_PROCESSOR_H
#define SENSOR_DATA_PROCESSOR_H

#include "BME280Sensor.h"

class SensorDataProcessor
{
public:
    SensorDataProcessor();
    SensorDataProcessor(const SensorDataProcessor &);
    ~SensorDataProcessor() = default;

    SensorDataProcessor &operator=(const SensorDataProcessor &);

    const char *getBME280DataAsHttpString();
    const char *getPrecipDataAsHttpString();

private:

    BME280Sensor m_bme280;

    // TODO Add other sensors
};

#endif // SENSOR_DATA_PROCESSOR_H