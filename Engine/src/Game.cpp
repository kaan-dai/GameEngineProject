//--------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include <d3d11.h>
#include <d3dcompiler.h>

#include "Game.h"
#include "Engine.h"
#include "MathEngine.h"
#include "Camera.h"
#include "CameraNodeMan.h"
#include "CameraNode.h"
#include "CameraUtility.h"
#include "Colors.h"
#include "GameObject.h"
#include "GameObject_Pulsing.h"
#include "GameObject_Rotating.h"
#include "GameObject_RotatingPulsing.h"
#include "ShaderObject.h"
#include "ShaderObject_ColorByVertex.h"
#include "ShaderObject_FlatTexture.h"
#include "ShaderObject_LightTexture.h"
#include "ShaderObject_ConstColor.h"
#include "Mesh.h"
#include "MeshA.h"
#include "MeshB.h"
#include "MeshC.h"
#include "MeshD.h"
#include "MeshE.h"
#include "MeshCube.h"
#include "MeshPyramid.h"
#include "GraphicsObject_ColorByVertex.h"
#include "GraphicsObject_Wireframe.h"
#include "GraphicsObject_FlatTexture.h"
#include "GraphicsObject_LightTexture.h"
#include "GraphicsObject_ConstColor.h"
#include "GameObjectMan.h"
#include "MeshNodeMan.h"
#include "ShaderObjectNodeMan.h"
#include "StateDirectXMan.h"
#include "TextureObject.h"
#include "TextureMan.h"

namespace Azul
{

	Game *poGame;

	// Demo
	Vec3 Orig_up;
	Vec3 Orig_tar;
	Vec3 Orig_pos;
	Vec3 Orig_upNorm;
	Vec3 Orig_forwardNorm;
	Vec3 Orig_RightNorm;


	Game::Game(const char *const pName, int width, int height)
		: Engine(pName, width, height)
	{
		poGame = this;
	}

	Game::~Game()
	{
	}

	//-----------------------------------------------------------------------------
	// Game::LoadContent()
	//		Allows you to load all content needed for your engine,
	//	    such as objects, graphics, etc.
	//-----------------------------------------------------------------------------
	bool Game::LoadContent()
	{
		ShaderObjectNodeMan::Create();
		MeshNodeMan::Create();
		GameObjectMan::Create();
		CameraNodeMan::Create();
		TextureMan::Create();

		// ---------------------------------
		//  Camera - Setup
		// ---------------------------------
		{
			Camera *pMainCamera = new Camera();
			assert(pMainCamera);

			Vec3 mainUp(0, 1, 0);
			Vec3 mainPos(0, 0, 1);
			Vec3 mainTar(0, 0, 0);

			pMainCamera->SetHelper(mainUp, mainTar, mainPos);
			pMainCamera->setPerspective(50.0f, GetAspectRatio(), 0.1f, 1000.0f);


			Camera *pBehindCamera = new Camera();
			assert(pBehindCamera);

			Vec3 upVect(0, 1, 0);
			Vec3 camPosVect(0, 0, -2);
			Vec3 tarVect(0, 0, 0);

			pBehindCamera->SetHelper(upVect, tarVect, camPosVect);
			pBehindCamera->setPerspective(50.0f, GetAspectRatio(), 0.1f, 1000.0f);

			CameraUtility::Create(pBehindCamera);


			Camera *pFirstPersonCamera = new Camera();
			assert(pFirstPersonCamera);

			Vec3 fpUp(0, 1, 0);
			Vec3 fpPos(0, 0, 2);
			Vec3 fpTar(0, 0, 0);
			
			pFirstPersonCamera->SetHelper(fpUp, fpTar, fpPos);
			pFirstPersonCamera->setPerspective(50.0f, GetAspectRatio(), 0.1f, 1000.0f);

			Camera *pTopDownCamera = new Camera();
			assert(pTopDownCamera);

			Vec3 tdUp(0, 0, -1);
			Vec3 tdPos(0, 2, 0);
			Vec3 tdTar(0, 0, 0);

			pTopDownCamera->SetHelper(tdUp, tdTar, tdPos);
			pTopDownCamera->setPerspective(50.0f, GetAspectRatio(), 0.1f, 1000.0f);

			Camera *pSideViewCamera = new Camera();
			assert(pSideViewCamera);

			Vec3 svUp(0, 1, 0);
			Vec3 svPos(2, 0, 0);
			Vec3 svTar(0, 0, 0);

			pSideViewCamera->SetHelper(svUp, svTar, svPos);
			pSideViewCamera->setPerspective(50.0f, GetAspectRatio(), 0.1f, 1000.0f);


			CameraNodeMan::Add(CameraNode::Name::MAIN_CAMERA, pMainCamera);
			CameraNodeMan::Add(CameraNode::Name::SIDE_VIEW_CAMERA, pSideViewCamera);
			CameraNodeMan::Add(CameraNode::Name::BEHIND_CAMERA, pBehindCamera);
			CameraNodeMan::Add(CameraNode::Name::TOP_DOWN_CAMERA, pTopDownCamera);
			CameraNodeMan::Add(CameraNode::Name::FIRST_PERSON_CAMERA, pFirstPersonCamera);

			CameraNodeMan::SetCurrentCamera(CameraNode::Name::MAIN_CAMERA);
		}

		// ------------------------------------------
		//   Model + Shaders --> GraphicsObject
		// -------------------------------------------
		{
			// ---------------------------------
			//  Model - Cube
			// ---------------------------------
			Mesh *poMeshCube = new MeshCube();
			MeshNodeMan::Add(Mesh::Name::CUBE, poMeshCube);

			Mesh *poMeshPyramid = new MeshPyramid();
			MeshNodeMan::Add(Mesh::Name::PYRAMID, poMeshPyramid);

			Mesh *poMeshA = new MeshA();
			MeshNodeMan::Add(Mesh::Name::A, poMeshA);

			Mesh *poMeshB = new MeshB();
			MeshNodeMan::Add(Mesh::Name::B, poMeshB);

			Mesh *poMeshC = new MeshC();
			MeshNodeMan::Add(Mesh::Name::C, poMeshC);

			Mesh *poMeshD = new MeshD();
			MeshNodeMan::Add(Mesh::Name::D, poMeshD);

			Mesh* poMeshE = new MeshE();
			MeshNodeMan::Add(Mesh::Name::E, poMeshE);


			MeshNodeMan::Dump();

			// --------------------------------
			//  ShaderObject  ColorByVertex
			// --------------------------------
			ShaderObject *poShaderColorVertex = new ShaderObject_ColorByVertex(ShaderObject::Name::ColorByVertex);
			ShaderObjectNodeMan::Add(poShaderColorVertex);

			ShaderObject *poShaderFlatTex= new ShaderObject_FlatTexture(ShaderObject::Name::FlatTexture);
			ShaderObjectNodeMan::Add(poShaderFlatTex);

			ShaderObject *poShaderLightTex = new ShaderObject_LightTexture(ShaderObject::Name::LightTexture);
			ShaderObjectNodeMan::Add(poShaderLightTex);

			ShaderObject *poShaderConstColor = new ShaderObject_ConstColor(ShaderObject::Name::ConstColor);
			ShaderObjectNodeMan::Add(poShaderConstColor);

			ShaderObjectNodeMan::Dump();

			// -----------------------------------
			//  Texture
			// -----------------------------------

			TextureObject *pTexA = new TextureObject(TextureObject::Name::A, L"A.tga");
			pTexA = TextureMan::Add(TextureObject::Name::A, pTexA);

			TextureObject *pTexB = new TextureObject(TextureObject::Name::B, L"B.tga");
			pTexB = TextureMan::Add(TextureObject::Name::B, pTexB);

			TextureObject *pTexC = new TextureObject(TextureObject::Name::C, L"C.tga");
			pTexC = TextureMan::Add(TextureObject::Name::C, pTexC);

			TextureObject *pTexD = new TextureObject(TextureObject::Name::D, L"D.tga");
			pTexD = TextureMan::Add(TextureObject::Name::D, pTexD);

			TextureObject *pTexE = new TextureObject(TextureObject::Name::E, L"E.tga");
			pTexE = TextureMan::Add(TextureObject::Name::E, pTexE);

			TextureMan::Dump();

			// --------------------------------
			//  Graphics Object -- needs model + shader
			// --------------------------------
			Vec3 LightColor(1, 1, 1);
			Vec3 LightPos(50, 50, 100);

			//Object A
			{  
				LightColor *= 1.2f;
				GraphicsObject *pGraphicsObject = new GraphicsObject_LightTexture(poMeshA,
																				  poShaderLightTex,
																				  pTexA,
																				  LightColor,
																				  LightPos);
				GameObject *pGameObj = new GameObject_Pulsing(pGraphicsObject);
				pGameObj->SetName("A Light Texture");
				pGameObj->SetScale(1.0f);
				pGameObj->SetPos(Vec3(-0.5f, 0.35f, 0));

				GameObjectMan::Add(pGameObj);
			}

			{ 

				GraphicsObject *pGraphicsObject = new GraphicsObject_FlatTexture(poMeshA, poShaderFlatTex, pTexA);
				GameObject *pGameObj = new GameObject_RotatingPulsing(pGraphicsObject);
				pGameObj->SetName("A Flat Texture");
				pGameObj->SetPos(Vec3(-0.5f, -0.35f, 0));

				GameObjectMan::Add(pGameObj);
			}

			{  

				Vec3 color(0, 0, 1);
				GraphicsObject *pGraphicsObject = new GraphicsObject_ConstColor(poMeshA, poShaderConstColor, color);
				GameObject *pGameObj = new GameObject_Rotating(pGraphicsObject);
				pGameObj->SetName("A WireFrame");
				pGameObj->SetPos(Vec3(-0.5f, 0, 0));

				GameObjectMan::Add(pGameObj);
			}

			//Object B
			{  
				Vec3 LightColorB(1, 0, 0);
				LightColorB *= 1.2f;
				GraphicsObject *pGraphicsObject = new GraphicsObject_LightTexture(poMeshB,
																				  poShaderLightTex,
																				  pTexB,
																				  LightColorB,
																				  LightPos);
				GameObject *pGameObj = new GameObject_Pulsing(pGraphicsObject, 0.5f, 1.0f, 0.1f);
				pGameObj->SetName("B Light Texture");
				pGameObj->SetPos(Vec3(-0.25f, 0.35f, 0));

				GameObjectMan::Add(pGameObj);
			}

			{

				GraphicsObject *pGraphicsObject = new GraphicsObject_FlatTexture(poMeshB, poShaderFlatTex, pTexB);
				GameObject *pGameObj = new GameObject_RotatingPulsing(pGraphicsObject, Rot1::X, 0.075f, 0.5f, 1.0f, 0.1f);
				pGameObj->SetName("B Flat Texture");
				pGameObj->SetPos(Vec3(-0.25f, -0.35f, 0));

				GameObjectMan::Add(pGameObj);
			}

			{

				Vec3 color(0, 1, 1);
				GraphicsObject *pGraphicsObject = new GraphicsObject_ConstColor(poMeshB, poShaderConstColor, color);
				GameObject* pGameObj = new GameObject_Rotating(pGraphicsObject, Rot1::X , 0.075f);
				pGameObj->SetName("B WireFrame");
				pGameObj->SetPos(Vec3(-0.25f, 0, 0));

				GameObjectMan::Add(pGameObj);
			}

			//Object C
			{ 
				Vec3 LightColorC(0, 1, 0);
				LightColorC *= 1.2f;
				GraphicsObject *pGraphicsObject = new GraphicsObject_LightTexture(poMeshC,
																				  poShaderLightTex,
																				  pTexC,
																				  LightColorC,
																				  LightPos);
				GameObject *pGameObj = new GameObject_Pulsing(pGraphicsObject, 0.1f, 1.2f);
				pGameObj->SetName("C Light Texture");
				pGameObj->SetPos(Vec3(0, 0.35f, 0));

				GameObjectMan::Add(pGameObj);
			}

			{

				GraphicsObject *pGraphicsObject = new GraphicsObject_FlatTexture(poMeshC, poShaderFlatTex, pTexC);
				GameObject *pGameObj = new GameObject_RotatingPulsing(pGraphicsObject, Rot1::Y, 0.05f, 0.1f, 1.2f);
				pGameObj->SetName("C Flat Texture");
				pGameObj->SetPos(Vec3(0, -0.35f, 0));

				GameObjectMan::Add(pGameObj);
			}

			{

				Vec3 color(0, 1, 0);
				GraphicsObject *pGraphicsObject = new GraphicsObject_ConstColor(poMeshC, poShaderConstColor, color);
				GameObject* pGameObj = new GameObject_Rotating(pGraphicsObject, Rot1::Y , 0.05f);
				pGameObj->SetName("C WireFrame");
				pGameObj->SetPos(Vec3(0, 0, 0));

				GameObjectMan::Add(pGameObj);
			}

			//Object D
			{ 
				Vec3 LightColorD(0, 0, 1);
				LightColorD *= 1.2f;
				GraphicsObject *pGraphicsObject = new GraphicsObject_LightTexture(poMeshD,
																				  poShaderLightTex,
																				  pTexD,
																			      LightColorD,
																				  LightPos);
				GameObject *pGameObj = new GameObject_Pulsing(pGraphicsObject, 0.1f, 2.0f, 0.02f);
				pGameObj->SetName("D Light Texture");
				pGameObj->SetScale(1.0f);
				pGameObj->SetPos(Vec3(0.25f, 0.35f, 0));

				GameObjectMan::Add(pGameObj);
			}

			{

				GraphicsObject *pGraphicsObject = new GraphicsObject_FlatTexture(poMeshD, poShaderFlatTex, pTexD);
				GameObject *pGameObj = new GameObject_RotatingPulsing(pGraphicsObject, Rot1::Z, -0.025f, 0.1f, 2.0f, 0.02f);
				pGameObj->SetName("D Flat Texture");
				pGameObj->SetPos(Vec3(0.25f, -0.35f, 0));

				GameObjectMan::Add(pGameObj);
			}

			{

				Vec3 color(1, 1, 0);
				GraphicsObject *pGraphicsObject = new GraphicsObject_ConstColor(poMeshD, poShaderConstColor, color);
				GameObject *pGameObj = new GameObject_Rotating(pGraphicsObject, Rot1::Z, -0.025f);
				pGameObj->SetName("D WireFrame");
				pGameObj->SetPos(Vec3(0.25f, 0, 0));

				GameObjectMan::Add(pGameObj);
			}

			//Object E
			{ 
				Vec3 LightColorE(1, 1, 1);
				LightColorE *= 1.2f;
				GraphicsObject *pGraphicsObject = new GraphicsObject_LightTexture(poMeshE,
																				  poShaderLightTex,
																				  pTexE,
																				  LightColorE,
																				  LightPos);
				GameObject *pGameObj = new GameObject_Pulsing(pGraphicsObject, 0.3f, 1.3f, 0.2f);
				pGameObj->SetName("E Light Texture");
				pGameObj->SetScale(1.0f);
				pGameObj->SetPos(Vec3(0.5f, 0.35f, 0));

				GameObjectMan::Add(pGameObj);
			}

			{

				GraphicsObject *pGraphicsObject = new GraphicsObject_FlatTexture(poMeshE, poShaderFlatTex, pTexE);
				GameObject *pGameObj = new GameObject_RotatingPulsing(pGraphicsObject, Rot1::X, -0.1f, 0.3f, 1.3f, 0.2f);
				pGameObj->SetName("E Flat Texture");
				pGameObj->SetPos(Vec3(0.5f, -0.35f, 0));

				GameObjectMan::Add(pGameObj);
			}

			{

				Vec3 color(1, 0, 0);
				GraphicsObject *pGraphicsObject = new GraphicsObject_ConstColor(poMeshE, poShaderConstColor, color);
				GameObject *pGameObj = new GameObject_Rotating(pGraphicsObject, Rot1::X, -0.1f);
				pGameObj->SetName("E WireFrame");
				pGameObj->SetPos(Vec3(0.5f, 0, 0));

				GameObjectMan::Add(pGameObj);
			}
		}

		return true;
	}

	//-----------------------------------------------------------------------------
	// Game::Update()
	//      Called once per frame, update data, tranformations, etc
	//      Use this function to control process order
	//      Input, AI, Physics, Animation, and Graphics
	//-----------------------------------------------------------------------------
	void Game::Update(float)
	{
		// ------------------------------------
		// Update the camera once per frame
		// ------------------------------------
		CameraNodeMan::UpdateCurrentCamera();

		// ------------------------------------
		// Update objects
		// ------------------------------------

		GameObjectMan::Update();
	}

	//-----------------------------------------------------------------------------
	// Game::Render()
	//		This function is called once per frame
	//	    Use this for draw graphics to the screen.
	//      Only do rendering here
	//-----------------------------------------------------------------------------
	void Game::Render()
	{
		this->SetDefaultTargetMode();

		GameObjectMan::Draw();
	}

	//-----------------------------------------------------------------------------
	// Game::UnLoadContent()
	//       unload content (resources loaded above)
	//       unload all content that was loaded before the Engine Loop started
	//-----------------------------------------------------------------------------
	void Game::UnloadContent()
	{
		
		TextureMan::Destroy();
		CameraUtility::Destroy();
		CameraNodeMan::Destroy();
		GameObjectMan::Destroy();
		MeshNodeMan::Destroy();
		ShaderObjectNodeMan::Destroy();


	}

	//------------------------------------------------------------------
	// Game::ClearBufferFunc()
	// Allows user to change the way the clear buffer function works
	// 
	// Clear the color and depth buffers.
	//------------------------------------------------------------------
	void Game::ClearDepthStencilBuffer()
	{
#ifdef _DEBUG
		const Vec4 ClearColor = Azul::Colors::LightGray;
#else
		const Vec4 ClearColor = Azul::Colors::Wheat;
#endif
		float clearDepth = 1.0f;
		uint8_t clearStencil = 0;
		this->mStateRenderTargetView.Clear(ClearColor);
		this->mDepthStencilView.Clear(clearDepth, clearStencil);
	}



}

// --- End of File ---
