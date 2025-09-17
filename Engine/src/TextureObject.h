//--------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#ifndef TEXTURE_OBJECT_H
#define TEXTURE_OBJECT_H

#include <d3d11.h>
#include "DLink.h"

namespace Azul
{
	class TextureObject : public DLink
	{
	public:
		enum class Name
		{
			NullTexture,
			A,
			B,
			C,
			D,
			E,
			Uninitialized
		};

	public:
		TextureObject();
		TextureObject(const TextureObject &) = delete;
		TextureObject &operator = (const TextureObject &) = delete;
		virtual ~TextureObject();

		TextureObject(TextureObject::Name _name,
					  LPCWSTR filepath,
					  D3D11_FILTER filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR);

		void ActivateTexture();

		char *GetName();
		void SetName(TextureObject::Name _name);
		virtual void Wash() override;
		virtual bool Compare(DLink *pTargetNode) override;
		virtual void Dump() override;
		void Set(TextureObject::Name _name, TextureObject *pSourceTexture);

		// ---------------------------------------------
		// 	   Data:
		// ---------------------------------------------
		TextureObject::Name name;

		ID3D11ShaderResourceView *poTextureRV;
		ID3D11SamplerState *poSampler;

	private:
		void privClear();
	};

}

#endif

// --- End of File ---
