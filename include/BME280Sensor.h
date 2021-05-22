#ifndef BME280_SENSOR_H
#define BME280_SENSOR_H

#include <Ticker.h>
#include <Wire.h>
#include <BME280_t.h>

class BME280Sensor
{
public:
    BME280Sensor();
    BME280Sensor(const BME280Sensor &);
    ~BME280Sensor() = default;

    BME280Sensor &operator=(const BME280Sensor &);

    void sample();

    float getAvgTemperature();
    float getAvgHumidity();
    float getAvgPressure();

private:
    // Refreshes the sensor data every SAMPLE_RATE seconds of SAMPLE_INTERVAL
    static const int SAMPLE_INTERVAL = 60; // [s]
    static const int SAMPLE_RATE = 6;      // [s]

    static BME280Sensor* sampledInstance;
    static Ticker sampler;
    
    static void refresh_callback();
    
    BME280<> m_bme280;

    float m_avgTemperature;
    float m_avgHumidity;
    float m_avgPressure;
};

#endif // BME280_SENSOR_H