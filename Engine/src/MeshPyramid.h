//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef MESH_PYRAMID_H
#define MESH_PYRAMID_H

#include "Mesh.h"
#include "BufferIBV.h"
#include "BufferVBV.h"

namespace Azul
{

	class MeshPyramid : public Mesh
	{
	public:
		MeshPyramid();
		MeshPyramid(const MeshPyramid &) = delete;
		MeshPyramid &operator = (MeshPyramid &) = delete;
		virtual ~MeshPyramid();

		virtual void ActivateMesh() override;
		virtual void RenderIndexBuffer() override;

		// Data
		BufferVBV VBVBuffer_pos;
		BufferVBV VBVBuffer_color;
		BufferVBV VBVBuffer_tex;
		BufferVBV VBVBuffer_norm;

		BufferIBV IBVBuffer;
	};

}

#endif

// --- End of File ---
