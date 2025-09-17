//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "PCSTreeForwardIterator.h"

namespace Azul
{
	PCSTreeForwardIterator::PCSTreeForwardIterator(PCSNode *rootNode)
	{
		assert(rootNode != nullptr);
		this->root = rootNode;
		this->current = nullptr;
	}

	PCSNode *PCSTreeForwardIterator::First()
	{
		assert(this->root != nullptr);
		this->current = this->root;

		return this->current;
	}

	PCSNode *PCSTreeForwardIterator::Next()
	{
		assert(this->current != nullptr);
		this->current = this->current->GetForward();

		return this->current;
	}

	bool PCSTreeForwardIterator::IsDone()
	{
		return (this->current == nullptr);
	}

	PCSNode *PCSTreeForwardIterator::Current()
	{
		return this->current;
	}

}

// ---  End of File ---
