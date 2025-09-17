//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef PCSTREE_H
#define PCSTREE_H

#include "PCSTree_DLLInterface.h"

namespace Azul
{

	// forward declare
	class PCSNode;

	// PCSTree class 
	class PCSTree
	{
	public:
		// Simple data structure
		struct Info
		{
			int currNumNodes;
			int maxNumNodes;
			int currNumLevels;
			int maxNumLevels;
		};

	public:
		// constructor
		PCSTREE_LIBRARY_API PCSTree();

		// copy constructor 
		PCSTREE_LIBRARY_API PCSTree(const PCSTree &in) = delete;

		// assignment operator
		PCSTREE_LIBRARY_API PCSTree &operator = (const PCSTree &in) = delete;

		// destructor
		PCSTREE_LIBRARY_API ~PCSTree();

		// get Root
		PCSTREE_LIBRARY_API PCSNode *GetRoot() const;

		// insert
		PCSTREE_LIBRARY_API void Insert(PCSNode *const pInNode, PCSNode *const pParent);

		// remove
		PCSTREE_LIBRARY_API void Remove(PCSNode *const pInNode);

		// get info
		PCSTREE_LIBRARY_API void GetInfo(Info &info);
		PCSTREE_LIBRARY_API void Print() const;

	private:
                // feel free to add helper methods

		int RemoveSubtree(PCSNode* root);
		int CountNodes(PCSNode* root);
		int ComputeDepth(PCSNode* root);
		void ForwardReverseLinks();
	private:
		// Data
		Info	mInfo;
		PCSNode *pRoot;

	};

}

#endif

// ---  End of File ---
