//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "BufferVBV.h"
#include "StateDirectXMan.h"

namespace Azul
{
	BufferVBV::BufferVBV()
		: numBytes{ 0 },
		strideSize{ 0 },
		offset{ 0 },
		poBufferVBV{ nullptr },
		bCreate{ false },
		pData{ nullptr }
	{
	}

	BufferVBV::BufferVBV(uint32_t _numBytes, uint32_t _strideSize, void *pData)
		: numBytes { _numBytes },
		strideSize { _strideSize },
		offset { 0 },
		poBufferVBV { nullptr },
		bCreate { false },
		pData{ nullptr }
		
	{
		assert(pData);
		this->privCreate(pData);
	}

	void BufferVBV::privCreate(void *pVertexData)
	{
		// in case set was called before
		assert(this->bCreate == false);
		this->bCreate = true;

		assert(pVertexData);

		// Create an initialize the vertex buffer.
		D3D11_BUFFER_DESC vertexBufferDesc { 0 };
		D3D11_SUBRESOURCE_DATA resourceData { 0 };

		// type of buffer
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.ByteWidth = this->numBytes;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

		resourceData.pSysMem = pVertexData;

		HRESULT hr;
		hr = StateDirectXMan::GetDevice()->CreateBuffer(&vertexBufferDesc, &resourceData, &this->poBufferVBV);

		assert(SUCCEEDED(hr));
		assert(this->poBufferVBV);
	}

	void BufferVBV::SetActive(VertexSlot slot)
	{
		// slow down... check this function 
		StateDirectXMan::GetContext()->IASetVertexBuffers((uint32_t) slot,
														   1,
														   &this->poBufferVBV,
														   &this->strideSize,
														   &this->offset);
	}

	BufferVBV::~BufferVBV()
	{
		SafeRelease(this->poBufferVBV);
		if (this->pData)
		{
			delete[](char*)this->pData;
		}
	}

	void *BufferVBV::LoadBinaryFile(const char *filename, uint32_t &fileSize)
	{
		File::Handle fh;
		File::Error ferror;

		ferror = File::Open(fh, filename, File::Mode::READ);
		assert(ferror == File::Error::SUCCESS);

		ferror = File::Seek(fh, File::Position::END, 0);
		assert(ferror == File::Error::SUCCESS);

		DWORD fileSizeDWORD;
		ferror = File::Tell(fh, fileSizeDWORD);
		assert(ferror == File::Error::SUCCESS);
		fileSize = (uint32_t)fileSizeDWORD;

		ferror = File::Seek(fh, File::Position::BEGIN, 0);
		assert(ferror == File::Error::SUCCESS);

		void *pLoadedData = new char[fileSize];
		ferror = File::Read(fh, pLoadedData, fileSize);
		assert(ferror == File::Error::SUCCESS);

		ferror = File::Close(fh);
		assert(ferror == File::Error::SUCCESS);

		return pLoadedData;
	}

	void BufferVBV::Initialize(const char *filename, uint32_t _strideSize)
	{
		this->pData = LoadBinaryFile(filename, this->numBytes);
		this->strideSize = _strideSize;
		this->offset = 0;
		this->poBufferVBV = nullptr;
		this->bCreate = false;

		this->privCreate(this->pData);
	}
}

//--- End of File ---
