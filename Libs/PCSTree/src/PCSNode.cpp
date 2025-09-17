//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "PCSTree.h"
#include "PCSNode.h"

namespace Azul
{
	// constructor
	PCSNode::PCSNode()
	{
		
		this->pParent = nullptr;
		this->pChild = nullptr;
		this->pNextSibling = nullptr;
		this->pPrevSibling = nullptr;
		this->pForward = nullptr;
		this->pReverse = nullptr;

		memset(this->pName, 0, PCSNode::NAME_SIZE);
	}

	// copy constructor
	PCSNode::PCSNode(const PCSNode & in)
	{
		
		this->pParent = in.pParent;
		this->pChild = in.pChild;
		this->pNextSibling = in.pNextSibling;
		this->pPrevSibling = in.pPrevSibling;
		this->pForward = nullptr;
		this->pReverse = nullptr;

		memset(this->pName, 0, PCSNode::NAME_SIZE);
		strncpy_s(this->pName, in.pName, PCSNode::NAME_SIZE - 1);
		this->pName[PCSNode::NAME_SIZE - 1] = '\0';
	}

	// Specialize Constructor
	PCSNode::PCSNode(PCSNode * const pInParent, PCSNode * const pInChild, PCSNode * const pInNextSibling, PCSNode * const pInPrevSibling, const char * const pInName)
	{
		this->pParent = pInParent;
		this->pChild = pInChild;
		this->pNextSibling = pInNextSibling;
		this->pPrevSibling = pInPrevSibling;
		this->pForward = nullptr;
		this->pReverse = nullptr;

		memset(this->pName, 0, PCSNode::NAME_SIZE);
		if (pInName)
		{
			strncpy_s(this->pName, pInName, PCSNode::NAME_SIZE - 1);
			this->pName[PCSNode::NAME_SIZE - 1] = '\0';
		}

	}

	PCSNode::PCSNode(const char * const pInName)
	{
		this->pParent = nullptr;
		this->pChild = nullptr;
		this->pNextSibling = nullptr;
		this->pPrevSibling = nullptr;
		this->pForward = nullptr;
		this->pReverse = nullptr;

		memset(this->pName, 0, PCSNode::NAME_SIZE);
		if (pInName)
		{
			strncpy_s(this->pName, pInName, PCSNode::NAME_SIZE - 1);
			this->pName[PCSNode::NAME_SIZE - 1] = '\0';
		}
	}

	// destructor
	PCSNode::~PCSNode()
	{
	
	}

	// assignment operator
	PCSNode & PCSNode::operator = (const PCSNode & in)
	{
		if (this != &in)
		{
			this->pParent = in.pParent;
			this->pChild = in.pChild;
			this->pNextSibling = in.pNextSibling;
			this->pPrevSibling = in.pPrevSibling;

			memset(this->pName, 0, PCSNode::NAME_SIZE);
			strncpy_s(this->pName, in.pName, PCSNode::NAME_SIZE - 1);
			this->pName[PCSNode::NAME_SIZE - 1] = '\0';
		}
		return *this;
	}

	void PCSNode::SetParent(PCSNode * const pIn)
	{
		this->pParent = pIn;
	}

	void PCSNode::SetChild(PCSNode * const pIn)
	{
		this->pChild = pIn;
	}

	void PCSNode::SetNextSibling(PCSNode * const pIn)
	{
		this->pNextSibling = pIn;
	}

	void PCSNode::SetPrevSibling(PCSNode * const pIn)
	{
		this->pPrevSibling = pIn;
	}

	PCSNode * PCSNode::GetParent(void) const
	{
		return this->pParent;
	}

	PCSNode * PCSNode::GetChild(void) const
	{
		return this->pChild;
	}

	PCSNode * PCSNode::GetNextSibling(void) const
	{
		return this->pNextSibling;
	}

	PCSNode * PCSNode::GetPrevSibling(void) const
	{
		return this->pPrevSibling;
	}

	PCSNode::Code PCSNode::SetName(const char * const pInName)
	{
		if (pInName == nullptr) {

			return Code::FAIL_NULL_PTR;
		}
			
		memset(this->pName, 0, PCSNode::NAME_SIZE);
		strncpy_s(this->pName, pInName, PCSNode::NAME_SIZE - 1);

		this->pName[PCSNode::NAME_SIZE - 1] = '\0';

		return Code::SUCCESS;
	}

	PCSNode::Code PCSNode::GetName(char * const pOutBuffer, unsigned int sizeOutBuffer) const
	{
		if (pOutBuffer == nullptr)
		{
			return Code::FAIL_NULL_PTR;
		}
		memset(pOutBuffer, 0, sizeOutBuffer);

		unsigned int available;
		if (sizeOutBuffer > 0)
		{
			available = sizeOutBuffer - 1;
		}
		else
		{
			available = 0;
		}

		unsigned int srcLen = (unsigned int)strlen(this->pName);
		unsigned int copyLen;

		if (srcLen < available)
		{
			copyLen = srcLen;
		}
		else
		{
			copyLen = available;
		}

		for (unsigned int i = 0; i < copyLen; i++)
		{
			pOutBuffer[i] = this->pName[i];
		}

		pOutBuffer[copyLen] = '\0';

		return Code::SUCCESS;
	}

	void PCSNode::PrintNode() const
	{
		Trace::out("Node Name: %s\n", this->pName);
		Trace::out("Node Address: %p\n", this);

		if (this->pParent)
		{
			Trace::out("Parent: %s (%p)\n", this->pParent->pName, this->pParent);
		}
		else
		{
			Trace::out("Parent: NULL\n");
		}

		if (this->pChild)
		{
			Trace::out("Child: %s (%p)\n", this->pChild->pName, this->pChild);
		}
		else
		{
			Trace::out("Child: NULL\n");
		}

		if (this->pNextSibling)
		{
			Trace::out("Next Sibling: %s (%p)\n", this->pNextSibling->pName, this->pNextSibling);
		}
		else
		{
			Trace::out("Next Sibling: NULL\n");
		}

		if (this->pPrevSibling)
		{
			Trace::out("Prev Sibling: %s (%p)\n\n", this->pPrevSibling->pName, this->pPrevSibling);
		}
		else
		{
			Trace::out("Prev Sibling: NULL\n\n");
		}
	}

	void PCSNode::PrintChildren() const
	{
		PCSNode *child = this->pChild;

		while (child)
		{
			Trace::out("Child: %s (%p)\n", child->pName, child);
			child = child->GetNextSibling();
		}
	}


	void PCSNode::PrintSiblings() const
	{
		const PCSNode *first = this;

		while (first->pPrevSibling) 
		{
			first = first->pPrevSibling;
		}

		const PCSNode *sibling = first;

		while (sibling)
		{
			if (sibling && sibling != this)
			{
				Trace::out("Sibling: %s (%p)\n", sibling->pName, sibling);
			}

			sibling = sibling->pNextSibling;
		}
	}

	int PCSNode::GetNumSiblings() const
	{
		int count = 0;
		const PCSNode *first = this;

		while (first->pPrevSibling) 
		{
			first = first->GetPrevSibling();
		}
		const PCSNode *sibling = first;

		while (sibling)
		{
			count++;
			sibling = sibling->GetNextSibling();
		}

		return count;
	}

	int PCSNode::GetNumChildren() const
	{
		int count = 0;
		const PCSNode *child = this->pChild;
		while (child)
		{
			count++;
			child = child->GetNextSibling();
		}

		return count;
	}

	void PCSNode::SetForward(PCSNode *const pIn)
	{
		this->pForward = pIn;
	}

	void PCSNode::SetReverse(PCSNode *const pIn)
	{
		this->pReverse = pIn;
	}

	PCSNode *PCSNode::GetForward() const
	{
		return this->pForward;
	}

	PCSNode *PCSNode::GetReverse() const
	{
		return this->pReverse;
	}

}

// ---  End of File ---
