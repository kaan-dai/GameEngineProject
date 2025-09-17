#ifndef MESH_C_H
#define MESH_C_H

#include "Mesh.h"
#include "BufferIBV.h"
#include "BufferVBV.h"

namespace Azul
{
	class MeshC : public Mesh
	{
	public:
		MeshC();
		MeshC(const MeshC&) = delete;
		MeshC& operator = (MeshC&) = delete;
		virtual ~MeshC();

		virtual void ActivateMesh() override;
		virtual void RenderIndexBuffer() override;

		// Data
		BufferVBV VBVBuffer_pos;
		BufferVBV VBVBuffer_color;
		BufferVBV VBVBuffer_norm;
		BufferVBV VBVBuffer_tex;

		BufferIBV IBVBuffer;

	private:
		uint32_t CalculateVertexCount();
		uint32_t CalculateIndexCount();
	};
}

#endif

// --- End of File ---
