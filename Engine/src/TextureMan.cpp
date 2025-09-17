#include "TextureMan.h"
#include "DLinkMan.h"

namespace Azul
{
	TextureMan *TextureMan::posInstance = nullptr;

	TextureMan::TextureMan(int reserveNum, int reserveGrow)
		: ManBase(new DLinkMan(), new DLinkMan(), reserveNum, reserveGrow)
	{
		this->proFillReservedPool(reserveNum);
		this->poTextureCompare = new TextureObject();
		assert(this->poTextureCompare != nullptr);
	}

	TextureMan::~TextureMan()
	{
		delete this->poTextureCompare;
		this->poTextureCompare = nullptr;

		Iterator *pIt = this->baseGetActiveIterator();

		DLink *pNode = pIt->First();

		while (!pIt->IsDone())
		{
			TextureObject *pDeleteMe = (TextureObject*)pIt->Curr();
			pNode = pIt->Next();
			delete pDeleteMe;
		}
	}

	void TextureMan::Create(int reserveNum, int reserveGrow)
	{
		assert(reserveNum >= 0);
		assert(reserveGrow > 0);

		assert(posInstance == nullptr);

		if (posInstance == nullptr)
		{
			posInstance = new TextureMan(reserveNum, reserveGrow);
		}
	}

	void TextureMan::Destroy()
	{
		TextureMan *pMan = TextureMan::privGetInstance();
		assert(pMan != nullptr);
		AZUL_UNUSED_VAR(pMan);

		delete TextureMan::posInstance;
		TextureMan::posInstance = nullptr;
	}

	TextureObject *TextureMan::Add(TextureObject::Name name, TextureObject *pTexture)
	{
		TextureMan *pMan = TextureMan::privGetInstance();

		assert(pTexture);

		TextureObject *pNode = (TextureObject*)pMan->baseAddToFront();
		assert(pNode != nullptr);

		pNode->name = name;
		pNode->poTextureRV = pTexture->poTextureRV;
		pNode->poSampler = pTexture->poSampler;

		pTexture->poTextureRV = nullptr;
		pTexture->poSampler = nullptr;

		delete pTexture;

		return pNode;
	}

	TextureObject *TextureMan::Find(TextureObject::Name _name)
	{
		TextureMan *pMan = TextureMan::privGetInstance();
		assert(pMan != nullptr);

		pMan->poTextureCompare->name = _name;

		TextureObject *pData = (TextureObject*)pMan->baseFind(pMan->poTextureCompare);

		return pData;
	}

	void TextureMan::Remove(TextureObject *pTexture)
	{
		assert(pTexture != nullptr);

		TextureMan *pMan = TextureMan::privGetInstance();
		assert(pMan != nullptr);

		pMan->baseRemove(pTexture);
	}

	void TextureMan::Dump()
	{
		TextureMan *pMan = TextureMan::privGetInstance();
		assert(pMan != nullptr);

		pMan->baseDump();
	}

	TextureMan *TextureMan::privGetInstance()
	{
		assert(posInstance != nullptr);

		return posInstance;
	}

	DLink *TextureMan::derivedCreateNode()
	{
		DLink *pNodeBase = new TextureObject();
		assert(pNodeBase != nullptr);

		return pNodeBase;
	}
}

// --- End of File ---