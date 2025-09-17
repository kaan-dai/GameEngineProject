//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "PCSTree.h"
#include "PCSNode.h"

namespace Azul
{
	void PCSTree::ForwardReverseLinks()
	{
		PCSNode *pPrev = nullptr;
		PCSNode *pNode = this->pRoot;

		while (pNode != nullptr)
		{
			if (pPrev)
			{
				pPrev->SetForward(pNode);
				pNode->SetReverse(pPrev);
			}
			else
			{
				pNode->SetReverse(nullptr);
			}
			pPrev = pNode;

			if (pNode->GetChild() != nullptr)
			{
				pNode = pNode->GetChild();
			}
			else if (pNode->GetNextSibling() != nullptr)
			{
				pNode = pNode->GetNextSibling();
			}
			else
			{
				PCSNode *upNode = pNode->GetParent();

				while (upNode != nullptr && upNode->GetNextSibling() == nullptr)
				{
					upNode = upNode->GetParent();
				}
				if (upNode != nullptr)
				{
					pNode = upNode->GetNextSibling();
				}
				else
				{
					pNode = nullptr;
				}
			}
		}

		if (pPrev)
		{
			pPrev->SetForward(nullptr);
		}
	}

	int PCSTree::RemoveSubtree(PCSNode *root)
	{
		if (root == nullptr) 
		{
			return 0;
		}
			
		PCSNode *parent = root->GetParent();
		if (parent != nullptr)
		{
			if (parent->GetChild() == root)
			{
				parent->SetChild(root->GetNextSibling());
			}
			if (root->GetPrevSibling()) 
			{
				root->GetPrevSibling()->SetNextSibling(root->GetNextSibling());
			}
			if (root->GetNextSibling())
			{
				root->GetNextSibling()->SetPrevSibling(root->GetPrevSibling());
			}
		}

		root->SetParent(nullptr);
		root->SetPrevSibling(nullptr);
		root->SetNextSibling(nullptr);

		int count = 0;
		PCSNode *head = nullptr;

		root->SetPrevSibling(head);
		head = root;

		while (head)
		{
			PCSNode *curr = head;
			head = curr->GetPrevSibling();
			PCSNode *child = curr->GetChild();

			while (child)
			{
				PCSNode *nextChild = child->GetNextSibling();
				child->SetPrevSibling(head);
				head = child;
				child = nextChild;
			}

			count++;

			curr->SetParent(nullptr);
			curr->SetChild(nullptr);
			curr->SetNextSibling(nullptr);
			curr->SetPrevSibling(nullptr);
		}

		return count;
	}

	int PCSTree::CountNodes(PCSNode *root)
	{
		if (root == nullptr)
		{
			return 0;
		}
		
		int count = 0;
		PCSNode *curr = root;

		while (curr)
		{
			count++;
			PCSNode *child = curr->GetChild();

			if (child)
			{
				curr = child;
			}
			else
			{
				PCSNode *upNode = curr;

				while (upNode && !upNode->GetNextSibling())
				{
					upNode = upNode->GetParent();
				}
				
				if (upNode)
				{
					curr = upNode->GetNextSibling();
				}
				else
				{
					curr = nullptr;
				}
			}
		}
		return count;
	}

	int PCSTree::ComputeDepth(PCSNode *root)
	{
		if (root == nullptr)
		{
			return 0;
		}
		
		int maxDepth = 0;
		PCSNode *curr = root;

		while (curr)
		{
			int depth = 1;
			PCSNode *parent = curr->GetParent();

			while (parent)
			{
				depth++;
				parent = parent->GetParent();
			}
			if (depth > maxDepth)
			{
				maxDepth = depth;
			}
			
			PCSNode *child = curr->GetChild();

			if (child)
			{
				curr = child;
			}
			else
			{
				PCSNode *nextNode = curr;

				while (nextNode && !nextNode->GetNextSibling())
				{
					nextNode = nextNode->GetParent();
				}

				if (nextNode)
				{
					curr = nextNode->GetNextSibling();
				}
				else
				{
					curr = nullptr;
				}
			}
		}
		return maxDepth;
	}

	// constructor
	PCSTree::PCSTree()
	{

        this->pRoot = nullptr;

		this->mInfo.currNumNodes = 0;
		this->mInfo.maxNumNodes = 0;
		this->mInfo.currNumLevels = 0;
		this->mInfo.maxNumLevels = 0;

	};

	// destructor
	PCSTree::~PCSTree()
	{
		if (this->pRoot)
		{
			this->pRoot = nullptr;
			this->mInfo.currNumNodes = 0;
			this->mInfo.maxNumNodes = 0;
			this->mInfo.currNumLevels = 0;
			this->mInfo.maxNumLevels = 0;
		}
	};


	// get Root
	PCSNode * PCSTree::GetRoot() const
	{
		return this->pRoot;
	}


	// insert
	void PCSTree::Insert(PCSNode * const pInNode, PCSNode * const pParent)
	{
		if (pInNode == nullptr) {

			return;
		}

		if (pParent == nullptr)
		{
			pInNode->SetParent(nullptr);
			pInNode->SetNextSibling(nullptr);
			pInNode->SetPrevSibling(nullptr);
			pInNode->SetChild(nullptr);
			this->pRoot = pInNode;
		}

		else
		{
			pInNode->SetParent(pParent);
			PCSNode *currentChild = pParent->GetChild();
			pInNode->SetNextSibling(currentChild);

			if (currentChild != nullptr)
			{
				currentChild->SetPrevSibling(pInNode);
			}

			pParent->SetChild(pInNode);
			pInNode->SetPrevSibling(nullptr);
		}

		ForwardReverseLinks();

		if (this->pRoot)
		{
			this->mInfo.currNumNodes = CountNodes(this->pRoot);
			this->mInfo.currNumLevels = ComputeDepth(this->pRoot);
		}

		else
		{
			this->mInfo.currNumNodes = 0;
			this->mInfo.currNumLevels = 0;
		}

		if (this->mInfo.currNumNodes > this->mInfo.maxNumNodes) {
			this->mInfo.maxNumNodes = this->mInfo.currNumNodes;
		}

		if (this->mInfo.currNumLevels > this->mInfo.maxNumLevels) {
			this->mInfo.maxNumLevels = this->mInfo.currNumLevels;
		}
	}


	// Remove
	void PCSTree::Remove(PCSNode * const pInNode)
	{
		if (pInNode == nullptr) {

			return;
		}

		if (pInNode == this->pRoot)
		{
			RemoveSubtree(this->pRoot);
			this->pRoot = nullptr;
			this->mInfo.currNumNodes = 0;
			this->mInfo.currNumLevels = 0;
		}

		else
		{
			PCSNode *parent = pInNode->GetParent();
			if (parent)
			{
				if (parent->GetChild() == pInNode)
				{
					parent->SetChild(pInNode->GetNextSibling());
				}

				else
				{
					if (pInNode->GetPrevSibling()) {
						pInNode->GetPrevSibling()->SetNextSibling(pInNode->GetNextSibling());
					}
						
				}
				if (pInNode->GetNextSibling() != nullptr) {
					pInNode->GetNextSibling()->SetPrevSibling(pInNode->GetPrevSibling());
				}
			}

			RemoveSubtree(pInNode);
			ForwardReverseLinks();
			if (this->pRoot)
			{
				this->mInfo.currNumNodes = CountNodes(this->pRoot);
				this->mInfo.currNumLevels = ComputeDepth(this->pRoot);
			}

			else
			{
				this->mInfo.currNumNodes = 0;
				this->mInfo.currNumLevels = 0;
			}
		}
	}

	// get tree info
	void PCSTree::GetInfo(Info &info)
	{
		info.currNumNodes = this->mInfo.currNumNodes;
		info.maxNumNodes = this->mInfo.maxNumNodes;
		info.currNumLevels = this->mInfo.currNumLevels;
		info.maxNumLevels = this->mInfo.maxNumLevels;

	}

	void PCSTree::Print() const
	{
		if (!this->pRoot)
		{
			Trace::out("Tree is empty.\n");
			return;
		}

		PCSNode *curr = this->pRoot;
		while (curr)
		{
			char nameBuffer[PCSNode::NAME_SIZE];
			curr->GetName(nameBuffer, PCSNode::NAME_SIZE);

			Trace::out("Name: %s\n", nameBuffer);
			Trace::out("Address: %p\n", curr);

			PCSNode *parent = curr->GetParent();
			if (parent)
			{
				char parentName[PCSNode::NAME_SIZE];
				parent->GetName(parentName, PCSNode::NAME_SIZE);
				Trace::out("Parent: %s (%p)\n", parentName, parent);
			}
			else
			{
				Trace::out("Parent: NULL\n", parent);
			}

			PCSNode *child = curr->GetChild();
			if (child)
			{
				char childName[PCSNode::NAME_SIZE];
				child->GetName(childName, PCSNode::NAME_SIZE);
				Trace::out("Child: %s (%p)\n", childName, child);
			}
			else
			{
				Trace::out("Child: NULL\n", child);
			}

			PCSNode *nextSibling = curr->GetNextSibling();
			if (nextSibling)
			{
				char nextSiblingName[PCSNode::NAME_SIZE];
				nextSibling->GetName(nextSiblingName, PCSNode::NAME_SIZE);
				Trace::out("nextSibling: %s (%p)\n", nextSiblingName, nextSibling);
			}
			else
			{
				Trace::out("nextSibling: NULL\n", nextSibling);
			}

			PCSNode *prevSibling = curr->GetPrevSibling();
			if (prevSibling)
			{
				char prevSiblingName[PCSNode::NAME_SIZE];
				prevSibling->GetName(prevSiblingName, PCSNode::NAME_SIZE);
				Trace::out("prevSibling: %s (%p)\n", prevSiblingName, prevSibling);
			}
			else
			{
				Trace::out("prevSibling: NULL\n");
			}

			Trace::out("\n");

			if (child)
			{
				curr = child;
			}
			else
			{
				PCSNode *nextNode = curr;
				while (nextNode && !nextNode->GetNextSibling())
				{
					nextNode = nextNode->GetParent();
				}

				if (nextNode)
				{
					curr = nextNode->GetNextSibling();
				}
				else
				{
					curr = nullptr;
				}
			}
		}
	}

}

// ---  End of File ---
