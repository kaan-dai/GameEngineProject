//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <d3d11.h>
#include "Game.h"
#include "Engine.h"
#include "MathEngine.h"
#include "Mesh.h"
#include "GraphicsObject_Wireframe.h"
#include "ShaderObject.h"
#include "StateDirectXMan.h"
#include "CameraNodeMan.h"

namespace Azul
{
	extern Game *poGame;

	// ---------------------------------------------
	//  Transfer data to the constant buffer
	//    CPU ---> GPU
	//    World, View, Projection Matrix
	// ---------------------------------------------
	GraphicsObject_Wireframe::GraphicsObject_Wireframe(Mesh *_pMesh, ShaderObject *_pShaderObj)
		: GraphicsObject(_pMesh, _pShaderObj)
	{
		assert(pMesh);
		assert(pShaderObj);
		assert(poWorld);
	}

	void GraphicsObject_Wireframe::SetState()
	{
		poGame->mStateRasterizerWireframe.Activate();
	}

	void GraphicsObject_Wireframe::SetDataGPU()
	{
		pShaderObj->ActivateShader();
		pShaderObj->ActivateCBV();
		pShaderObj->TransferWorldViewProj(CameraNodeMan::GetCurrentCamera(), this->poWorld);
		pMesh->ActivateMesh();
	}

	void GraphicsObject_Wireframe::Draw()
	{
		pMesh->RenderIndexBuffer();
	}

	void GraphicsObject_Wireframe::RestoreState()
	{
		poGame->mStateRasterizerSolid.Activate();
	}

}

// ---  End of File ---
