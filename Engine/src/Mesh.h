//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef MESH_H
#define MESH_H

#include <d3d11.h>
#include "DLink.h"
#include "MathEngine.h"
#include "Camera.h"
#include "BufferCBV_vs.h"

namespace Azul
{

	// Quick Hack
	struct Vec2f
	{
		Vec2f()
			: u(0.0f), v(0.0f)
		{
		}
		Vec2f(const Vec2f &) = default;
		Vec2f &operator = (const Vec2f &) = default;
		~Vec2f() = default;

		Vec2f(const float _u, const float _v)
			: u(_u), v(_v)
		{
		}

		float u;
		float v;
	};

	struct Vec3f
	{
		Vec3f()
			: x(0.0f), y(0.0f), z(0.0f)
		{
		}
		Vec3f(const Vec3f &) = default;
		Vec3f &operator = (const Vec3f &) = default;
		~Vec3f() = default;

		Vec3f(const float a, const float b, const float c)
			: x(a), y(b), z(c)
		{
		}

		float x;
		float y;
		float z;
	};

	// Vertex data for a colored cube.
	struct VertexColor
	{
		Vec3f Color;
	};

	struct VertexPos
	{
		Vec3f Position;
	};

	struct VertexNorm
	{
		Vec3f Norm;
	};

	struct VertexTexCoord
	{
		Vec2f TexCoord;
	};


	class Mesh
	{
	public:
		enum class Name
		{
			CUBE,
			PYRAMID,
			A,
			B,
			C,
			D,
			E,
			NULL_MESH,
			NOT_INITIALIZED
		};

	public:
		Mesh() = delete;
		Mesh(Mesh &) = delete;
		Mesh &operator = (Mesh &) = delete;
		virtual ~Mesh();

		Mesh(unsigned int numVerts, unsigned int numTriangles);

		void Wash();
		bool Compare(DLink *pTarget);
		char *GetName();
		void SetName(Mesh::Name _name);

		virtual void ActivateMesh() = 0;
		virtual void RenderIndexBuffer() = 0;

		// ---------------------------------------------
		// 	   Data:
		// ---------------------------------------------

		Name name;

		unsigned int numVerts;
		unsigned int numIndices;

	};
}

#endif

// --- End of File ---
