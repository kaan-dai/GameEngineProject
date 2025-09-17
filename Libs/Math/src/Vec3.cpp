//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "MathEngine.h"

namespace Azul
{
    // Constructor
    Vec3::Vec3()
    {
        _vx = 0.0f;
        _vy = 0.0f;
        _vz = 0.0f;
    }

    // Copy Constructor
    Vec3::Vec3(const Vec3& inV)
    {
        _vx = inV._vx;
        _vy = inV._vy;
        _vz = inV._vz;
    }

    // Assignment Operator
    Vec3 &Vec3::operator = (const Vec3 &v)
    {
        if (this != &v)
        {
            _vx = v._vx;
            _vy = v._vy;
            _vz = v._vz;
        }

        return *this;
    }

    // Destructor
    Vec3::~Vec3()
    {
       

    }

    // Constructor (x,y,z)
    Vec3::Vec3(const float in_x, const float in_y, const float in_z)
    {
        _vx = in_x;
        _vy = in_y;
        _vz = in_z;
    }

    // Explicit Constructor
    Vec3::Vec3(const Vec4& v)
    {
        _vx = v.x();
        _vy = v.y();
        _vz = v.z();
    }

    // Assignment Operator
    Vec3 &Vec3::operator = (const Vec4 &v)
    {
        _vx = v.x();
        _vy = v.y();
        _vz = v.z();

        return *this;
    }

    // (non-const) Bracket operator 
    float &Vec3::operator[] (const enum x_enum)
    {
        return _vx;
    }

    float &Vec3::operator[] (const enum y_enum)
    {
        return _vy;
    }

    float &Vec3::operator[] (const enum z_enum)
    {
        return _vz;
    }

    // (const) Bracket operator 
    float Vec3::operator[] (const enum x_enum) const
    {
        return _vx;
    }

    float Vec3::operator[] (const enum y_enum) const
    {
        return _vy;
    }

    float Vec3::operator[] (const enum z_enum) const
    {
        return _vz;
    }

    // Accessors
    void Vec3::x(const float v)
    {
        _vx = v;
    }

    void Vec3::y(const float v)
    {
        _vy = v;
    }

    void Vec3::z(const float v)
    {
        _vz = v;
    }

    float Vec3::x() const { 
        return _vx; 
    }

    float Vec3::y() const { 
        return _vy; 
    }

    float Vec3::z() const { 
        return _vz; 
    }


    Vec3 Vec3::operator + (void) const
    {
        return *this;
    }

    // Vector addition
    Vec3 Vec3::operator + (const Vec3 &inV) const
    {
        return Vec3(_vx + inV._vx, _vy + inV._vy, _vz + inV._vz);
    }

    Vec3 &Vec3::operator += (const Vec3 &inV)
    {
        _vx += inV._vx;
        _vy += inV._vy;
        _vz += inV._vz;

        return *this;
    }

    // Vector subtraction
    Vec3 Vec3::operator - (const Vec3 &inV) const
    {
        return Vec3(_vx - inV._vx, _vy - inV._vy, _vz - inV._vz);
    }

    Vec3 &Vec3::operator -= (const Vec3 &inV)
    {
        _vx -= inV._vx;
        _vy -= inV._vy;
        _vz -= inV._vz;

        return *this;
    }

    Vec3 Vec3::operator - (void) const
    {
        return Vec3(-_vx, -_vy, -_vz);
    }

    Vec3 Vec3::operator * (const float scale) const
    {
        return Vec3(_vx * scale, _vy * scale, _vz * scale);
    }

    Vec3 operator * (const float scale, const Vec3 &inV)
    {
        return Vec3(inV._vx * scale, inV._vy * scale, inV._vz * scale);
    }

    Vec3 &Vec3::operator *= (const float scale)
    {
        _vx *= scale;
        _vy *= scale;
        _vz *= scale;

        return *this;
    }

    // Vec3 * Mat3 
    Vec3 Vec3::operator * (const Mat3 &m) const
    {
        return Vec3(
            _vx * m._m0 + _vy * m._m4 + _vz * m._m8,
            _vx * m._m1 + _vy * m._m5 + _vz * m._m9,
            _vx * m._m2 + _vy * m._m6 + _vz * m._m10);
    }


    Vec3 &Vec3::operator *= (const Mat3& m)
    {
        *this = *this * m;

        return *this;
    }


    // Normalize 
    Vec3 &Vec3::norm(void)
    {
        float length = this->dot(*this);
        if (length > MATH_TOLERANCE * MATH_TOLERANCE) {

            length = Trig::rsqrt(length);
			_vx *= length;
			_vy *= length;
			_vz *= length;
		}
		else
		{
            assert(false);
		}

        return *this;
    }

    Vec3 Vec3::getNorm(void) const
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

        return Vec3(_vx * length, _vy * length, _vz * length);
    }

    // Dot
    float Vec3::dot(const Vec3 &vIn) const
    {
        return _vx * vIn._vx + _vy * vIn._vy + _vz * vIn._vz;
    }

    // Cross 
    Vec3 Vec3::cross(const Vec3 &vIn) const
    {
        return Vec3(_vy * vIn._vz - _vz * vIn._vy,
                    _vz * vIn._vx - _vx * vIn._vz,
                    _vx * vIn._vy - _vy * vIn._vx);
    }

    Vec3Proxy Vec3::len(void) const
    {
        return Vec3Proxy(_vx, _vy, _vz);
    }

    float Vec3::getAngle(const Vec3 &vIn) const
    {
        float dotVal = this->dot(vIn);
        float magA = Trig::sqrt(_vx * _vx + _vy * _vy + _vz * _vz);
        float magB = Trig::sqrt(vIn._vx * vIn._vx + vIn._vy * vIn._vy + vIn._vz * vIn._vz);

        if (magA < MATH_TOLERANCE || magB < MATH_TOLERANCE) {

            return 0.0f;
        }

        float cosTheta = dotVal / (magA * magB);
        if (cosTheta > 1.0f) {
            cosTheta = 1.0f;
        }  

        if (cosTheta < -1.0f) {
            cosTheta = -1.0f;
        }

        return Trig::acos(cosTheta);
    }

    // Set 
    void Vec3::set(const float inX, const float inY, const float inZ)
    {
        _vx = inX;
        _vy = inY;
        _vz = inZ;
    }

    void Vec3::set(const Vec3 &A)
    {
        _vx = A._vx;
        _vy = A._vy;
        _vz = A._vz;
    }

    void Vec3::set(const Vec4 &A)
    {
        _vx = A.x();
        _vy = A.y();
        _vz = A.z();
    }

    bool Vec3::isEqual(const Vec3 &v, const float epsilon) const
    {
        return Util::isEqual(_vx, v._vx, epsilon) &&
               Util::isEqual(_vy, v._vy, epsilon) &&
               Util::isEqual(_vz, v._vz, epsilon);
    }

    bool Vec3::isZero(const float epsilon) const
    {
        return Util::isZero(_vx, epsilon) &&
               Util::isZero(_vy, epsilon) &&
               Util::isZero(_vz, epsilon);
    }

    // Print
    void Vec3::Print(const char *pName) const
    {
       Trace::out("%s: [%f, %f, %f]\n", pName, _vx, _vy, _vz);
    }
}

//--- End of File ---
