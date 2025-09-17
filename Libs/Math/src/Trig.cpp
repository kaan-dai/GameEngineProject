//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include <math.h>    // <--- ONLY location for <math.h> allowed
#include "Trig.h"

namespace Azul
{

    float Trig::cos(const float angle_radians)
    {
        return ::cosf(angle_radians);
    }

    float Trig::sin(const float angle_radians)
    {
        return ::sinf(angle_radians);
    }

    float Trig::tan(const float val)
    {
        return ::tanf(val);
    }

    float Trig::atan(const float val)
    {
        return ::atanf(val);
    }

    float Trig::atan2(const float y, const float x)
    {
        return ::atan2f(y, x);
    }

    float Trig::acos(const float val)
    {
        return ::acosf(val);
    }

    float Trig::asin(const float val)
    {
        return ::asinf(val);
    }

    void Trig::cossin(float &cosOut, float &sinOut, const float angle_radians)
    {
        cosOut = ::cosf(angle_radians);
        sinOut = ::sinf(angle_radians);
    }

    float Trig::sqrt(const float val)
    {
        return ::sqrtf(val);
    }

    float Trig::rsqrt(const float val)
    {
        if (val <= 0) {
            return 0.0f;
        }

        return 1.0f / ::sqrtf(val);
    }

    float Trig::abs(const float val)
    {
        return ::fabsf(val);
    }

}

//--- End of File ---
