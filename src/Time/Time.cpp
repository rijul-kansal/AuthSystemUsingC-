#include "Time.h"
#include <ctime>
long long Time::getCurrentTime() const 
{
    time_t timestamp = time(NULL);
    struct tm* datetime = new tm(*localtime(&timestamp));
    auto time =  mktime(datetime);
    delete datetime;
    return time;
}

long long Time::addTime(long long seconds) const
{
    return seconds + getCurrentTime();
}
