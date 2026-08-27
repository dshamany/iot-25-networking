#include "timestamp.h"

std::string time_to_iso8601(time_t timestamp)
{
    struct tm utcTime;
    gmtime_r(&timestamp, &utcTime);

    char buffer[25];

    strftime(
        buffer,
        sizeof(buffer),
        "%Y-%m-%dT%H:%M:%SZ",
        &utcTime
    );

    return std::string(buffer);
}
