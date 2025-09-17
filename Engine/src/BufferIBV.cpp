//----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "BufferIBV.h"
#include "StateDirectXMan.h"

namespace Azul
{
	BufferIBV::BufferIBV()
		: numBytes{ 0 },
		poBufferIBV{ nullptr },
		bCreate{ false },
		pData{ nullptr }
	{
	}

	BufferIBV::BufferIBV(uint32_t _numBytes, void *pData)
		: numBytes { _numBytes },
		poBufferIBV { nullptr },
		bCreate { false },
		pData{ nullptr }
	{
		assert(pData);
		this->privCreate(pData);
	}

	void BufferIBV::privCreate(void *pIndexData)
	{
		// in case set was called before
		assert(this->bCreate == false);
		this->bCreate = true;

		assert(pIndexData);

		// Create and initialize the index buffer.
		D3D11_BUFFER_DESC indexBufferDesc { 0 };
		D3D11_SUBRESOURCE_DATA resourceData { 0 };

		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.ByteWidth = this->numBytes;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

		resourceData.pSysMem = pIndexData;

		HRESULT hr;
		hr = StateDirectXMan::GetDevice()->CreateBuffer(&indexBufferDesc,
														 &resourceData,
														 &this->poBufferIBV);
		assert(SUCCEEDED(hr));
		assert(this->poBufferIBV);

	}

	void BufferIBV::SetActive()
	{
		// slow down... check this function 
		StateDirectXMan::GetContext()->IASetIndexBuffer(this->poBufferIBV,
														 DXGI_FORMAT_R32_UINT,
														 0);
	}

	BufferIBV::~BufferIBV()
	{
		SafeRelease(this->poBufferIBV);
		if (this->pData)
		{
			delete[](char*)this->pData;
		}

	}

	void* BufferIBV::LoadBinaryFile(const char *filename, uint32_t &fileSize)
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

		void* pLoadedData = new char[fileSize];
		ferror = File::Read(fh, pLoadedData, fileSize);
		assert(ferror == File::Error::SUCCESS);

		ferror = File::Close(fh);
		assert(ferror == File::Error::SUCCESS);

		return pLoadedData;
	}

	void BufferIBV::Initialize(const char *filename)
	{
		this->pData = LoadBinaryFile(filename, this->numBytes);
		this->poBufferIBV = nullptr;
		this->bCreate = false;

		this->privCreate(this->pData);
	}

}

//--- End of File ---
