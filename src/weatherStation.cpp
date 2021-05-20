#include "WeatherStation.h"

#include <cstring>
#include <ctime>
#include <md5.h>

WeatherStation::WeatherStation(const char *uid, const char *passw)
    : m_uid(uid), m_passw(passw) {}

WeatherStation::WeatherStation(const WeatherStation &ws)
    : m_uid(ws.m_uid), m_passw(ws.m_passw), m_sensors(ws.m_sensors) {}

WeatherStation &WeatherStation::operator=(const WeatherStation &ws)
{
    if (this != &ws)
    {
        m_uid = ws.m_uid;
        m_passw = ws.m_passw;
        m_sensors = ws.m_sensors;
    }

    return *this;
}

const char *WeatherStation::getUID() const
{
    return m_uid;
}

const char *WeatherStation::getPassw() const
{
    return m_passw;
}

const char *WeatherStation::assembleURL()
{
    const size_t URL_SIZE = 250;
    const char *API_UPLOAD_URL = "http://www.windguru.cz/upload/api.php?";

    static char url[URL_SIZE];

    const char *salt = generateSalt();
    const char *hash = generateHash(salt);

    memset(url, 0, sizeof(url));
    sprintf(url,
            "%suid=%s&salt=%s&hash=%s&%s&%s%s",
            API_UPLOAD_URL,
            m_uid,
            salt,
            hash,
            "test_wind",
            m_sensors.getBME280DataAsHttpString(),
            m_sensors.getPrecipDataAsHttpString());

    return url;
}

const char *WeatherStation::generateSalt() const
{
    const size_t SALT_LEN = 15;
    static char salt[SALT_LEN];

    std::time_t currTime = std::time(nullptr);

    memset(salt, 0, sizeof(salt));
    strcpy(salt, std::asctime(std::localtime(&currTime))); // generate timestamp

    return salt;
}

const char *WeatherStation::generateHash(const char *salt) const
{
    const size_t HASH_LEN = 33;
    const size_t BUFF_SIZE = 16;

    static char hash[HASH_LEN];

    md5_context_t ctx;
    uint8_t buffer[BUFF_SIZE] = {0};

    MD5Init(&ctx);
    MD5Update(&ctx, reinterpret_cast<const uint8_t *>(salt), strlen(salt));
    MD5Update(&ctx, reinterpret_cast<const uint8_t *>(m_uid), strlen(m_uid));
    MD5Update(&ctx, reinterpret_cast<const uint8_t *>(m_passw), strlen(m_passw));
    MD5Final(buffer, &ctx);

    memset(hash, 0, strlen(hash));

    for (size_t i = 0; i < BUFF_SIZE; i++)
    {
        sprintf(hash + (i * 2), "%02x", buffer[i]);
    }

    return hash;
}
