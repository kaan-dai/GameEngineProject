//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "MathEngine.h"

namespace Azul
{
    void Mat4::Swap(float& a, float& b)
    {
        float temp = a;
        a = b;
        b = temp;
    }

    // Constructor
    Mat4::Mat4()
    {
        _m0 = 0.0f;  _m1 = 0.0f;  _m2 = 0.0f;  _m3 = 0.0f;
        _m4 = 0.0f;  _m5 = 0.0f;  _m6 = 0.0f;  _m7 = 0.0f;
        _m8 = 0.0f;  _m9 = 0.0f;  _m10 = 0.0f; _m11 = 0.0f;
        _m12 = 0.0f; _m13 = 0.0f; _m14 = 0.0f; _m15 = 0.0f;
    }


    // Copy Constructor
    Mat4::Mat4(const Mat4 &m)
    {
        for (int i = 0; i < 16; i++)
        {
            ((float*)this)[i] = ((const float*)&m)[i];
        }
    }

    // Assignment Operator
    Mat4 &Mat4::operator=(const Mat4 &m)
    {
        if (this != &m)
        {
            for (int i = 0; i < 16; i++)
            {
                ((float*)this)[i] = ((const float*)&m)[i];
            }
        }

        return *this;
    }

    // Destructor
    Mat4::~Mat4()
    {

    }

    // Construct 4 Vec4 Rows
    Mat4::Mat4(const Vec4 &tV0, const Vec4 &tV1, const Vec4 &tV2, const Vec4 &tV3)
    {
        _v0 = tV0;
        _v1 = tV1;
        _v2 = tV2;
        _v3 = tV3;
    }

    // Construct Identity
    Mat4::Mat4(const enum Identity_enum)
    {
        _m0 = 1.0f; _m1 = 0.0f; _m2 = 0.0f; _m3 = 0.0f;
        _m4 = 0.0f; _m5 = 1.0f; _m6 = 0.0f; _m7 = 0.0f;
        _m8 = 0.0f; _m9 = 0.0f; _m10 = 1.0f; _m11 = 0.0f;
        _m12 = 0.0f; _m13 = 0.0f; _m14 = 0.0f; _m15 = 1.0f;
    }

    // Set
    void Mat4::set(const Mat4 &mIn)
    {
        for (int i = 0; i < 16; i++)
        {
            ((float*)this)[i] = ((const float*)&mIn)[i];
        }
    }

    void Mat4::set(const Vec4 &V0, const Vec4 &V1, const Vec4 &V2, const Vec4 &V3)
    {
        _v0 = V0;
        _v1 = V1;
        _v2 = V2;
        _v3 = V3;
    }

    // Set Identity
    void Mat4::set(const enum Identity_enum)
    {
        _m0 = 1.0f; _m1 = 0.0f; _m2 = 0.0f; _m3 = 0.0f;
        _m4 = 0.0f; _m5 = 1.0f; _m6 = 0.0f; _m7 = 0.0f;
        _m8 = 0.0f; _m9 = 0.0f; _m10 = 1.0f; _m11 = 0.0f;
        _m12 = 0.0f; _m13 = 0.0f; _m14 = 0.0f; _m15 = 1.0f;
    }

    // Set Row
    void Mat4::set(const Row4 type, const Vec4 &V)
    {
        switch (type)
        {
        case Row4::i0:
            _v0 = V;

            break;

        case Row4::i1:
            _v1 = V;

            break;

        case Row4::i2:
            _v2 = V;

            break;

        case Row4::i3:
            _v3 = V;

            break;

        default:

            break;
        }
    }

    // Get
    Vec4 Mat4::get(const Row4 type) const
    {
        switch (type)
        {
        case Row4::i0:
            return _v0;

        case Row4::i1:
            return _v1;

        case Row4::i2:
            return _v2;

        case Row4::i3:
            return _v3;

        default:
            return Vec4();

        }
    }

    // (non-const) Bracket operators 
    Mat4Proxy Mat4::operator[](const m0_enum) {
        return Mat4Proxy(*this, _m0);
    }

    Mat4Proxy Mat4::operator[](const m1_enum) {
        return Mat4Proxy(*this, _m1);
    }

    Mat4Proxy Mat4::operator[](const m2_enum) {
        return Mat4Proxy(*this, _m2);
    }

    Mat4Proxy Mat4::operator[](const m3_enum) {
        return Mat4Proxy(*this, _m3);
    }

    Mat4Proxy Mat4::operator[](const m4_enum) {
        return Mat4Proxy(*this, _m4);
    }

    Mat4Proxy Mat4::operator[](const m5_enum) {
        return Mat4Proxy(*this, _m5);
    }

    Mat4Proxy Mat4::operator[](const m6_enum) {
        return Mat4Proxy(*this, _m6);
    }

    Mat4Proxy Mat4::operator[](const m7_enum) {
        return Mat4Proxy(*this, _m7);
    }

    Mat4Proxy Mat4::operator[](const m8_enum) {
        return Mat4Proxy(*this, _m8);
    }

    Mat4Proxy Mat4::operator[](const m9_enum) {
        return Mat4Proxy(*this, _m9);
    }

    Mat4Proxy Mat4::operator[](const m10_enum) {
        return Mat4Proxy(*this, _m10);
    }

    Mat4Proxy Mat4::operator[](const m11_enum) {
        return Mat4Proxy(*this, _m11);
    }

    Mat4Proxy Mat4::operator[](const m12_enum) {
        return Mat4Proxy(*this, _m12);
    }

    Mat4Proxy Mat4::operator[](const m13_enum) {
        return Mat4Proxy(*this, _m13);
    }

    Mat4Proxy Mat4::operator[](const m14_enum) {
        return Mat4Proxy(*this, _m14);
    }

    Mat4Proxy Mat4::operator[](const m15_enum) {
        return Mat4Proxy(*this, _m15);
    }


    // (const) Bracket operators 
    float Mat4::operator[](const m0_enum) const {
        return _m0;
    }

    float Mat4::operator[](const m1_enum) const {
        return _m1;
    }

    float Mat4::operator[](const m2_enum) const {
        return _m2;
    }

    float Mat4::operator[](const m3_enum) const {
        return _m3;
    }

    float Mat4::operator[](const m4_enum) const {
        return _m4;
    }

    float Mat4::operator[](const m5_enum) const {
        return _m5;
    }

    float Mat4::operator[](const m6_enum) const {
        return _m6;
    }

    float Mat4::operator[](const m7_enum) const {
        return _m7;
    }

    float Mat4::operator[](const m8_enum) const {
        return _m8;
    }

    float Mat4::operator[](const m9_enum) const {
        return _m9;
    }

    float Mat4::operator[](const m10_enum) const {
        return _m10;
    }

    float Mat4::operator[](const m11_enum) const {
        return _m11;
    }

    float Mat4::operator[](const m12_enum) const {
        return _m12;
    }

    float Mat4::operator[](const m13_enum) const {
        return _m13;
    }

    float Mat4::operator[](const m14_enum) const {
        return _m14;
    }

    float Mat4::operator[](const m15_enum) const {
        return _m15;
    }

    // Accessors
    void Mat4::m0(const float v) {
        _m0 = v;
    }

    void Mat4::m1(const float v) {
        _m1 = v;
    }

    void Mat4::m2(const float v) {
        _m2 = v;
    }

    void Mat4::m3(const float v) {
        _m3 = v;
    }

    void Mat4::m4(const float v) {
        _m4 = v;
    }

    void Mat4::m5(const float v) {
        _m5 = v;
    }

    void Mat4::m6(const float v) {
        _m6 = v;
    }

    void Mat4::m7(const float v) {
        _m7 = v;
    }

    void Mat4::m8(const float v) {
        _m8 = v;
    }

    void Mat4::m9(const float v) {
        _m9 = v;
    }

    void Mat4::m10(const float v) {
        _m10 = v;
    }

    void Mat4::m11(const float v) {
        _m11 = v;
    }

    void Mat4::m12(const float v) {
        _m12 = v;
    }

    void Mat4::m13(const float v) {
        _m13 = v;
    }

    void Mat4::m14(const float v) {
        _m14 = v;
    }

    void Mat4::m15(const float v) {
        _m15 = v;
    }


    float Mat4::m0() const {
        return _m0;
    }

    float Mat4::m1() const {
        return _m1;
    }

    float Mat4::m2() const {
        return _m2;
    }

    float Mat4::m3() const {
        return _m3;
    }

    float Mat4::m4() const {
        return _m4;
    }

    float Mat4::m5() const {
        return _m5;
    }

    float Mat4::m6() const {
        return _m6;
    }

    float Mat4::m7() const {
        return _m7;
    }

    float Mat4::m8() const {
        return _m8;
    }

    float Mat4::m9() const {
        return _m9;
    }

    float Mat4::m10() const {
        return _m10;
    }

    float Mat4::m11() const {
        return _m11;
    }

    float Mat4::m12() const {
        return _m12;
    }

    float Mat4::m13() const {
        return _m13;
    }

    float Mat4::m14() const {
        return _m14;
    }

    float Mat4::m15() const {
        return _m15;
    }

    // Determinant
    float Mat4::det() const
    {
        float det_0 = _m0 * (_m5 * (_m10 * _m15 - _m11 * _m14) -
                      _m6 * (_m9 * _m15 - _m11 * _m13) +
                      _m7 * (_m9 * _m14 - _m10 * _m13));

        float det_1 = -_m1 * (_m4 * (_m10 * _m15 - _m11 * _m14) -
                       _m6 * (_m8 * _m15 - _m11 * _m12) +
                       _m7 * (_m8 * _m14 - _m10 * _m12));

        float det_2 = _m2 * (_m4 * (_m9 * _m15 - _m11 * _m13) -
                      _m5 * (_m8 * _m15 - _m11 * _m12) +
                      _m7 * (_m8 * _m13 - _m9 * _m12));

        float det_3 = -_m3 * (_m4 * (_m9 * _m14 - _m10 * _m13) -
                       _m5 * (_m8 * _m14 - _m10 * _m12) +
                       _m6 * (_m8 * _m13 - _m9 * _m12));

        return det_0 + det_1 + det_2 + det_3;
    }

    // Transpose
    Mat4& Mat4::T(void)
    {
        Swap(_m1, _m4);
        Swap(_m2, _m8);
        Swap(_m3, _m12);
        Swap(_m6, _m9);
        Swap(_m7, _m13);
        Swap(_m11, _m14);

        return *this;
    }

    Mat4 Mat4::getT(void) const
    {
        Mat4 temp(*this);
        temp.T();

        return temp;
    }

    // Inverse 
    Mat4 Mat4::getInv(void) const
    {
        float det = this->det();
        assert(!Util::isZero(det, 0.0f));

        float invDet = 1.0f / det;
        Mat4 inv;

        inv._m0 = (_m5 * (_m10 * _m15 - _m11 * _m14) -
                   _m6 * (_m9 * _m15 - _m11 * _m13) +
                   _m7 * (_m9 * _m14 - _m10 * _m13)) * invDet;

        inv._m1 = (-_m1 * (_m10 * _m15 - _m11 * _m14) +
                   _m2 * (_m9 * _m15 - _m11 * _m13) -
                   _m3 * (_m9 * _m14 - _m10 * _m13)) * invDet;

        inv._m2 = (_m1 * (_m6 * _m15 - _m7 * _m14) -
                   _m2 * (_m5 * _m15 - _m7 * _m13) +
                   _m3 * (_m5 * _m14 - _m6 * _m13)) * invDet;

        inv._m3 = (-_m1 * (_m6 * _m11 - _m7 * _m10) +
                   _m2 * (_m5 * _m11 - _m7 * _m9) -
                   _m3 * (_m5 * _m10 - _m6 * _m9)) * invDet;

        inv._m4 = (-_m4 * (_m10 * _m15 - _m11 * _m14) +
                   _m6 * (_m8 * _m15 - _m11 * _m12) -
                   _m7 * (_m8 * _m14 - _m10 * _m12)) * invDet;

        inv._m5 = (_m0 * (_m10 * _m15 - _m11 * _m14) -
                   _m2 * (_m8 * _m15 - _m11 * _m12) +
                   _m3 * (_m8 * _m14 - _m10 * _m12)) * invDet;

        inv._m6 = (-_m0 * (_m6 * _m15 - _m7 * _m14) +
                   _m2 * (_m4 * _m15 - _m7 * _m12) -
                   _m3 * (_m4 * _m14 - _m6 * _m12)) * invDet;

        inv._m7 = (_m0 * (_m6 * _m11 - _m7 * _m10) -
                   _m2 * (_m4 * _m11 - _m7 * _m8) +
                   _m3 * (_m4 * _m10 - _m6 * _m8)) * invDet;

        inv._m8 = (_m4 * (_m9 * _m15 - _m11 * _m13) -
                   _m5 * (_m8 * _m15 - _m11 * _m12) +
                   _m7 * (_m8 * _m13 - _m9 * _m12)) * invDet;

        inv._m9 = (-_m0 * (_m9 * _m15 - _m11 * _m13) +
                   _m1 * (_m8 * _m15 - _m11 * _m12) -
                   _m3 * (_m8 * _m13 - _m9 * _m12)) * invDet;

        inv._m10 = (_m0 * (_m5 * _m15 - _m7 * _m13) -
                    _m1 * (_m4 * _m15 - _m7 * _m12) +
                    _m3 * (_m4 * _m13 - _m5 * _m12)) * invDet;

        inv._m11 = (-_m0 * (_m5 * _m11 - _m7 * _m9) +
                    _m1 * (_m4 * _m11 - _m7 * _m8) -
                    _m3 * (_m4 * _m9 - _m5 * _m8)) * invDet;

        inv._m12 = (-_m4 * (_m9 * _m14 - _m10 * _m13) +
                    _m5 * (_m8 * _m14 - _m10 * _m12) -
                    _m6 * (_m8 * _m13 - _m9 * _m12)) * invDet;

        inv._m13 = (_m0 * (_m9 * _m14 - _m10 * _m13) -
                    _m1 * (_m8 * _m14 - _m10 * _m12) +
                    _m2 * (_m8 * _m13 - _m9 * _m12)) * invDet;

        inv._m14 = (-_m0 * (_m5 * _m14 - _m6 * _m13) +
                    _m1 * (_m4 * _m14 - _m6 * _m12) -
                    _m2 * (_m4 * _m13 - _m5 * _m12)) * invDet;

        inv._m15 = (_m0 * (_m5 * _m10 - _m6 * _m9) -
                    _m1 * (_m4 * _m10 - _m6 * _m8) +
                    _m2 * (_m4 * _m9 - _m5 * _m8)) * invDet;

        return inv;
    
    }

    Mat4 &Mat4::inv(void)
    {
        *this = getInv();

        return *this;
    }

    bool Mat4::isEqual(const Mat4 &A, const float epsilon) const
    {
        for (int i = 0; i < 16; i++)
        {
            float a = ((const float*)this)[i];
            float b = ((const float*)&A)[i];

            if (!Util::isEqual(a, b, epsilon)) {

                return false;
            }     
        }

        return true;
    }

    bool Mat4::isIdentity(const float epsilon) const
    {
        return Util::isEqual(_m0, 1.0f, epsilon) &&
               Util::isEqual(_m1, 0.0f, epsilon) &&
               Util::isEqual(_m2, 0.0f, epsilon) &&
               Util::isEqual(_m3, 0.0f, epsilon) &&
               Util::isEqual(_m4, 0.0f, epsilon) &&
               Util::isEqual(_m5, 1.0f, epsilon) &&
               Util::isEqual(_m6, 0.0f, epsilon) &&
               Util::isEqual(_m7, 0.0f, epsilon) &&
               Util::isEqual(_m8, 0.0f, epsilon) &&
               Util::isEqual(_m9, 0.0f, epsilon) &&
               Util::isEqual(_m10, 1.0f, epsilon) &&
               Util::isEqual(_m11, 0.0f, epsilon) &&
               Util::isEqual(_m12, 0.0f, epsilon) &&
               Util::isEqual(_m13, 0.0f, epsilon) &&
               Util::isEqual(_m14, 0.0f, epsilon) &&
               Util::isEqual(_m15, 1.0f, epsilon);
    }

    bool Mat4::isRotation(const float epsilon) const
    {
        Mat4 rotationMatrix = (*this) * this->getT();

        return rotationMatrix.isIdentity(epsilon);
    }

    // Addition Operators
    Mat4 Mat4::operator + (void) const
    {
        return *this;
    }

    Mat4 Mat4::operator + (const Mat4 &A) const
    {
        Mat4 result;

        for (int i = 0; i < 16; i++)
        {
            ((float*)&result)[i] = ((const float*)this)[i] + ((const float*)&A)[i];
        }

        return result;
    }

    Mat4 &Mat4::operator += (const Mat4 &A)
    {
        *this = *this + A;

        return *this;
    }

    // Subtraction Operators
    Mat4 Mat4::operator - (void) const
    {
        Mat4 result;

        for (int i = 0; i < 16; i++)
        {
            ((float*)&result)[i] = -((const float*)this)[i];
        }

        return result;
    }


    Mat4 Mat4::operator - (const Mat4 &A) const
    {
        Mat4 result;

        for (int i = 0; i < 16; i++)
        {
            ((float*)&result)[i] = ((const float*)this)[i] - ((const float*)&A)[i];
        }

        return result;
    }

    Mat4 &Mat4::operator -= (const Mat4 &A)
    {
        *this = *this - A;

        return *this;
    }

    // Scale 
    Mat4 Mat4::operator * (const float s) const
    {
        Mat4 result;

        for (int i = 0; i < 16; i++)
        {
            ((float*)&result)[i] = ((const float*)this)[i] * s;
        }

        return result;
    }

    Mat4 operator * (const float scale, const Mat4 &A)
    {
        return A * scale;
    }

    Mat4 &Mat4::operator *= (const float scale)
    {
        *this = *this * scale;

        return *this;
    }

    // Matrix Mult
    Mat4 Mat4::operator * (const Mat4 &A) const
    {
        Mat4 result(Identity);

        for (int row = 0; row < 4; row++)
        {
            for (int col = 0; col < 4; col++)
            {
                float sum = 0.0f;
                for (int k = 0; k < 4; k++)
                {
                    sum += ((const float*)this)[row * 4 + k] * ((const float*)&A)[k * 4 + col];
                }
                ((float*)&result)[row * 4 + col] = sum;
            }
        }

        return result;
    }

    Mat4 &Mat4::operator *= (const Mat4 &A)
    {
        *this = *this * A;

        return *this;
    }

    // Print.
    void Mat4::Print(const char *pName) const
    {
        Trace::out("%s:\n", pName);

        for (int row = 0; row < 4; row++)
        {
            Trace::out("| %f %f %f %f |\n", ((const float*)this)[row * 4 + 0],
                                            ((const float*)this)[row * 4 + 1],
                                            ((const float*)this)[row * 4 + 2],
                                            ((const float*)this)[row * 4 + 3]);
        }
    }

}

// ---  End of File ---



