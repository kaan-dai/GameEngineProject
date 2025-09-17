//--------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#ifndef SHADER_OBJECT_NULL_H
#define SHADER_OBJECT_NULL_H

#include "ShaderObject.h"
#include "BufferVertexShader.h"
#include "BufferPixelShader.h"
#include "BufferInputLayout.h"

namespace Azul
{
	class ShaderObject_Null : public ShaderObject
	{
	public:

	public:
		ShaderObject_Null() = delete;
		ShaderObject_Null(const ShaderObject_Null &) = delete;
		ShaderObject_Null &operator = (const ShaderObject_Null &) = delete;
		virtual ~ShaderObject_Null();

		ShaderObject_Null(ShaderObject_Null::Name _name);

		virtual void ActivateShader() override;
		virtual void ActivateCBV() override;
		virtual void TransferWorldViewProj(Camera *pCam, Mat4 *pWorld) override;

		// ---------------------------------------------
		// 	   Data:
		// ---------------------------------------------

		BufferVertexShader VertexShader;
		BufferPixelShader  PixelShader;
		BufferInputLayout  InputLayout;
	};
}

#endif

// --- End of File ---
