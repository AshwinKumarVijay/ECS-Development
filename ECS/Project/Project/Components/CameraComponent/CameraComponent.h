#pragma once

#include "../ECS/Component/Component.h"
#include "../Camera/Camera.h"

struct CameraDescription
{	

};


class CameraComponent : public Component
{

public:

	//	Add Comments - TO DO
	CameraComponent();

	//	Add Comments - TO DO
	virtual ~CameraComponent();

	//	Add Comments - TO DO
	void setActive();

	//	Add Comments - TO DO
	void setInactive();

	//	Add Comments - TO DO
	bool getIsActive() const;

	//	Add Comments - TO DO
	float getNearClip() const;
	//	Add Comments - TO DO
	void setNearClip(float newNearClip);

	//	Add Comments - TO DO
	float getFarClip() const;
	//	Add Comments - TO DO
	void setFarClip(float newFarClip);

	//	Add Comments - TO DO
	float getFOV() const;
	//	Add Comments - TO DO
	void setFOV(float newFOV);

	//	Add Comments - TO DO
	float getAspectRatio() const;
	//	Add Comments - TO DO
	void setAspectRatio(float newAspectRatio);
	


private:

	//	Add Comments- TO DO.
	bool isActive;

	//	Add Comments- TO DO.
	float nearClip;
	//	Add Comments- TO DO.
	float farClip;
	
	//	Add Comments- TO DO.
	float FOV;
	//	Add Comments- TO DO.
	float aspectRatio;
};

