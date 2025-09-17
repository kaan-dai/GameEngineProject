//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#ifndef ENGINE_MATH_UTIL_H
#define ENGINE_MATH_UTIL_H

#include "Math_DLLInterface.h"

namespace Azul
{
	class Util
	{
	public:
		MATH_LIBRARY_API static bool isEqual(const float a, const float b, const float epsilon);
		MATH_LIBRARY_API static bool isNotEqual(const float a, const float b, const float epsilon);
		MATH_LIBRARY_API static bool isOne(const float a, const float epsilon);
		MATH_LIBRARY_API static bool isNonZero(const float a, const float epsilon);
		MATH_LIBRARY_API static bool isZero(const float a, const float epsilon);
	};
}

#endif

//--- End of File ---
