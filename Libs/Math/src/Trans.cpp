//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "MathEngine.h"

namespace Azul
{
    // Constructor
    Trans::Trans()
    {
        this->set(Identity);
    }

    // Constructor With Values
    Trans::Trans(const float tx, const float ty, const float tz)
    {
        this->_m0 = 1.0f; this->_m1 = 0.0f; this->_m2 = 0.0f; this->_m3 = 0.0f;
        this->_m4 = 0.0f; this->_m5 = 1.0f; this->_m6 = 0.0f; this->_m7 = 0.0f;
        this->_m8 = 0.0f; this->_m9 = 0.0f; this->_m10 = 1.0f; this->_m11 = 0.0f;
        this->_m12 = tx; this->_m13 = ty; this->_m14 = tz; this->_m15 = 1.0f;
    }

    // Constructor With Translation Vec
    Trans::Trans(const Vec3 &vTrans)
    {
        this->_m0 = 1.0f; this->_m1 = 0.0f; this->_m2 = 0.0f; this->_m3 = 0.0f;
        this->_m4 = 0.0f; this->_m5 = 1.0f; this->_m6 = 0.0f; this->_m7 = 0.0f;
        this->_m8 = 0.0f; this->_m9 = 0.0f; this->_m10 = 1.0f; this->_m11 = 0.0f;
        this->_m12 = vTrans.x(); this->_m13 = vTrans.y(); this->_m14 = vTrans.z(); this->_m15 = 1.0f;
    }

    // Constructor Identity
    Trans::Trans(const enum Identity_enum)
    {
        this->_m0 = 1.0f; this->_m1 = 0.0f; this->_m2 = 0.0f; this->_m3 = 0.0f;
        this->_m4 = 0.0f; this->_m5 = 1.0f; this->_m6 = 0.0f; this->_m7 = 0.0f;
        this->_m8 = 0.0f; this->_m9 = 0.0f; this->_m10 = 1.0f; this->_m11 = 0.0f;
        this->_m12 = 0.0f; this->_m13 = 0.0f; this->_m14 = 0.0f; this->_m15 = 1.0f;
    }

    // Set
    void Trans::set(const float tx, const float ty, const float tz)
    {
        this->_m12 = tx;
        this->_m13 = ty;
        this->_m14 = tz;
    }

    void Trans::set(const Vec3 &vTrans)
    {
        set(vTrans.x(), vTrans.y(), vTrans.z());
    }

    void Trans::set(const enum Identity_enum)
    {
        
        this->_m0 = 1.0f; this->_m1 = 0.0f; this->_m2 = 0.0f; this->_m3 = 0.0f;
        this->_m4 = 0.0f; this->_m5 = 1.0f; this->_m6 = 0.0f; this->_m7 = 0.0f;
        this->_m8 = 0.0f; this->_m9 = 0.0f; this->_m10 = 1.0f; this->_m11 = 0.0f;
        this->_m12 = 0.0f; this->_m13 = 0.0f; this->_m14 = 0.0f; this->_m15 = 1.0f;
    }
}

// ---  End of File ---
