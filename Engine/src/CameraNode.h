#ifndef CAMERA_NODE_H
#define CAMERA_NODE_H

#include "DLink.h"
#include "Camera.h"
#include "CameraUtility.h"


namespace Azul
{

	class CameraNode : public DLink
	{
	public:
		enum class Name
		{
			MAIN_CAMERA,
			BEHIND_CAMERA,
			FIRST_PERSON_CAMERA,
			TOP_DOWN_CAMERA,
			SIDE_VIEW_CAMERA,
			UNINITIALIZED
		};

	public:
		CameraNode();
		CameraNode(const CameraNode&) = delete;
		CameraNode& operator = (const CameraNode&) = delete;
		virtual ~CameraNode();

		void Set(CameraNode::Name name, Camera* pCamera);
		void SetNameForComparison(CameraNode::Name _name);
		Camera *GetCamera();
		CameraNode::Name GetCameraName();
		CameraUtility::CameraType GetCameraUtilityType();

		virtual char *GetName() override;  
		virtual void Wash() override;
		virtual bool Compare(DLink* pTargetNode) override;
		virtual void Dump() override;

	private:
		void privClear();
		//--------------------------------------------------
		// Data
		//--------------------------------------------------
		Camera *poCamera;
		CameraNode::Name name;
	};
}

#endif

// --- End of File ---