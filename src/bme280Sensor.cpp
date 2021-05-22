#include "BME280Sensor.h"

BME280Sensor *BME280Sensor::sampledInstance;
Ticker BME280Sensor::sampler;

BME280Sensor::BME280Sensor()
    : m_avgTemperature(0.0),
      m_avgHumidity(0.0),
      m_avgPressure(0.0)
{
    sample();
    m_bme280.begin();
}

BME280Sensor::BME280Sensor(const BME280Sensor &sensor)
    : m_bme280(sensor.m_bme280),
      m_avgTemperature(sensor.m_avgTemperature),
      m_avgHumidity(sensor.m_avgHumidity),
      m_avgPressure(sensor.m_avgPressure) {}

BME280Sensor &BME280Sensor::operator=(const BME280Sensor &sensor)
{
    if (this != &sensor)
    {
        m_avgTemperature = sensor.m_avgTemperature;
        m_avgHumidity = sensor.m_avgHumidity;
        m_avgPressure = sensor.m_avgPressure;
        m_bme280 = sensor.m_bme280;
    }

    return *this;
}

void BME280Sensor::refresh_callback()
{
    sampledInstance->m_bme280.refresh();
    sampledInstance->m_avgTemperature += sampledInstance->m_bme280.temperature;
    sampledInstance->m_avgHumidity += sampledInstance->m_bme280.humidity;
    sampledInstance->m_avgPressure += sampledInstance->m_bme280.pressure;
}

void BME280Sensor::sample()
{
    static bool samplerInitialized = false;

    if (!samplerInitialized)
    {
        sampler.attach(SAMPLE_RATE, BME280Sensor::refresh_callback);
        samplerInitialized = true;
    }

    sampledInstance = this;
}

float BME280Sensor::getAvgTemperature()
{
    float temp = m_avgTemperature / (SAMPLE_INTERVAL / SAMPLE_RATE);
    m_avgTemperature = 0;

    return temp;
}

float BME280Sensor::getAvgHumidity()
{
    float temp = m_avgHumidity / (SAMPLE_INTERVAL / SAMPLE_RATE);
    m_avgHumidity = 0;

    return temp;
}

float BME280Sensor::getAvgPressure()
{
    float temp = m_avgPressure / (SAMPLE_INTERVAL / SAMPLE_RATE);
    m_avgPressure = 0;

    return temp;
}