#include "MeshD.h"
#include "MathEngine.h"
#include "StateDirectXMan.h"
#include "ShaderMappings.h"

namespace Azul
{
	MeshD::MeshD()
		: Mesh(0, 0),
		VBVBuffer_pos(),
		VBVBuffer_norm(),
		VBVBuffer_tex(),
		IBVBuffer()
	{
		VBVBuffer_pos.Initialize("D_POSITION_Center.cdm", sizeof(VertexPos));
		VBVBuffer_norm.Initialize("D_NORMAL.cdm", sizeof(VertexNorm));
		VBVBuffer_tex.Initialize("D_TEXCOORD_0.cdm", sizeof(VertexTexCoord));
		IBVBuffer.Initialize("D_INDICES.cdm");

		this->numVerts = CalculateVertexCount();
		this->numIndices = CalculateIndexCount();
	}

	MeshD::~MeshD()
	{
	}

	void MeshD::ActivateMesh()
	{
		// ---------------------------------------------
		//    Set (point to ) vertex: position 
		//    Set (point to ) vertex: color
		//    Set (point to ) vertex: norm
		//    Set (point to ) vertex: texCoord
		// ---------------------------------------------
		this->VBVBuffer_pos.SetActive(VertexSlot::Position);
		this->VBVBuffer_norm.SetActive(VertexSlot::Norm);
		this->VBVBuffer_tex.SetActive(VertexSlot::TexCoord);
	}

	void MeshD::RenderIndexBuffer()
	{
		// ---------------------------------------------
		//    Set (point to ) Index buffer 
		//    Render configuration: Triangles
		// ---------------------------------------------
		this->IBVBuffer.SetActive();
		StateDirectXMan::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//--------------------------------------------------------
		// RENDER - using index data
		//--------------------------------------------------------
		StateDirectXMan::GetContext()->DrawIndexed(numIndices, 0, 0);
	}

	uint32_t MeshD::CalculateVertexCount()
	{
		return VBVBuffer_pos.numBytes / sizeof(VertexPos);
	}

	uint32_t MeshD::CalculateIndexCount()
	{
		return IBVBuffer.numBytes / sizeof(uint32_t);
	}

}

// --- End of File ---
