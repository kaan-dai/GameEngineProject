//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "MathEngine.h"
#include "GameObject.h"
#include "Game.h"
#include "Camera.h"

namespace Azul
{

	GameObject::GameObject(GraphicsObject *pGraphicsObject)
		: poPos { new Vec3(0,0,0) },
		poGraphicsObject(pGraphicsObject),
		scale(1.0f)
	{
		assert(pGraphicsObject);
		assert(poPos);

		this->poWorld = new Mat4(Identity);
		assert(this->poWorld);
	}

	void GameObject::SetScale(float v)
	{
		this->scale = v;
	}

	GameObject::~GameObject()
	{
		delete this->poPos;
		delete this->poGraphicsObject;
		delete this->poWorld;
	}

	Mat4 *GameObject::GetWorld()
	{
		return this->poWorld;
	}

	void GameObject::SetPos(Vec3 v)
	{
		poPos->set(v);
	}

	void GameObject::Update()
	{

		Trans TransA(poPos->x(), poPos->y(), poPos->z());
		Scale ScaleA(scale, scale, scale);

		*this->poWorld = ScaleA * TransA;

		// PUSH to Graphics object
		this->poGraphicsObject->SetWorld(*this->poWorld);
	}

	void GameObject::SetWorld(Mat4 *world)
	{
		assert(world);
		*this->poWorld = *world;
	}

	void GameObject::Draw()
	{
		// ---------------------------------------------
		//  Transfer data to the constant buffer
		//    CPU ---> GPU
		//    World, View, Projection Matrix
		//    Set Shader
		//    Render
		// ---------------------------------------------
		this->poGraphicsObject->Render();

	}

}

// --- End of File ---
