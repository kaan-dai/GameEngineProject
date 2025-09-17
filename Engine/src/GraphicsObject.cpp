//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "GraphicsObject.h"
#include "MathEngine.h"
#include "Mesh.h"

using namespace Azul;

GraphicsObject::GraphicsObject(Mesh *_pMesh, ShaderObject *_pShaderObj)
	: pMesh(_pMesh),
	pShaderObj(_pShaderObj)
{
	this->poWorld = new Mat4(Identity);
	assert(_pMesh);
	assert(_pShaderObj);
}

GraphicsObject::~GraphicsObject()
{
	delete this->poWorld;
}

void GraphicsObject::Render()
{
	this->SetState();
	this->SetDataGPU();
	this->Draw();
	this->RestoreState();
}

Mesh *GraphicsObject::GetMesh() const
{
	return this->pMesh;
}

Mat4 &GraphicsObject::GetWorld()
{
	return *this->poWorld;
}

void GraphicsObject::SetWorld(Mat4 &_world)
{
	*this->poWorld = _world;
}

// --- End of File ---
