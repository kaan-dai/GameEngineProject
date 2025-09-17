//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "MathEngine.h"

namespace Azul
{
    // Constructor
    Vec4::Vec4()
    {
        _vx = 0.0f;
        _vy = 0.0f;
        _vz = 0.0f;
        _vw = 0.0f;
    }

    // Copy Constructor
    Vec4::Vec4(const Vec4 &inV)
    {
        _vx = inV._vx;
        _vy = inV._vy;
        _vz = inV._vz;
        _vw = inV._vw;
    }

    // Assignment operator
    Vec4 &Vec4::operator=(const Vec4 &v)
    {
        if (this != &v)
        {
            _vx = v._vx;
            _vy = v._vy;
            _vz = v._vz;
            _vw = v._vw;
        }

        return *this;
    }

    // Destructor
    Vec4::~Vec4()
    {

    }

    // Constructor (x,y,z,w)
    Vec4::Vec4(const float in_x, const float in_y, const float in_z, const float in_w)
    {
        _vx = in_x;
        _vy = in_y;
        _vz = in_z;
        _vw = in_w;
    }

    // Constructor w Component
    Vec4::Vec4(const Vec3 &v, const float w)
    {
        _vx = v.x();
        _vy = v.y();
        _vz = v.z();
        _vw = w;
    }

    // (non-const) Bracket operator 
    float& Vec4::operator[] (const enum x_enum)
    {
        return _vx;
    }

    float& Vec4::operator[] (const enum y_enum)
    {
        return _vy;
    }

    float& Vec4::operator[] (const enum z_enum)
    {
        return _vz;
    }

    float& Vec4::operator[] (const enum w_enum)
    {
        return _vw;
    }

    // (const) Bracket operator 
    float Vec4::operator[] (const enum x_enum) const
    {
        return _vx;
    }

    float Vec4::operator[] (const enum y_enum) const
    {
        return _vy;
    }

    float Vec4::operator[] (const enum z_enum) const
    {
        return _vz;
    }

    float Vec4::operator[] (const enum w_enum) const
    {
        return _vw;
    }

    // Accessors
    void Vec4::x(const float v)
    {
        _vx = v;
    }

    void Vec4::y(const float v)
    {
        _vy = v;
    }

    void Vec4::z(const float v)
    {
        _vz = v;
    }

    void Vec4::w(const float v)
    {
        _vw = v;
    }

    float Vec4::x() const { 
        return _vx; 
    }

    float Vec4::y() const { 
        return _vy; 
    }

    float Vec4::z() const { 
        return _vz; 
    }

    float Vec4::w() const {
        return _vw; 
    }

    Vec4 Vec4::operator + (void) const
    {
        return *this;
    }

    // Vector Addition
    Vec4 Vec4::operator + (const Vec4 &inV) const
    {
        return Vec4(_vx + inV._vx, _vy + inV._vy, _vz + inV._vz, _vw + inV._vw);
    }

    Vec4 &Vec4::operator += (const Vec4 &inV)
    {
        _vx += inV._vx;
        _vy += inV._vy;
        _vz += inV._vz;
        _vw += inV._vw;

        return *this;
    }

    // Vector subtraction
    Vec4 Vec4::operator - (const Vec4 &inV) const
    {
        return Vec4(_vx - inV._vx, _vy - inV._vy, _vz - inV._vz, _vw - inV._vw);
    }

    Vec4 &Vec4::operator -= (const Vec4 &inV)
    {
        _vx -= inV._vx;
        _vy -= inV._vy;
        _vz -= inV._vz;
        _vw -= inV._vw;

        return *this;
    }

    Vec4 Vec4::operator - (void) const
    {
        return Vec4(-_vx, -_vy, -_vz, -_vw);
    }


    Vec4 Vec4::operator * (const float scale) const
    {
        return Vec4(_vx * scale, _vy * scale, _vz * scale, _vw * scale);
    }
    Vec4 operator * (const float scale, const Vec4 &inV)
    {
        return Vec4(inV._vx * scale, inV._vy * scale, inV._vz * scale, inV._vw * scale);
    }
    Vec4 &Vec4::operator *= (const float scale)
    {
        _vx *= scale;
        _vy *= scale;
        _vz *= scale;
        _vw *= scale;

        return *this;
    }

    // Vec4 * Mat4
    Vec4 Vec4::operator * (const Mat4 &m) const
    {
        return Vec4(
            _vx * m._m0 + _vy * m._m4 + _vz * m._m8 + _vw * m._m12,
            _vx * m._m1 + _vy * m._m5 + _vz * m._m9 + _vw * m._m13,
            _vx * m._m2 + _vy * m._m6 + _vz * m._m10 + _vw * m._m14,
            _vx * m._m3 + _vy * m._m7 + _vz * m._m11 + _vw * m._m15
        );
    }

    Vec4 &Vec4::operator *= (const Mat4 &m)
    {
        *this = *this * m;

        return *this;
    }

    // Normalize
    Vec4 &Vec4::norm(void)
    {
        float length = this->dot(*this);
        if (length > MATH_TOLERANCE * MATH_TOLERANCE) {

            length = Trig::rsqrt(length);
            _vx *= length;
            _vy *= length;
            _vz *= length;
			_vw *= length;
        }
        else
        {
            assert(false);
        }

        return *this;
    }

    Vec4 Vec4::getNorm(void) const
    {
        float length = this->dot(*this);

        if (length > MATH_TOLERANCE * MATH_TOLERANCE)
        {
            length = Trig::rsqrt(length);
        }
        else
        {
            assert(false);
        }

        return Vec4(_vx * length, _vy * length, _vz * length, _vw * length);
    }

    // Dot
    float Vec4::dot(const Vec4 &vIn) const
    {
        return _vx * vIn._vx + _vy * vIn._vy + _vz * vIn._vz + _vw * vIn._vw;
    }

    //Length
    Vec4Proxy Vec4::len() const
    {
        return Vec4Proxy(_vx, _vy, _vz, _vw);
    }

    // Set
    void Vec4::set(const float inX, const float inY, const float inZ, const float inW)
    {
        _vx = inX;
        _vy = inY;
        _vz = inZ;
        _vw = inW;
    }

    void Vec4::set(const Vec4 &A)
    {
        _vx = A._vx;
        _vy = A._vy;
        _vz = A._vz;
        _vw = A._vw;
    }

    void Vec4::set(const Vec3 &v, const float w)
    {
        _vx = v.x();
        _vy = v.y();
        _vz = v.z();
        _vw = w;
    }

    bool Vec4::isEqual(const Vec4 &v, const float epsilon) const
    {
        return Util::isEqual(_vx, v._vx, epsilon) &&
               Util::isEqual(_vy, v._vy, epsilon) &&
               Util::isEqual(_vz, v._vz, epsilon) &&
               Util::isEqual(_vw, v._vw, epsilon);
    }

    bool Vec4::isZero(const float epsilon) const
    {
        return Util::isZero(_vx, epsilon) &&
               Util::isZero(_vy, epsilon) &&
               Util::isZero(_vz, epsilon) &&
               Util::isZero(_vw, epsilon);
    }

    // Print
    void Vec4::Print(const char *pName) const
    {
        Trace::out("%s: [%f, %f, %f, %f]\n", pName, _vx, _vy, _vz, _vw);
    }
}

//--- End of File ---
