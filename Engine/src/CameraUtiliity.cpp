//--------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include "CameraUtility.h"
#include "Camera.h"

namespace Azul
{
	CameraUtility *CameraUtility::posInstance = nullptr;
	bool CameraUtility::Ready = false;

	static Vec3 obj(0.0f, 0.0f, 0.0f);


	CameraUtility *CameraUtility::privGetInstance()
	{
		if (CameraUtility::posInstance == nullptr)
		{
			CameraUtility::posInstance = new CameraUtility();
		}

		return posInstance;
	}

	CameraUtility::~CameraUtility()
	{
		CameraUtility::Ready = false;
	}


	void CameraUtility::Destroy()
	{
		delete CameraUtility::posInstance;
	}

	void CameraUtility::Create(Camera *pCam)
	{
		CameraUtility *pUtil = CameraUtility::privGetInstance();
		assert(pUtil);
		assert(pCam);

		pCam->updateCamera();
		pCam->GetHelper(pUtil->Orig_up, 
						pUtil->Orig_tar,
						pUtil->Orig_pos,
						pUtil->Orig_upNorm, 
						pUtil->Orig_forwardNorm, 
						pUtil->Orig_rightNorm);

		CameraUtility::Ready = true;

	}

	void CameraUtility::UpdateCamera(Camera* pCam, CameraType type)
	{
		switch (type)
		{
		case CameraType::BEHIND:
			CameraUtility::BehindCamera(pCam);
			break;
		case CameraType::FIRST_PERSON:
			CameraUtility::FirstPersonCamera(pCam);
			break;
		case CameraType::TOP_DOWN:
			CameraUtility::TopDownCamera(pCam);
			break;
		case CameraType::SIDE_VIEW:
			CameraUtility::SideViewCamera(pCam);
			break;
		case CameraType::STATIC:
		default:
			break;
		}
	}

	void CameraUtility::FirstPersonCamera(Camera *pCam)
	{
		CameraUtility *pUtil = CameraUtility::privGetInstance();
		assert(pUtil);
		assert(pCam);
		assert(CameraUtility::Ready);

		pUtil->privUpdateHelper(pCam);

		float moveSpeed = 0.05f;
		float lookSpeed = 0.04f;

		if (GetKeyState('W') & 0x8000)
		{
			pUtil->pos += moveSpeed * pUtil->forwardNorm;
			pUtil->tar = pUtil->pos + pUtil->forwardNorm;
			pUtil->up = pUtil->pos + pUtil->upNorm;
		}
		else if (GetKeyState('S') & 0x8000)
		{
			pUtil->pos -= moveSpeed * pUtil->forwardNorm;
			pUtil->tar = pUtil->pos + pUtil->forwardNorm;
			pUtil->up = pUtil->pos + pUtil->upNorm;
		}

		if (GetKeyState('A') & 0x8000)
		{
			pUtil->pos -= moveSpeed * pUtil->rightNorm;
			pUtil->tar = pUtil->pos + pUtil->forwardNorm;
			pUtil->up = pUtil->pos + pUtil->upNorm;
		}
		else if (GetKeyState('D') & 0x8000)
		{
			pUtil->pos += moveSpeed * pUtil->rightNorm;
			pUtil->tar = pUtil->pos + pUtil->forwardNorm;
			pUtil->up = pUtil->pos + pUtil->upNorm;
		}


		if ((GetKeyState(VK_LEFT) & 0x8000))
		{
			
			Rot RotY;
			RotY.set(Axis::AxisAngle, pUtil->upNorm, lookSpeed);
			Mat4 M = RotY;

			Vec4 newForwardVec4 = Vec4(pUtil->forwardNorm, 0.0f) * M;
			Vec3 newForward(newForwardVec4.x(), newForwardVec4.y(), newForwardVec4.z());
			newForward.norm(); 

			pUtil->tar = pUtil->pos + newForward;
		}
		if ((GetKeyState(VK_RIGHT) & 0x8000))
		{
			Rot RotY;
			RotY.set(Axis::AxisAngle, pUtil->upNorm, -lookSpeed);
			Mat4 M = RotY;

			Vec4 newForwardVec4 = Vec4(pUtil->forwardNorm, 0.0f) * M;
			Vec3 newForward(newForwardVec4.x(), newForwardVec4.y(), newForwardVec4.z());
			newForward.norm(); 

			pUtil->tar = pUtil->pos + newForward;
		}
		if ((GetKeyState(VK_UP) & 0x8000))
		{
			Rot RotX;
			RotX.set(Axis::AxisAngle, pUtil->rightNorm, lookSpeed);
			Mat4 M = RotX;

			Vec4 newForwardVec4 = Vec4(pUtil->forwardNorm, 0.0f) * M;
			Vec3 newForward(newForwardVec4.x(), newForwardVec4.y(), newForwardVec4.z());
			newForward.norm(); 

			Vec4 newUpVec4 = Vec4(pUtil->upNorm, 0.0f) * M;
			Vec3 newUp(newUpVec4.x(), newUpVec4.y(), newUpVec4.z());
			newUp.norm(); 

			pUtil->tar = pUtil->pos + newForward;
			pUtil->up = pUtil->pos + newUp;
			
		}
		if ((GetKeyState(VK_DOWN) & 0x8000))
		{
			Rot RotX;
			RotX.set(Axis::AxisAngle, pUtil->rightNorm, -lookSpeed);
			Mat4 M = RotX;

			Vec4 newForwardVec4 = Vec4(pUtil->forwardNorm, 0.0f) * M;
			Vec3 newForward(newForwardVec4.x(), newForwardVec4.y(), newForwardVec4.z());
			newForward.norm(); 

			Vec4 newUpVec4 = Vec4(pUtil->upNorm, 0.0f) * M;
			Vec3 newUp(newUpVec4.x(), newUpVec4.y(), newUpVec4.z());
			newUp.norm(); 

			pUtil->tar = pUtil->pos + newForward;
			pUtil->up = pUtil->pos + newUp;
		}

		pCam->SetHelper(pUtil->up, pUtil->tar, pUtil->pos);
	}

	void CameraUtility::BehindCamera(Camera* pCam)
	{
		CameraUtility* pUtil = CameraUtility::privGetInstance();
		assert(pUtil);
		assert(pCam);
		assert(CameraUtility::Ready);

		pUtil->privUpdateHelper(pCam);

		if ((GetKeyState('S') & 0x8000))
		{
			// Reset	
			obj.set(0, 0, 0);
			pCam->SetHelper(pUtil->Orig_up, pUtil->Orig_tar, pUtil->Orig_pos);
		}

		if ((GetKeyState('W') & 0x8000))
		{
			Vec3 newObj(2, 0, 0);
			Vec3 delta = newObj - obj;

			pUtil->up += delta;
			pUtil->tar += delta;
			pUtil->pos += delta;

			obj = newObj;

			pCam->SetHelper(pUtil->up, pUtil->tar, pUtil->pos);
		}

		if ((GetKeyState('E') & 0x8000))
		{
			Vec3 newObj(-2, 0, 0);
			Vec3 delta = newObj - obj;

			pUtil->up += delta;
			pUtil->tar += delta;
			pUtil->pos += delta;

			obj = newObj;

			pCam->SetHelper(pUtil->up, pUtil->tar, pUtil->pos);
		}

		if ((GetKeyState('D') & 0x8000))
		{
			Vec3 newObj(0, 0, 0);
			Vec3 delta = newObj - obj;

			pUtil->up += delta;
			pUtil->tar += delta;
			pUtil->pos += delta;

			obj = newObj;

			pCam->SetHelper(pUtil->up, pUtil->tar, pUtil->pos);
		}

		if ((GetKeyState('I') & 0x8000))
		{
			pUtil->pos = pUtil->pos + 0.03f * pUtil->forwardNorm;
			pUtil->up = pUtil->up + 0.03f * pUtil->forwardNorm;

			pCam->SetHelper(pUtil->up, pUtil->tar, pUtil->pos);
		}

		if ((GetKeyState('O') & 0x8000))
		{
			pUtil->pos = pUtil->pos - 0.03f * pUtil->forwardNorm;
			pUtil->up = pUtil->up - 0.03f * pUtil->forwardNorm;

			pCam->SetHelper(pUtil->up, pUtil->tar, pUtil->pos);
		}

		if ((GetKeyState(VK_RIGHT) & 0x8000))
		{
			Trans TransA(pUtil->tar);
			Trans NegTrans(-pUtil->tar);

			Rot RotA;
			RotA.set(Axis::AxisAngle, pUtil->upNorm, +0.03f);

			Mat4 M = NegTrans * RotA * TransA;

			pUtil->up = Vec4(pUtil->up, 1.0f) * M;
			pUtil->pos = Vec4(pUtil->pos, 1.0f) * M;
			pUtil->tar = Vec4(pUtil->tar, 1.0f) * M;

			pCam->SetHelper(pUtil->up, pUtil->tar, pUtil->pos);
		}

		if ((GetKeyState(VK_LEFT) & 0x8000))
		{
			Trans TransA(pUtil->tar);
			Trans NegTrans(-pUtil->tar);

			Rot RotA;
			RotA.set(Axis::AxisAngle, pUtil->upNorm, -0.03f);

			Mat4 M = NegTrans * RotA * TransA;

			pUtil->up = Vec4(pUtil->up, 1.0f) * M;
			pUtil->pos = Vec4(pUtil->pos, 1.0f) * M;
			pUtil->tar = Vec4(pUtil->tar, 1.0f) * M;

			pCam->SetHelper(pUtil->up, pUtil->tar, pUtil->pos);
		}

		if ((GetKeyState(VK_DOWN) & 0x8000))
		{
			Trans TransA(pUtil->tar);
			Trans NegTrans(-pUtil->tar);

			Rot RotA;
			RotA.set(Axis::AxisAngle, pUtil->rightNorm, 0.03f);

			Mat4 M = NegTrans * RotA * TransA;

			pUtil->up = Vec4(pUtil->up, 1.0f) * M;
			pUtil->pos = Vec4(pUtil->pos, 1.0f) * M;
			pUtil->tar = Vec4(pUtil->tar, 1.0f) * M;

			pCam->SetHelper(pUtil->up, pUtil->tar, pUtil->pos);
		}

		if ((GetKeyState(VK_UP) & 0x8000))
		{
			Trans TransA(pUtil->tar);
			Trans NegTrans(-pUtil->tar);

			Rot RotA;
			RotA.set(Axis::AxisAngle, pUtil->rightNorm, -0.03f);

			Mat4 M = NegTrans * RotA * TransA;

			pUtil->up = Vec4(pUtil->up, 1.0f) * M;
			pUtil->pos = Vec4(pUtil->pos, 1.0f) * M;
			pUtil->tar = Vec4(pUtil->tar, 1.0f) * M;

			pCam->SetHelper(pUtil->up, pUtil->tar, pUtil->pos);
		}
	}

	void CameraUtility::TopDownCamera(Camera *pCam)
	{
		CameraUtility *pUtil = CameraUtility::privGetInstance();
		assert(pUtil);
		assert(pCam);
		assert(CameraUtility::Ready);

		pUtil->privUpdateHelper(pCam);

		if ((GetKeyState('S') & 0x8000))
		{
			// Reset	
			obj.set(0, 0, 0);
			pCam->SetHelper(pUtil->Orig_up, pUtil->Orig_tar, pUtil->Orig_pos);
		}

		if ((GetKeyState(VK_RIGHT) & 0x8000))
		{
			Trans TransA(pUtil->tar);
			Trans NegTrans(-pUtil->tar);

			Rot RotA;
			RotA.set(Axis::AxisAngle, pUtil->upNorm, +0.03f);

			Mat4 M = NegTrans * RotA * TransA;

			pUtil->up = Vec4(pUtil->up, 1.0f) * M;
			pUtil->pos = Vec4(pUtil->pos, 1.0f) * M;
			pUtil->tar = Vec4(pUtil->tar, 1.0f) * M;

			pCam->SetHelper(pUtil->up, pUtil->tar, pUtil->pos);
		}

		if ((GetKeyState(VK_LEFT) & 0x8000))
		{
			Trans TransA(pUtil->tar);
			Trans NegTrans(-pUtil->tar);

			Rot RotA;
			RotA.set(Axis::AxisAngle, pUtil->upNorm, -0.03f);

			Mat4 M = NegTrans * RotA * TransA;

			pUtil->up = Vec4(pUtil->up, 1.0f) * M;
			pUtil->pos = Vec4(pUtil->pos, 1.0f) * M;
			pUtil->tar = Vec4(pUtil->tar, 1.0f) * M;

			pCam->SetHelper(pUtil->up, pUtil->tar, pUtil->pos);
		}

		if ((GetKeyState(VK_DOWN) & 0x8000))
		{
			Trans TransA(pUtil->tar);
			Trans NegTrans(-pUtil->tar);

			Rot RotA;
			RotA.set(Axis::AxisAngle, pUtil->rightNorm, 0.03f);

			Mat4 M = NegTrans * RotA * TransA;

			pUtil->up = Vec4(pUtil->up, 1.0f) * M;
			pUtil->pos = Vec4(pUtil->pos, 1.0f) * M;
			pUtil->tar = Vec4(pUtil->tar, 1.0f) * M;

			pCam->SetHelper(pUtil->up, pUtil->tar, pUtil->pos);
		}

		if ((GetKeyState(VK_UP) & 0x8000))
		{
			Trans TransA(pUtil->tar);
			Trans NegTrans(-pUtil->tar);

			Rot RotA;
			RotA.set(Axis::AxisAngle, pUtil->rightNorm, -0.03f);

			Mat4 M = NegTrans * RotA * TransA;

			pUtil->up = Vec4(pUtil->up, 1.0f) * M;
			pUtil->pos = Vec4(pUtil->pos, 1.0f) * M;
			pUtil->tar = Vec4(pUtil->tar, 1.0f) * M;

			pCam->SetHelper(pUtil->up, pUtil->tar, pUtil->pos);
		}
	}

	void CameraUtility::SideViewCamera(Camera *pCam)
	{
		CameraUtility *pUtil = CameraUtility::privGetInstance();
		assert(pUtil);
		assert(pCam);
		assert(CameraUtility::Ready);

		pUtil->privUpdateHelper(pCam);

		if ((GetKeyState('S') & 0x8000))
		{
			// Reset	
			obj.set(0, 0, 0);
			pCam->SetHelper(pUtil->Orig_up, pUtil->Orig_tar, pUtil->Orig_pos);
		}

		if ((GetKeyState(VK_RIGHT) & 0x8000))
		{
			Trans TransA(pUtil->tar);
			Trans NegTrans(-pUtil->tar);

			Rot RotA;
			RotA.set(Axis::AxisAngle, pUtil->upNorm, +0.03f);

			Mat4 M = NegTrans * RotA * TransA;

			pUtil->up = Vec4(pUtil->up, 1.0f) * M;
			pUtil->pos = Vec4(pUtil->pos, 1.0f) * M;
			pUtil->tar = Vec4(pUtil->tar, 1.0f) * M;

			pCam->SetHelper(pUtil->up, pUtil->tar, pUtil->pos);
		}

		if ((GetKeyState(VK_LEFT) & 0x8000))
		{
			Trans TransA(pUtil->tar);
			Trans NegTrans(-pUtil->tar);

			Rot RotA;
			RotA.set(Axis::AxisAngle, pUtil->upNorm, -0.03f);

			Mat4 M = NegTrans * RotA * TransA;

			pUtil->up = Vec4(pUtil->up, 1.0f) * M;
			pUtil->pos = Vec4(pUtil->pos, 1.0f) * M;
			pUtil->tar = Vec4(pUtil->tar, 1.0f) * M;

			pCam->SetHelper(pUtil->up, pUtil->tar, pUtil->pos);
		}

		if ((GetKeyState(VK_DOWN) & 0x8000))
		{
			Trans TransA(pUtil->tar);
			Trans NegTrans(-pUtil->tar);

			Rot RotA;
			RotA.set(Axis::AxisAngle, pUtil->rightNorm, 0.03f);

			Mat4 M = NegTrans * RotA * TransA;

			pUtil->up = Vec4(pUtil->up, 1.0f) * M;
			pUtil->pos = Vec4(pUtil->pos, 1.0f) * M;
			pUtil->tar = Vec4(pUtil->tar, 1.0f) * M;

			pCam->SetHelper(pUtil->up, pUtil->tar, pUtil->pos);
		}

		if ((GetKeyState(VK_UP) & 0x8000))
		{
			Trans TransA(pUtil->tar);
			Trans NegTrans(-pUtil->tar);

			Rot RotA;
			RotA.set(Axis::AxisAngle, pUtil->rightNorm, -0.03f);

			Mat4 M = NegTrans * RotA * TransA;

			pUtil->up = Vec4(pUtil->up, 1.0f) * M;
			pUtil->pos = Vec4(pUtil->pos, 1.0f) * M;
			pUtil->tar = Vec4(pUtil->tar, 1.0f) * M;

			pCam->SetHelper(pUtil->up, pUtil->tar, pUtil->pos);
		}
	}

	void CameraUtility::privUpdateHelper(Camera *pCam)
	{
		assert(pCam);
		pCam->GetHelper(up, 
						tar,
						pos,
						upNorm,
						forwardNorm,
						rightNorm);

	}

}

// --- End of File ---
