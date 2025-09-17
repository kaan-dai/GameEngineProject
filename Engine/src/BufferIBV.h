//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef BUFFER_IBV_H
#define BUFFER_IBV_H

#include <d3d11.h>
#include "ShaderMappings.h"
#include "File.h"

namespace Azul
{
	class BufferIBV
	{
	public:
		BufferIBV();
		BufferIBV(const BufferIBV &r) = delete;
		BufferIBV &operator=(const BufferIBV &) = delete;
		virtual ~BufferIBV();

		BufferIBV(uint32_t numBytes, void *pIndexData);

		void SetActive();
		void Initialize(const char *filename);

	private:
		void privCreate(void *pIndexData);
		void *LoadBinaryFile(const char *filename, uint32_t &fileSize);


		// ----------------------
		//  Data
		// ----------------------
	public:
		uint32_t     numBytes;
		ID3D11Buffer *poBufferIBV;
		bool         bCreate;
		void *pData;
	};
}

#endif

//--- End of File ---
