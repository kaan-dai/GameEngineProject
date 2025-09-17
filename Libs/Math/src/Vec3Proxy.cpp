//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "MathEngine.h"

namespace Azul
{
    // Constructor
    Vec3Proxy::Vec3Proxy(float a, float b, float c): x(a), y(b), z(c)
    {

    }

    // Conversion
    Vec3Proxy::operator float() const
    {
        return Trig::sqrt(x * x + y * y + z * z);
    }

    // Dot
    float Vec3Proxy::operator * (const Vec3Proxy &r) const
    {
        float A = x * x + y * y + z * z;
		float B = r.x * r.x + r.y * r.y + r.z* r.z;
        return Trig::sqrt(A * B);
    }

    // Comparison
    bool Vec3Proxy::operator > (const Vec3Proxy &r) const
    {
        float A = x * x + y * y + z * z;
		float B = r.x * r.x + r.y * r.y + r.z * r.z;
        return (A > B);
    }

    bool Vec3Proxy::operator < (const Vec3Proxy &r) const
    {
		float A = x * x + y * y + z * z;
		float B = r.x * r.x + r.y * r.y + r.z * r.z;
		return (A < B);
    }

    bool Vec3Proxy::operator == (const Vec3Proxy &r) const
    {
		float A = x * x + y * y + z * z;
		float B = r.x * r.x + r.y * r.y + r.z * r.z;
		return (A == B);
    }

    bool Vec3Proxy::operator >= (const Vec3Proxy &r) const
    {
		float A = x * x + y * y + z * z;
		float B = r.x * r.x + r.y * r.y + r.z * r.z;
		return (A >= B);
    }

    bool Vec3Proxy::operator <= (const Vec3Proxy &r) const
    {
		float A = x * x + y * y + z * z;
		float B = r.x * r.x + r.y * r.y + r.z * r.z;
		return (A <= B);
    }

    bool Vec3Proxy::operator != (const Vec3Proxy &r) const
    {
		float A = x * x + y * y + z * z;
		float B = r.x * r.x + r.y * r.y + r.z * r.z;
		return (A != B);
    }

}

//--- End of File ---
