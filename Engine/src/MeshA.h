#ifndef MESH_A_H
#define MESH_A_H

#include "Mesh.h"
#include "BufferIBV.h"
#include "BufferVBV.h"

namespace Azul
{
	class MeshA : public Mesh
	{
	public:
		MeshA();
		MeshA(const MeshA&) = delete;
		MeshA& operator = (MeshA&) = delete;
		virtual ~MeshA();

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
