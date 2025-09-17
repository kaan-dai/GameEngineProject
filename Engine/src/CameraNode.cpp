#include "CameraNode.h"

namespace Azul
{
	CameraNode::CameraNode()
		: DLink(),
		poCamera(nullptr),
		name(CameraNode::Name::UNINITIALIZED)
	{
		this->privClear();
	}

	CameraNode::~CameraNode()
	{
		this->privClear();
	}

	void CameraNode::Set(CameraNode::Name _name, Camera *_pCamera)
	{
		assert(_pCamera);

		this->poCamera = _pCamera;
		this->name = _name;
	}

	Camera* CameraNode::GetCamera()
	{
		return this->poCamera;
	}

	CameraNode::Name CameraNode::GetCameraName()  
	{
		return this->name;
	}

	void CameraNode::SetNameForComparison(CameraNode::Name _name)
	{
		this->name = _name;
	}

	CameraUtility::CameraType CameraNode::GetCameraUtilityType()
	{
		switch (this->name)
		{
		case CameraNode::Name::BEHIND_CAMERA:
			return CameraUtility::CameraType::BEHIND;
		case CameraNode::Name::FIRST_PERSON_CAMERA:
			return CameraUtility::CameraType::FIRST_PERSON;
		case CameraNode::Name::TOP_DOWN_CAMERA:
			return CameraUtility::CameraType::TOP_DOWN;
		case CameraNode::Name::SIDE_VIEW_CAMERA:
			return CameraUtility::CameraType::SIDE_VIEW;
		case CameraNode::Name::MAIN_CAMERA:
		case CameraNode::Name::UNINITIALIZED:
		default:
			return CameraUtility::CameraType::STATIC;
		}
	}

	void CameraNode::privClear()
	{
		if (this->poCamera)
		{
			delete this->poCamera;
		}
		this->poCamera = nullptr;
		this->name = CameraNode::Name::UNINITIALIZED;
	}


	char* CameraNode::GetName()  
	{
		static char pTmp[128];
		switch (this->name)
		{
		case CameraNode::Name::MAIN_CAMERA:
			strcpy_s(pTmp, 128, "MAIN_CAMERA");
			break;
		case CameraNode::Name::BEHIND_CAMERA:
			strcpy_s(pTmp, 128, "BEHIND_CAMERA");
			break;
		case CameraNode::Name::FIRST_PERSON_CAMERA:
			strcpy_s(pTmp, 128, "FIRST_PERSON_CAMERA");
			break;
		case CameraNode::Name::TOP_DOWN_CAMERA:
			strcpy_s(pTmp, 128, "TOP_DOWN_CAMERA");
			break;
		case CameraNode::Name::SIDE_VIEW_CAMERA:
			strcpy_s(pTmp, 128, "SIDE_VIEW_CAMERA");
			break;
		case CameraNode::Name::UNINITIALIZED:
			strcpy_s(pTmp, 128, "UNINITIALIZED");
			break;
		default:
			strcpy_s(pTmp, 128, "UNKNOWN");
			break;
		}
		return pTmp;
	}

	void CameraNode::Wash()
	{
		this->privClear();
	}

	bool CameraNode::Compare(DLink *pTargetNode)
	{
		assert(pTargetNode);

		CameraNode *pDataB = (CameraNode*)pTargetNode;

		bool status = false;

		if (this->name == pDataB->name)
		{
			status = true;
		}

		return status;
	}

	void CameraNode::Dump()
	{
		Trace::out("      CameraNode(%p)\n", this);
		Trace::out("      Name: %s \n", this->GetName());
		Trace::out("      Camera: %p \n", this->poCamera);

		this->DLink::Dump();
	}
}

// --- End of File ---