//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "MathEngine.h"

namespace Azul
{
    // Constructor
    Scale::Scale()
    {
        this->set(Identity);
    }

    // Constructor With Values
    Scale::Scale(const float sx, const float sy, const float sz)
    {
        this->_m0 = sx;    this->_m1 = 0.0f;  this->_m2 = 0.0f;  this->_m3 = 0.0f;
        this->_m4 = 0.0f;  this->_m5 = sy;    this->_m6 = 0.0f;  this->_m7 = 0.0f;
        this->_m8 = 0.0f;  this->_m9 = 0.0f;  this->_m10 = sz;   this->_m11 = 0.0f;
        this->_m12 = 0.0f; this->_m13 = 0.0f; this->_m14 = 0.0f; this->_m15 = 1.0f;
    }

    // Constructor With Vec3.
    Scale::Scale(const Vec3 &vScale)
    {
        this->_m0 = vScale.x();    this->_m1 = 0.0f;         this->_m2 = 0.0f;         this->_m3 = 0.0f;
        this->_m4 = 0.0f;          this->_m5 = vScale.y();   this->_m6 = 0.0f;         this->_m7 = 0.0f;
        this->_m8 = 0.0f;          this->_m9 = 0.0f;         this->_m10 = vScale.z();  this->_m11 = 0.0f;
        this->_m12 = 0.0f;         this->_m13 = 0.0f;        this->_m14 = 0.0f;        this->_m15 = 1.0f;
    }

    // Constructor Identity 
    Scale::Scale(const enum Identity_enum)
    {
        this->_m0 = 1.0f;  this->_m1 = 0.0f;  this->_m2 = 0.0f;  this->_m3 = 0.0f;
        this->_m4 = 0.0f;  this->_m5 = 1.0f;  this->_m6 = 0.0f;  this->_m7 = 0.0f;
        this->_m8 = 0.0f;  this->_m9 = 0.0f;  this->_m10 = 1.0f; this->_m11 = 0.0f;
        this->_m12 = 0.0f; this->_m13 = 0.0f; this->_m14 = 0.0f; this->_m15 = 1.0f;
    }

    // Set
    void Scale::set(const float sx, const float sy, const float sz)
    {
        this->_m0 = sx;     this->_m1 = 0.0f;  this->_m2 = 0.0f;  this->_m3 = 0.0f;
        this->_m4 = 0.0f;   this->_m5 = sy;    this->_m6 = 0.0f;  this->_m7 = 0.0f;
        this->_m8 = 0.0f;   this->_m9 = 0.0f;  this->_m10 = sz;   this->_m11 = 0.0f;
        this->_m12 = 0.0f;  this->_m13 = 0.0f; this->_m14 = 0.0f; this->_m15 = 1.0f;
    }

    void Scale::set(const Vec3 &vScale)
    {
        set(vScale.x(), vScale.y(), vScale.z());
    }

    void Scale::set(const enum Identity_enum)
    {
        set(1.0f, 1.0f, 1.0f);
    }

}

// ---  End of File ---
