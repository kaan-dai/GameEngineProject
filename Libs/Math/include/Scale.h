//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_SCALE_4x4_H
#define ENGINE_MATH_SCALE_4x4_H

#include "Math_DLLInterface.h"

#include "Mat4.h"

namespace Azul
{
	class Scale final : public Mat4
	{
	public:

		// Do your magic here

		// Big 4
		MATH_LIBRARY_API Scale();
		MATH_LIBRARY_API Scale &operator = (const Scale &) = default;
		MATH_LIBRARY_API Scale(const Scale &) = default;
		MATH_LIBRARY_API ~Scale() = default;

		// Big 6
		MATH_LIBRARY_API Scale(Scale &&) = default;
		MATH_LIBRARY_API Scale &operator = (Scale &&) = default;

		// Constructors
		MATH_LIBRARY_API Scale(const float sx, const float sy, const float sz);
		MATH_LIBRARY_API Scale(const Vec3 &vScale);
		MATH_LIBRARY_API Scale(const enum Identity_enum);

		// Set 
		MATH_LIBRARY_API void set(const float sx, const float sy, const float sz);
		MATH_LIBRARY_API void set(const Vec3 &vScale);
		MATH_LIBRARY_API void set(const enum Identity_enum);


	};
}

#endif

//--- End of File ---
