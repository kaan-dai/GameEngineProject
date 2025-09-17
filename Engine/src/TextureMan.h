#ifndef TEXTURE_MAN_H
#define TEXTURE_MAN_H 

#include "ManBase.h"
#include "TextureObject.h"

namespace Azul
{
	class TextureMan : public ManBase
	{

	public:
		static void Create(int reserveNum = 0, int reserveGrow = 1);
		static void Destroy();

		static TextureObject *Add(TextureObject::Name name, TextureObject *pTexture);
		static TextureObject *Find(TextureObject::Name name);

		static void Remove(TextureObject *pTexture);
		static void Dump();

	private:

		static TextureMan *privGetInstance();

		~TextureMan();
		TextureMan(int reserveNum, int reserveGrow);

	protected:

		DLink *derivedCreateNode() override;

	// ------------Data------------	
	private:

		TextureObject *poTextureCompare;
		static TextureMan *posInstance;
	};
}

#endif

// --- End of File ---