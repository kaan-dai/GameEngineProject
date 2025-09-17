#include "CameraNodeMan.h"
#include "CameraUtility.h"
#include "DLinkMan.h"

namespace Azul
{
	CameraNodeMan *CameraNodeMan::posInstance = nullptr;
	CameraNode *CameraNodeMan::poCurrentCamera = nullptr;

	CameraNodeMan::CameraNodeMan(int reserveNum, int reserveGrow)
		: ManBase(new DLinkMan(), new DLinkMan(), reserveNum, reserveGrow)
	{
		this->proFillReservedPool(reserveNum);
		this->poNodeCompare = new CameraNode();
	}

	CameraNodeMan::~CameraNodeMan()
	{
		delete this->poNodeCompare;
		this->poNodeCompare = nullptr;

		Iterator *pIt = this->baseGetActiveIterator();

		DLink* pNode = pIt->First();

		while (!pIt->IsDone())
		{
			CameraNode *pDeleteMe = (CameraNode*)pIt->Curr();
			pNode = pIt->Next();
			delete pDeleteMe;
		}

		pIt = this->baseGetReserveIterator();

		pNode = pIt->First();

		while (!pIt->IsDone())
		{
			CameraNode *pDeleteMe = (CameraNode*)pIt->Curr();
			pNode = pIt->Next();
			delete pDeleteMe;
		}
	}

	void CameraNodeMan::Create(int reserveNum, int reserveGrow)
	{
		assert(reserveNum >= 0);
		assert(reserveGrow > 0);
		assert(posInstance == nullptr);

		if (posInstance == nullptr)
		{
			posInstance = new CameraNodeMan(reserveNum, reserveGrow);
		}
	}

	void CameraNodeMan::Destroy()
	{
		CameraNodeMan *pMan = CameraNodeMan::privGetInstance();
		assert(pMan != nullptr);
		AZUL_UNUSED_VAR(pMan);

		delete CameraNodeMan::posInstance;
		CameraNodeMan::posInstance = nullptr;
	}

	CameraNode* CameraNodeMan::Add(CameraNode::Name name, Camera *pCamera)
	{
		CameraNodeMan *pMan = CameraNodeMan::privGetInstance();

		assert(pCamera);

		CameraNode *pNode = (CameraNode*)pMan->baseAddToFront();
		assert(pNode != nullptr);

		pNode->Set(name, pCamera);

		if (CameraNodeMan::poCurrentCamera == nullptr)
		{
			CameraNodeMan::poCurrentCamera = pNode;
		}

		return pNode;
	}

	CameraNode *CameraNodeMan::Find(CameraNode::Name _name)
	{
		CameraNodeMan *pMan = CameraNodeMan::privGetInstance();
		assert(pMan != nullptr);

		pMan->poNodeCompare->SetNameForComparison(_name);
		CameraNode *pData = (CameraNode*)pMan->baseFind(pMan->poNodeCompare);
		return pData;
	}

	void CameraNodeMan::Remove(CameraNode* pNode)
	{
		assert(pNode != nullptr);

		CameraNodeMan *pMan = CameraNodeMan::privGetInstance();
		assert(pMan != nullptr);

		if (CameraNodeMan::poCurrentCamera == pNode)
		{
			CameraNodeMan::SwitchToNextCamera();
		}

		pMan->baseRemove(pNode);
	}

	void CameraNodeMan::Dump()
	{
		CameraNodeMan *pMan = CameraNodeMan::privGetInstance();
		assert(pMan != nullptr);

		pMan->baseDump();
	}

	void CameraNodeMan::SetCurrentCamera(CameraNode::Name name)
	{
		CameraNode *pNode = CameraNodeMan::Find(name);
		if (pNode != nullptr)
		{
			CameraNodeMan::poCurrentCamera = pNode;
		}
	}

	Camera* CameraNodeMan::GetCurrentCamera()
	{
		if (CameraNodeMan::poCurrentCamera != nullptr)
		{
			return CameraNodeMan::poCurrentCamera->GetCamera();
		}
		return nullptr;
	}

	void CameraNodeMan::SwitchToNextCamera()
	{
		CameraNodeMan *pMan = CameraNodeMan::privGetInstance();
		assert(pMan != nullptr);

		if (CameraNodeMan::poCurrentCamera == nullptr)
		{
			Iterator *pIt = pMan->baseGetActiveIterator();
			DLink *pNode = pIt->First();
			if (!pIt->IsDone())
			{
				CameraNodeMan::poCurrentCamera = (CameraNode*)pNode;
			}
		}
		else
		{
			Iterator *pIt = pMan->baseGetActiveIterator();
			DLink *pNode = pIt->First();

			while (!pIt->IsDone() && pNode != CameraNodeMan::poCurrentCamera)
			{
				pNode = pIt->Next();
			}

			if (!pIt->IsDone())
			{
				pNode = pIt->Next();
				if (pIt->IsDone())
				{
					pNode = pIt->First();
				}
				CameraNodeMan::poCurrentCamera = (CameraNode*)pNode;
			}
		}
	}

	void CameraNodeMan::UpdateCurrentCamera()
	{
		Camera *pCam = CameraNodeMan::GetCurrentCamera();
		if (pCam != nullptr)
		{
			static bool keyPressed = false;

			if ((GetKeyState('C') & 0x8000))
			{
				if (!keyPressed)
				{
					CameraNodeMan::SwitchToNextCamera();
					keyPressed = true;
				}
			}
			else
			{
				keyPressed = false;
			}

			CameraUtility::CameraType cameraType = CameraNodeMan::poCurrentCamera->GetCameraUtilityType();
			CameraUtility::UpdateCamera(pCam, cameraType);

			pCam->updateCamera();
		}
	}


	CameraNodeMan *CameraNodeMan::privGetInstance()
	{
		assert(posInstance != nullptr);

		return posInstance;
	}

	DLink *CameraNodeMan::derivedCreateNode()
	{
		DLink *pNodeBase = new CameraNode();
		assert(pNodeBase != nullptr);

		return pNodeBase;
	}
	
}

// --- End of File ---