//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "MathEngine.h"

namespace Azul
{
    void Mat3::Swap(float &a, float &b)
    {
        float temp = a;
        a = b;
        b = temp;
    }

    // Constructor
    Mat3::Mat3()
    {
        _m0 = 0.0f;    _m1 = 0.0f;    _m2 = 0.0f;    _m3 = 0.0f;
        _m4 = 0.0f;    _m5 = 0.0f;    _m6 = 0.0f;    _m7 = 0.0f;
        _m8 = 0.0f;    _m9 = 0.0f;    _m10 = 0.0f;   _m11 = 0.0f;
        _m12 = 0.0f;   _m13 = 0.0f;   _m14 = 0.0f;   _m15 = 1.0f;
    }


    // Copy Constructor
    Mat3::Mat3(const Mat3 &tM)
    {
        for (int i = 0; i < 16; i++)
        {
            ((float*)this)[i] = ((const float*)&tM)[i];
        }
    }

    // Assignment Operator
    Mat3 &Mat3::operator = (const Mat3 &A)
    {
        if (this != &A)
        {
            for (int i = 0; i < 16; i++)
            {
                ((float*)this)[i] = ((const float*)&A)[i];
            }
        }

        return *this;
    }

    // Destructor
    Mat3::~Mat3()
    {

    }

    // Construct 3 Vec3 Rows
    Mat3::Mat3(const Vec3 &tV0, const Vec3 &tV1, const Vec3 &tV2)
    {
        _v0 = Vec4(tV0.x(), tV0.y(), tV0.z(), 0.0f);
        _v1 = Vec4(tV1.x(), tV1.y(), tV1.z(), 0.0f);
        _v2 = Vec4(tV2.x(), tV2.y(), tV2.z(), 0.0f);
        _v3 = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }

    Mat3::Mat3(const Mat4 &m)
    {
        _m0 = m.m0();
        _m1 = m.m1();
        _m2 = m.m2();
        _m3 = 0.0f;

        _m4 = m.m4();
        _m5 = m.m5();
        _m6 = m.m6();
        _m7 = 0.0f;

        _m8 = m.m8();
        _m9 = m.m9();
        _m10 = m.m10();
        _m11 = 0.0f;

        _m12 = 0.0f;
        _m13 = 0.0f;
        _m14 = 0.0f;
        _m15 = 1.0f;
    }

    // Construct Identity
    Mat3::Mat3(const enum Identity_enum)
    {
        _m0 = 1.0f;   _m1 = 0.0f;   _m2 = 0.0f;   _m3 = 0.0f;
        _m4 = 0.0f;   _m5 = 1.0f;   _m6 = 0.0f;   _m7 = 0.0f;
        _m8 = 0.0f;   _m9 = 0.0f;   _m10 = 1.0f;   _m11 = 0.0f;
        _m12 = 0.0f;   _m13 = 0.0f;   _m14 = 0.0f;   _m15 = 1.0f;
    }


    //Get
    Vec3 Mat3::get(const Row3 type) const
    {
        switch (type)
        {
        case Row3::i0:
            return Vec3(_v0.x(), _v0.y(), _v0.z());

        case Row3::i1:
            return Vec3(_v1.x(), _v1.y(), _v1.z());

        case Row3::i2:
            return Vec3(_v2.x(), _v2.y(), _v2.z());

        default:

            return Vec3();
        }
    }

    // Set
    void Mat3::set(const Mat3 &mIn)
    {
        for (int i = 0; i < 16; i++)
        {
            ((float*)this)[i] = ((const float*)&mIn)[i];
        }
    }

    // Set Identity
    void Mat3::set(const enum Identity_enum)
    {
        _m0 = 1.0f;   _m1 = 0.0f;   _m2 = 0.0f;   _m3 = 0.0f;
        _m4 = 0.0f;   _m5 = 1.0f;   _m6 = 0.0f;   _m7 = 0.0f;
        _m8 = 0.0f;   _m9 = 0.0f;   _m10 = 1.0f;   _m11 = 0.0f;
        _m12 = 0.0f;   _m13 = 0.0f;   _m14 = 0.0f;   _m15 = 1.0f;
    }

    // Set Row
    void Mat3::set(const Row3 type, const Vec3 &V)
    {
        switch (type)
        {
        case Row3::i0:
            _v0.x(V.x());
            _v0.y(V.y());
            _v0.z(V.z());

            break;

        case Row3::i1:
            _v1.x(V.x());
            _v1.y(V.y());
            _v1.z(V.z());

            break;

        case Row3::i2:
            _v2.x(V.x());
            _v2.y(V.y());
            _v2.z(V.z());

            break;

        default:

            break;
        }
    }

    // Set 3 Rows
    void Mat3::set(const Vec3 &V0, const Vec3 &V1, const Vec3 &V2)
    {
        set(Row3::i0, V0);
        set(Row3::i1, V1);
        set(Row3::i2, V2);
    }


    // Bracket Operators
    float &Mat3::operator[] (const enum m0_enum) {
        return _m0;
    }

    float &Mat3::operator[] (const enum m1_enum) {
        return _m1;
    }

    float &Mat3::operator[] (const enum m2_enum) {
        return _m2;
    }

    float &Mat3::operator[] (const enum m4_enum) {
        return _m4;
    }

    float &Mat3::operator[] (const enum m5_enum) {
        return _m5;
    }

    float &Mat3::operator[] (const enum m6_enum) {
        return _m6;
    }

    float &Mat3::operator[] (const enum m8_enum) {
        return _m8;
    }

    float &Mat3::operator[] (const enum m9_enum) {
        return _m9;
    }

    float &Mat3::operator[] (const enum m10_enum) {
        return _m10;
    }


    float Mat3::operator[] (const enum m0_enum) const {
        return _m0;
    }

    float Mat3::operator[] (const enum m1_enum) const {
        return _m1;
    }

    float Mat3::operator[] (const enum m2_enum) const {
        return _m2;
    }

    float Mat3::operator[] (const enum m4_enum) const {
        return _m4;
    }

    float Mat3::operator[] (const enum m5_enum) const {
        return _m5;
    }

    float Mat3::operator[] (const enum m6_enum) const {
        return _m6;
    }

    float Mat3::operator[] (const enum m8_enum) const {
        return _m8;
    }

    float Mat3::operator[] (const enum m9_enum) const {
        return _m9;
    }

    float Mat3::operator[] (const enum m10_enum) const {
        return _m10;
    }


    // Accessors
    void Mat3::m0(const float v) {
        _m0 = v;
    }

    void Mat3::m1(const float v) {
        _m1 = v;
    }

    void Mat3::m2(const float v) {
        _m2 = v;
    }

    void Mat3::m4(const float v) {
        _m4 = v;
    }

    void Mat3::m5(const float v) {
        _m5 = v;
    }

    void Mat3::m6(const float v) {
        _m6 = v;
    }

    void Mat3::m8(const float v) {
        _m8 = v;
    }

    void Mat3::m9(const float v) {
        _m9 = v;
    }

    void Mat3::m10(const float v) {
        _m10 = v;
    }


    float Mat3::m0() const {
        return _m0;
    }

    float Mat3::m1() const {
        return _m1;
    }

    float Mat3::m2() const {
        return _m2;
    }

    float Mat3::m4() const {
        return _m4;
    }

    float Mat3::m5() const {
        return _m5;
    }

    float Mat3::m6() const {
        return _m6;
    }

    float Mat3::m8() const {
        return _m8;
    }

    float Mat3::m9() const {
        return _m9;
    }

    float Mat3::m10() const {
        return _m10;
    }


    // Determinant
    float Mat3::det() const
    {
        return _m0 * (_m5 * _m10 - _m6 * _m9) -
               _m1 * (_m4 * _m10 - _m6 * _m8) +
               _m2 * (_m4 * _m9 - _m5 * _m8);
    }


    // Transpose
    Mat3 &Mat3::T(void)
    {
        Swap(_m1, _m4);
        Swap(_m2, _m8);
        Swap(_m6, _m9);

        return *this;
    }

    Mat3 Mat3::getT(void) const
    {
        Mat3 temp(*this);

        return temp.T();
    }


    // Inverse
    Mat3 Mat3::getInv(void) const
    {
        float determinant = this->det();
        assert(!Util::isZero(determinant, 0.0f));

        Mat3 inv;
        float invDet = 1.0f / determinant;
   
        inv._m0 = (_m5 * _m10 - _m6 * _m9) * invDet;
        inv._m1 = (_m2 * _m9 - _m1 * _m10) * invDet;
        inv._m2 = (_m1 * _m6 - _m2 * _m5) * invDet;

        inv._m4 = (_m6 * _m8 - _m4 * _m10) * invDet;
        inv._m5 = (_m0 * _m10 - _m2 * _m8) * invDet;
        inv._m6 = (_m2 * _m4 - _m0 * _m6) * invDet;

        inv._m8 = (_m4 * _m9 - _m5 * _m8) * invDet;
        inv._m9 = (_m1 * _m8 - _m0 * _m9) * invDet;
        inv._m10 = (_m0 * _m5 - _m1 * _m4) * invDet;

        inv._m3 = 0.0f;
        inv._m7 = 0.0f;
        inv._m11 = 0.0f;
        inv._m12 = 0.0f;
        inv._m13 = 0.0f;
        inv._m14 = 0.0f;
        inv._m15 = 1.0f; 

        return inv;

    }

    Mat3& Mat3::inv(void)
    {
        *this = getInv();

        return *this;
    }


    // Comparison
    bool Mat3::isEqual(const Mat3 &A, const float epsilon) const
    {
        return Util::isEqual(_m0, A._m0, epsilon) &&
               Util::isEqual(_m1, A._m1, epsilon) &&
               Util::isEqual(_m2, A._m2, epsilon) &&
               Util::isEqual(_m4, A._m4, epsilon) &&
               Util::isEqual(_m5, A._m5, epsilon) &&
               Util::isEqual(_m6, A._m6, epsilon) &&
               Util::isEqual(_m8, A._m8, epsilon) &&
               Util::isEqual(_m9, A._m9, epsilon) &&
               Util::isEqual(_m10, A._m10, epsilon);

    }

    bool Mat3::isIdentity(const float epsilon) const
    {
        Mat3 I(Identity);

        return this->isEqual(I, epsilon);
    }

    // Addition Operators
    Mat3 Mat3::operator + (void) const
    {
        return *this;
    }

    Mat3 Mat3::operator + (const Mat3 &A) const
    {
        Mat3 result;
        result._m0 = _m0 + A._m0;
        result._m1 = _m1 + A._m1;
        result._m2 = _m2 + A._m2;
        result._m4 = _m4 + A._m4;
        result._m5 = _m5 + A._m5;
        result._m6 = _m6 + A._m6;
        result._m8 = _m8 + A._m8;
        result._m9 = _m9 + A._m9;
        result._m10 = _m10 + A._m10;

        result._m3 = 0.0f;
        result._m7 = 0.0f;
        result._m11 = 0.0f;
        result._m12 = 0.0f;
        result._m13 = 0.0f;
        result._m14 = 0.0f;
        result._m15 = 1.0f;

        return result;
    }

    Mat3 &Mat3::operator += (const Mat3 &A)
    {
        *this = *this + A;

        return *this;
    }



    // Subtraction Operators
    Mat3 Mat3::operator - (void) const
    {
        Mat3 result;

        result._m0 = -_m0;
        result._m1 = -_m1;
        result._m2 = -_m2;
        result._m4 = -_m4;
        result._m5 = -_m5;
        result._m6 = -_m6;
        result._m8 = -_m8;
        result._m9 = -_m9;
        result._m10 = -_m10;

        result._m3 = 0.0f;
        result._m7 = 0.0f;
        result._m11 = 0.0f;
        result._m12 = 0.0f;
        result._m13 = 0.0f;
        result._m14 = 0.0f;
        result._m15 = 1.0f;

        return result;
    }


    Mat3 Mat3::operator - (const Mat3 &A) const
    {
        Mat3 result;

        result._m0 = _m0 - A._m0;
        result._m1 = _m1 - A._m1;
        result._m2 = _m2 - A._m2;
        result._m4 = _m4 - A._m4;
        result._m5 = _m5 - A._m5;
        result._m6 = _m6 - A._m6;
        result._m8 = _m8 - A._m8;
        result._m9 = _m9 - A._m9;
        result._m10 = _m10 - A._m10;

        result._m3 = 0.0f;
        result._m7 = 0.0f;
        result._m11 = 0.0f;
        result._m12 = 0.0f;
        result._m13 = 0.0f;
        result._m14 = 0.0f;
        result._m15 = 1.0f;

        return result;
    }

    Mat3 &Mat3::operator -= (const Mat3 &A)
    {
        *this = *this - A;

        return *this;
    }


    // Scale
    Mat3 Mat3::operator * (const float s) const
    {
        Mat3 result;

        result._m0 = _m0 * s;
        result._m1 = _m1 * s;
        result._m2 = _m2 * s;
        result._m4 = _m4 * s;
        result._m5 = _m5 * s;
        result._m6 = _m6 * s;
        result._m8 = _m8 * s;
        result._m9 = _m9 * s;
        result._m10 = _m10 * s;

        result._m3 = 0.0f;
        result._m7 = 0.0f;
        result._m11 = 0.0f;
        result._m12 = 0.0f;
        result._m13 = 0.0f;
        result._m14 = 0.0f;
        result._m15 = 1.0f;

        return result;
    }

    Mat3 operator * (const float scale, const Mat3 &A)
    {
        return A * scale;
    }

    Mat3 &Mat3::operator *= (const float scale)
    {
        *this = *this * scale;

        return *this;
    }



    // Matrix Multiplication
    Mat3 Mat3::operator * (const Mat3 &A) const
    {
        Mat3 result;

        // Row 0:
        result._m0 = _m0 * A._m0 + _m1 * A._m4 + _m2 * A._m8;
        result._m1 = _m0 * A._m1 + _m1 * A._m5 + _m2 * A._m9;
        result._m2 = _m0 * A._m2 + _m1 * A._m6 + _m2 * A._m10;

        // Row 1:
        result._m4 = _m4 * A._m0 + _m5 * A._m4 + _m6 * A._m8;
        result._m5 = _m4 * A._m1 + _m5 * A._m5 + _m6 * A._m9;
        result._m6 = _m4 * A._m2 + _m5 * A._m6 + _m6 * A._m10;

        // Row 2:
        result._m8 = _m8 * A._m0 + _m9 * A._m4 + _m10 * A._m8;
        result._m9 = _m8 * A._m1 + _m9 * A._m5 + _m10 * A._m9;
        result._m10 = _m8 * A._m2 + _m9 * A._m6 + _m10 * A._m10;

        //Rest
        result._m3 = 0.0f;
        result._m7 = 0.0f;
        result._m11 = 0.0f;
        result._m12 = 0.0f;
        result._m13 = 0.0f;
        result._m14 = 0.0f;
        result._m15 = 1.0f;

        return result;
    }

    Mat3 &Mat3::operator *= (const Mat3 &A)
    {
        *this = *this * A;

        return *this;
    }



    // Print
    void Mat3::Print(const char *pName) const
    {
        Trace::out("%s:\n", pName);
        Trace::out("| %f %f %f %f |\n", _m0, _m1, _m2, _m3);
        Trace::out("| %f %f %f %f |\n", _m4, _m5, _m6, _m7);
        Trace::out("| %f %f %f %f |\n", _m8, _m9, _m10, _m11);
        Trace::out("| %f %f %f %f |\n", _m12, _m13, _m14, _m15);
    }

}

// ---  End of File ---
