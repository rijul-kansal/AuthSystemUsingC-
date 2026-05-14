#pragma once

#include "ITime.h"
class Time : public ITime
{
    public:
    long long getCurrentTime() const override;
    long long addTime(long long seconds) const override;
};