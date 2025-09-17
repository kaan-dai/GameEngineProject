//--------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include "ShaderObject_Null.h"
#include "Mesh.h"
#include "ShaderMappings.h"
#include "ShaderMappings.h"

// User generated headers... 
#include "Null.Px.h"
#include "Null.Vx.h"

namespace Azul
{

	D3D11_INPUT_ELEMENT_DESC ShaderObject_NullDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, (uint32_t) VertexSlot::Position, offsetof(VertexPos,Position), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR"   , 0, DXGI_FORMAT_R32G32B32_FLOAT, (uint32_t) VertexSlot::Color, offsetof(VertexColor,Color),  D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	ShaderObject_Null::~ShaderObject_Null()
	{

	}

	ShaderObject_Null::ShaderObject_Null(ShaderObject_Null::Name _name)
		: ShaderObject(_name),
		VertexShader { sizeof(g_Null_VxShader), (void *) g_Null_VxShader },
		PixelShader { sizeof(g_Null_PxShader), (void *) g_Null_PxShader },
		InputLayout { sizeof(g_Null_VxShader),(void *) g_Null_VxShader, ShaderObject_NullDesc,sizeof(ShaderObject_NullDesc) }

	{
	}

	void ShaderObject_Null::ActivateShader()
	{
		this->VertexShader.SetActive();
		this->PixelShader.SetActive();
	}

	void ShaderObject_Null::ActivateCBV()
	{
	}

	void ShaderObject_Null::TransferWorldViewProj(Camera *pCam, Mat4 *pWorld)
	{
		assert(pCam);
		assert(pWorld);
		AZUL_UNUSED_VAR(pCam);
		AZUL_UNUSED_VAR(pWorld);
	}

}

// --- End of File ---
