#include "SensorDataProcessor.h"

#include <cstring>

SensorDataProcessor::SensorDataProcessor()
{
    m_bme280.begin();
};

SensorDataProcessor::SensorDataProcessor(const SensorDataProcessor &ws)
    : m_bme280(ws.m_bme280) {}

SensorDataProcessor &SensorDataProcessor::operator=(const SensorDataProcessor &ws)
{
    if (this != &ws)
    {
        m_bme280 = ws.m_bme280;
    }

    return *this;
}

const char *SensorDataProcessor::getBME280DataAsHttpString()
{
    const size_t BUFF_SIZE = 50;

    static char httpString[BUFF_SIZE];

    m_bme280.refresh();

    memset(httpString, 0, sizeof(httpString));
    sprintf(httpString,
            "temperature=%.2f&rh=%.2f&mslp=%.2f",
            m_bme280.temperature,        // [℃]
            m_bme280.humidity,           // [%]
            m_bme280.pressure / 100.0F); // [hPa]

    return httpString;
}

const char *SensorDataProcessor::getPrecipDataAsHttpString()
{
    const size_t BUFF_SIZE = 10;
    const int PRECIP_INTERVAL = 3600; // [s]

    static char httpString[BUFF_SIZE];
    static int precipUpdateCountDown;

    precipUpdateCountDown -= 60; // one minute

    if (0 < precipUpdateCountDown)
    {
        precipUpdateCountDown = PRECIP_INTERVAL;

        memset(httpString, 0, sizeof(httpString));
        sprintf(httpString, "&precip=%.2f", 0.0);

        return httpString;
    }

    return "\0";
}