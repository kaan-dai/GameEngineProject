//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "MathEngine.h"

namespace Azul
{
    // Constructor
    Rot::Rot()
    {
        this->set(Identity);
    }

    // Constructor Identity
    Rot::Rot(const enum Identity_enum)
    {
        this->set(Identity);
    }

    // Constructor on Rot1
    Rot::Rot(const Rot1 type, const float angle)
    {
        this->set(Identity);

        float c = Trig::cos(angle);
        float s = Trig::sin(angle);

        switch (type)
        {
        case Rot1::X:
            this->_m5 = c;  this->_m6 = s;
            this->_m9 = -s;  this->_m10 = c;

            break;

        case Rot1::Y:
            this->_m0 = c;  this->_m2 = -s;
            this->_m8 = s; this->_m10 = c;

            break;

        case Rot1::Z:
            this->_m0 = c;  this->_m1 = s;
            this->_m4 = -s;  this->_m5 = c;

            break;

        default:
            assert(false);
            break;
        }
    }

     // Constructor Rotation Three Angles In Order.
    Rot::Rot(const Rot3 mode, const float angle_0, const float angle_1, const float angle_2)
    {
        Rot rx(Rot1::X, angle_0);
        Rot ry(Rot1::Y, angle_1);
        Rot rz(Rot1::Z, angle_2);

        switch (mode)
        {
            case Rot3::XYZ:
            {
                Mat4 temp = rx * ry * rz;
                this->Mat4::set(temp);

                break;
            }

            case Rot3::XZY:
            {
                Mat4 temp = rx * rz * ry;
                this->Mat4::set(temp);

                break;
            }

            case Rot3::YXZ:
            {
                Mat4 temp = ry * rx * rz;
                this->Mat4::set(temp);

                break;
            }

            case Rot3::YZX:
            {
                Mat4 temp = ry * rz * rx;
                this->Mat4::set(temp);

                break;
            }

            case Rot3::ZXY:
            {
                Mat4 temp = rz * rx * ry;
                this->Mat4::set(temp);

                break;
            }

            case Rot3::ZYX:
            {
                Mat4 temp = rz * ry * rx;
                this->Mat4::set(temp);

                break;
            }

            default:
            {
                this->set(Identity);

                break;
            }
        }
    }

    // Constructor Rotation Arbitrary Axis
    Rot::Rot(const Axis mode, const Vec3 &vAxis, const float angle_radians)
    {
        const float angle_a = 0.5f * angle_radians;
        float cos_a;
        float sin_a;

        Trig::cossin(cos_a, sin_a, angle_a);

        Vec3 vV = vAxis.getNorm();

        vV *= sin_a;

        Vec4 V;
        V[x] = vV[x];
        V[y] = vV[y];
        V[z] = vV[z];
        V[w] = cos_a;

        // this function has been transposed
        float x2, y2, z2;
        float xx, xy, xz;
        float yy, yz, zz;
        float wx, wy, wz;

        // ADD test to make sure that quat is normalized

        x2 = V[x] + V[x];
        y2 = V[y] + V[y];
        z2 = V[z] + V[z];

        xx = V[x] * x2;
        xy = V[x] * y2;
        xz = V[x] * z2;

        yy = V[y] * y2;
        yz = V[y] * z2;
        zz = V[z] * z2;

        wx = V[w] * x2;
        wy = V[w] * y2;
        wz = V[w] * z2;

        this->_m0 = 1.0f - (yy + zz);
        this->_m1 = xy + wz;
        this->_m2 = xz - wy;
        this->_m3 = 0.0f;

        this->_m4 = xy - wz;
        this->_m5 = 1.0f - (xx + zz);
        this->_m6 = yz + wx;
        this->_m7 = 0.0f;

        this->_m8 = xz + wy;
        this->_m9 = yz - wx;
        this->_m10 = 1.0f - (xx + yy);
        this->_m11 = 0.0f;

        this->_v3.set(0.0f, 0.0f, 0.0f, 1.0f);
    }
    

	// Constructor With DOF and Up Vect
    Rot::Rot(const Orient type, const Vec3 &dof, const Vec3 &up)
    {
        Vec3 forward = dof.getNorm();
        Vec3 right = up.cross(forward).getNorm();

        Vec3 newUp = forward.cross(right);

        if(type == Orient::LocalToWorld)
        {
            this->_m0  = right.x();   this->_m1  = right.y();   this->_m2  = right.z();   this->_m3  = 0.0f;
            this->_m4  = newUp.x();   this->_m5  = newUp.y();   this->_m6  = newUp.z();   this->_m7  = 0.0f;
            this->_m8  = forward.x(); this->_m9  = forward.y(); this->_m10 = forward.z(); this->_m11 = 0.0f;
        }
        else // WorldToLocal (Transpose)
        {
            this->_m0  = right.x();   this->_m1  = newUp.x();   this->_m2  = forward.x(); this->_m3  = 0.0f;
            this->_m4  = right.y();   this->_m5  = newUp.y();   this->_m6  = forward.y(); this->_m7  = 0.0f;
            this->_m8  = right.z();   this->_m9  = newUp.z();   this->_m10 = forward.z(); this->_m11 = 0.0f;
        }

		this->_m12 = 0.0f; this->_m13 = 0.0f; this->_m14 = 0.0f; this->_m15 = 1.0f; //Fourth row with (0,0,0,1)
    }

    // Set
    void Rot::set(const enum Identity_enum)
    {
        this->Mat4::set(Identity);
    }

    void Rot::set(const Rot& r)
    {
        *this = r;
    }

    void Rot::set(const Rot1 type, const float angle)
    {
        *this = Rot(type, angle);
    }

    void Rot::set(const Rot3 mode, const float angle_0, const float angle_1, const float angle_2)
    {
        *this = Rot(mode, angle_0, angle_1, angle_2);
    }

    void Rot::set(const Axis mode, const Vec3& vAxis, const float angle_radians)
    {
        *this = Rot(mode, vAxis, angle_radians);
    }

    void Rot::set(const Orient type, const Vec3& dof, const Vec3& up)
    {
        *this = Rot(type, dof, up);
    }

}

// ---  End of File ---
