#pragma once

class ITime
{
    public:
    virtual long long getCurrentTime() const =0;
    virtual long long addTime(long long seconds) const =0;
    virtual ~ITime() = default;
};