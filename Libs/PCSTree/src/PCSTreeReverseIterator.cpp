//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "PCSTreeReverseIterator.h"

namespace Azul
{
	PCSTreeReverseIterator::PCSTreeReverseIterator(PCSNode *rootNode)
	{
		assert(rootNode != nullptr);
		this->root = rootNode;
		this->current = nullptr;
		this->prevNode = nullptr;
	}

	PCSNode *PCSTreeReverseIterator::First()
	{
		assert(this->root != nullptr);
		this->current = this->root;
		this->prevNode = nullptr;

		while (this->current->GetForward() != nullptr)
		{
			this->current = this->current->GetForward();
		}

		return this->current;
	}

	PCSNode *PCSTreeReverseIterator::Next()
	{
		assert(this->current != nullptr);
		this->prevNode = this->current;
		this->current = this->prevNode->GetReverse();

		return this->current;
	}

	bool PCSTreeReverseIterator::IsDone()
	{
		return (this->current == nullptr);
	}

	PCSNode *PCSTreeReverseIterator::Current()
	{
		return this->current;
	}

}

// ---  End of File ---
