#ifndef MESH_D_H
#define MESH_D_H

#include "Mesh.h"
#include "BufferIBV.h"
#include "BufferVBV.h"

namespace Azul
{
	class MeshD : public Mesh
	{
	public:
		MeshD();
		MeshD(const MeshD&) = delete;
		MeshD& operator = (MeshD&) = delete;
		virtual ~MeshD();

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
