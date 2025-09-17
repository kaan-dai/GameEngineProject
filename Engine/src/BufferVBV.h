//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef BUFFER_VBV_H
#define BUFFER_VBV_H

#include <d3d11.h>
#include "ShaderMappings.h"
#include "File.h"

namespace Azul
{
	class BufferVBV
	{
	public:
		BufferVBV();
		BufferVBV(const BufferVBV &r) = delete;
		BufferVBV &operator=(const BufferVBV &) = delete;
		virtual ~BufferVBV();

		BufferVBV(uint32_t numBytes, uint32_t _strideSize, void *pVertexData);

		void SetActive(VertexSlot slot);
		void Initialize(const char *filename, uint32_t _strideSize);
	private:
		void privCreate(void * pVertexData);
		void *LoadBinaryFile(const char* filename, uint32_t& fileSize);

		// ----------------------
		//  Data
		// ----------------------
	public:
		uint32_t	 numBytes;
		uint32_t	 strideSize;
		uint32_t	 offset;
		ID3D11Buffer *poBufferVBV;
		bool         bCreate;
		void *pData;
	};
}

#endif

//--- End of File ---
