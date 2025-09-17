#ifndef MESH_E_H
#define MESH_E_H

#include "Mesh.h"
#include "BufferIBV.h"
#include "BufferVBV.h"

namespace Azul
{
	class MeshE : public Mesh
	{
	public:
		MeshE();
		MeshE(const MeshE&) = delete;
		MeshE& operator = (MeshE&) = delete;
		virtual ~MeshE();

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
