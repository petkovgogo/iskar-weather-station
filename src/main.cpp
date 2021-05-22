#include <Arduino.h>
#include "WeatherStation.h"

const int DELAY = 60; // [s]

// Function prototypes
bool millisDelay(uint64_t delay);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    static WeatherStation station("IskarStation", "123456789");

    if (millisDelay(DELAY * 1000))
    {
        Serial.println(station.assembleURL());
    }
}

bool millisDelay(uint64_t delay)
{
    static uint64_t startMillis;

    // if a new measurement is started, startMillis will be equal to 0
    // and after the calculation it will become equal to millis(),
    // but if the old delay is still active, the expression will evaluate to 0,
    // meaning startMillis will not be changed
    startMillis += !startMillis * millis();

    if (millis() - startMillis > delay)
    {
        startMillis = 0;

        return true;
    }

    return false;
}