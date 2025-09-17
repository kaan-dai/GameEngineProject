//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <d3d11.h>
#include "MathEngine.h"
#include "Mesh.h"
#include "GraphicsObject_FlatTexture.h"
#include "CameraNodeMan.h"

namespace Azul
{
	// ---------------------------------------------
	//  Transfer data to the constant buffer
	//    CPU ---> GPU
	//    World, View, Projection Matrix
	// ---------------------------------------------
	GraphicsObject_FlatTexture::GraphicsObject_FlatTexture(Mesh *mesh,
														   ShaderObject *pShaderObj,
														   TextureObject *_pTex)
		: GraphicsObject(mesh, pShaderObj),
		pTex(_pTex)
	{
		assert(pTex);
	}

	void GraphicsObject_FlatTexture::SetState()
	{
		// Future - settings to directX
		// set texture
		this->pTex->ActivateTexture();
	}

	void GraphicsObject_FlatTexture::SetDataGPU()
	{
		pShaderObj->ActivateShader();
		pShaderObj->ActivateCBV();
		pShaderObj->TransferWorldViewProj(CameraNodeMan::GetCurrentCamera(), this->poWorld);
		pMesh->ActivateMesh();
	}

	void GraphicsObject_FlatTexture::Draw()
	{
		pMesh->RenderIndexBuffer();
	}

	void GraphicsObject_FlatTexture::RestoreState()
	{
		// Future - Undo settings to directX
	}

}

// --- End of File ---
