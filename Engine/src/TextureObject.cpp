//--------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include <Windows.h>
#include <string>
#include <d3d11.h>

#include "TextureObject.h"
#include "Engine.h"
#include "StringThis.h"
#include "StateDirectXMan.h"

#include "DirectXTex.h"

namespace Azul
{

	TextureObject::TextureObject()
		: DLink(),
		name(TextureObject::Name::Uninitialized),
		poTextureRV(nullptr),
		poSampler(nullptr)
	{

	}

	TextureObject::~TextureObject()
	{
		this->privClear();
	}

	TextureObject::TextureObject(TextureObject::Name _name,
								 LPCWSTR filepath,
								 D3D11_FILTER filter)
		: DLink(),
		name(_name),
		poTextureRV(nullptr),
		poSampler(nullptr)
	{
		DirectX::ScratchImage testTexture;
		HRESULT hr = LoadFromTGAFile(filepath, nullptr, testTexture);
		assert(SUCCEEDED(hr));

		CreateShaderResourceView(StateDirectXMan::GetDevice(),
								 testTexture.GetImage(0, 0, 0),
								 testTexture.GetImageCount(),
								 testTexture.GetMetadata(),
								 &poTextureRV);
		assert(this->poTextureRV);

		// Create the sample state
		D3D11_SAMPLER_DESC sampDesc;
		ZeroMemory(&sampDesc, sizeof(sampDesc));
		sampDesc.Filter = filter;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
		hr = StateDirectXMan::GetDevice()->CreateSamplerState(&sampDesc, &poSampler);
		assert(SUCCEEDED(hr));
		assert(this->poSampler);
	}

	void TextureObject::ActivateTexture()
	{
		StateDirectXMan::GetContext()->PSSetShaderResources((uint32_t) ShaderResourceBufferSlot::TexA, 1, &poTextureRV);
		StateDirectXMan::GetContext()->PSSetSamplers((uint32_t) ShaderSamplerSlot::SampleA, 1, &poSampler);
	}

	void TextureObject::SetName(TextureObject::Name _name)
	{
		this->name = _name;
	}

	void TextureObject::Set(TextureObject::Name _name, TextureObject* pSourceTexture)
	{
		assert(pSourceTexture);
		this->privClear();

		this->name = _name;
		this->poTextureRV = pSourceTexture->poTextureRV;
		this->poSampler = pSourceTexture->poSampler;

		pSourceTexture->poTextureRV = nullptr;
		pSourceTexture->poSampler = nullptr;
		pSourceTexture->name = TextureObject::Name::Uninitialized;
	}


	char *TextureObject::GetName()
	{
		// todo - Hack understand why is this needed for print and fix...
		static char pTmp[128];
		strcpy_s(pTmp, 128, StringMe(this->name));
		return pTmp;
	}

	void TextureObject::privClear()
	{
		SafeRelease(poTextureRV);
		SafeRelease(poSampler);
	}

	void TextureObject::Wash()
	{
		this->privClear();
	}

	bool TextureObject::Compare(DLink *pTargetNode)
	{
		assert(pTargetNode);

		TextureObject *pDataB = (TextureObject*)pTargetNode;

		bool status = false;

		if (this->name == pDataB->name)
		{
			status = true;
		}

		return status;
	}

	void TextureObject::Dump()
	{
		Trace::out("TextureObject(%p)\n", this);
		Trace::out("Name: %s \n", StringMe(this->name));
		

		DLink::Dump();
	}
}


// --- End of File ---