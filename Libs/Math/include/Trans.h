//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_TRANS_4x4_H
#define ENGINE_MATH_TRANS_4x4_H

#include "Math_DLLInterface.h"

#include "Mat4.h"

namespace Azul
{
	class Trans final : public Mat4
	{
	public:

		// Do your magic here

		// Big 4
		MATH_LIBRARY_API Trans();
		MATH_LIBRARY_API Trans &operator = (const Trans &) = default;
		MATH_LIBRARY_API Trans(const Trans &) = default;
		MATH_LIBRARY_API ~Trans() = default;

		// Big 6
		MATH_LIBRARY_API Trans(Trans &&) = default;
		MATH_LIBRARY_API Trans &operator = (Trans &&) = default;

		// Constructors
		MATH_LIBRARY_API Trans(const float tx, const float ty, const float tz);
		MATH_LIBRARY_API Trans(const Vec3 &vTrans);
		MATH_LIBRARY_API Trans(const enum Identity_enum);

		// Set 
		MATH_LIBRARY_API void set(const float tx, const float ty, const float tz);
		MATH_LIBRARY_API void set(const Vec3 &vTrans);
		MATH_LIBRARY_API void set(const enum Identity_enum);

	};
}

#endif

//--- End of File ---
