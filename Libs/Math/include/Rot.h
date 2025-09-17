//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_ROT_4x4_H
#define ENGINE_MATH_ROT_4x4_H

#include "Math_DLLInterface.h"

#include "Mat4.h"

namespace Azul
{
	class Rot final : public Mat4
	{
	public:

		// Do your magic here

		// Big 4
		MATH_LIBRARY_API Rot();
		MATH_LIBRARY_API Rot &operator = (const Rot &) = default;
		MATH_LIBRARY_API Rot(const Rot &) = default;
		MATH_LIBRARY_API ~Rot() = default;

		// Big 6
		MATH_LIBRARY_API Rot(Rot &&) = default;
		MATH_LIBRARY_API Rot &operator = (Rot &&) = default;

		explicit MATH_LIBRARY_API Rot(const enum Identity_enum);
		MATH_LIBRARY_API Rot(const Rot1 type, const float angle);
		MATH_LIBRARY_API Rot(const Rot3 mode, const float angle_0, const float angle_1, const float angle_2);
		MATH_LIBRARY_API Rot(const Axis mode, const Vec3 &vAxis, const float angle_radians);
		MATH_LIBRARY_API Rot(const Orient, const Vec3 &dof, const Vec3 &up);

		MATH_LIBRARY_API void set(const enum Identity_enum);
		MATH_LIBRARY_API void set(const Rot &);
		MATH_LIBRARY_API void set(const Rot1 type, const float angle);
		MATH_LIBRARY_API void set(const Rot3 mode, const float angle_0, const float angle_1, const float angle_2);
		MATH_LIBRARY_API void set(const Axis mode, const Vec3 &vAxis, const float angle_radians);
		MATH_LIBRARY_API void set(const Orient, const Vec3 &dof, const Vec3 &up);

	private:
		void privSetRotOrient(const Vec3 &vect_dof, const Vec3 &vect_vup);
		void privSetRotInvOrient(const Vec3 &vect_dof, const Vec3 &vect_vup);

		void privSetRotXYZ(const float a, const float b, const float c);
		void privSetRotXZY(const float a, const float b, const float c);
		void privSetRotYXZ(const float a, const float b, const float c);
		void privSetRotYZX(const float a, const float b, const float c);
		void privSetRotZXY(const float a, const float b, const float c);
		void privSetRotZYX(const float a, const float b, const float c);

	};
}

#endif

//--- End of File ---
