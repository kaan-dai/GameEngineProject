#ifndef CAMERA_NODE_MAN_H
#define CAMERA_NODE_MAN_H 

#include "ManBase.h"
#include "CameraNode.h"
#include "Camera.h"

namespace Azul
{
	class CameraNodeMan : public ManBase
	{
	public:
		static void Create(int reserveNum = 0, int reserveGrow = 1);
		static void Destroy();

		static CameraNode *Add(CameraNode::Name name, Camera* pCamera);
		static CameraNode *Find(CameraNode::Name name);

		static void Remove(CameraNode* pNode);
		static void Dump();

		static void SetCurrentCamera(CameraNode::Name name);
		static Camera *GetCurrentCamera();
		static void SwitchToNextCamera();
		static void UpdateCurrentCamera();

		
	private:
		static CameraNodeMan *privGetInstance();

		~CameraNodeMan();
		CameraNodeMan(int reserveNum, int reserveGrow);

	protected:
		DLink *derivedCreateNode() override;

	private:
		CameraNode *poNodeCompare;
		static CameraNodeMan *posInstance;
		static CameraNode *poCurrentCamera;
	};
}
#endif

// --- End of File ---