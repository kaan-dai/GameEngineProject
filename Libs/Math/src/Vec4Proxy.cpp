//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "MathEngine.h"

namespace Azul
{
    // Constructor
    Vec4Proxy::Vec4Proxy(float a, float b, float c, float d) : x(a), y(b), z(c), w(d)
    {
    }

    // Conversion 
    Vec4Proxy::operator float() const
    {
        return Trig::sqrt(x * x + y * y + z * z + w * w);
    }

    // Dot
    float Vec4Proxy::operator * (const Vec4Proxy &r) const
    {
        float A = x * x + y * y + z * z + w * w;
        float B = r.x * r.x + r.y * r.y + r.z * r.z + r.w + r.w;
        return Trig::sqrt(A * B);
    }

    // Comparison
    bool Vec4Proxy::operator > (const Vec4Proxy &r) const
    { 
		float A = x * x + y * y + z * z + w * w;
		float B = r.x * r.x + r.y * r.y + r.z * r.z + r.w * r.w;
		return (A > B);
    }

    bool Vec4Proxy::operator < (const Vec4Proxy &r) const
    {
		float A = x * x + y * y + z * z + w * w;
		float B = r.x * r.x + r.y * r.y + r.z * r.z + r.w * r.w;
		return (A < B);
    }

    bool Vec4Proxy::operator == (const Vec4Proxy &r) const
    {
		float A = x * x + y * y + z * z + w * w;
		float B = r.x * r.x + r.y * r.y + r.z * r.z + r.w * r.w;
		return (A == B);
    }

    bool Vec4Proxy::operator >= (const Vec4Proxy &r) const
    {
		float A = x * x + y * y + z * z + w * w;
		float B = r.x * r.x + r.y * r.y + r.z * r.z + r.w * r.w;
		return (A >= B);
    }

    bool Vec4Proxy::operator <= (const Vec4Proxy &r) const
    {
		float A = x * x + y * y + z * z + w * w;
		float B = r.x * r.x + r.y * r.y + r.z * r.z + r.w * r.w;
		return (A <= B);
    }

    bool Vec4Proxy::operator != (const Vec4Proxy &r) const
    {
		float A = x * x + y * y + z * z + w * w;
		float B = r.x * r.x + r.y * r.y + r.z * r.z + r.w * r.w;
		return (A != B);
    }
}

//--- End of File ---
