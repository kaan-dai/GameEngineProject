#ifndef MESH_B_H
#define MESH_B_H

#include "Mesh.h"
#include "BufferIBV.h"
#include "BufferVBV.h"

namespace Azul
{
	class MeshB : public Mesh
	{
	public:
		MeshB();
		MeshB(const MeshB&) = delete;
		MeshB& operator = (MeshB&) = delete;
		virtual ~MeshB();

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
