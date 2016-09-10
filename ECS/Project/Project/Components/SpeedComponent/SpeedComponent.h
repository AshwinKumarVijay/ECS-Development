#pragma once

#include "../ECS/Component/Component.h"

class SpeedComponent : public Component
{
public:
	
	//	Add Comments - TO DO
	SpeedComponent();

	//	Add Comments - TO DO
	~SpeedComponent();

	//	Add Comments - TO DO
	float getSpeed() const;

	//	Add Comments - TO DO
	virtual void setSpeed(const float & newSpeed);

private:
	
	float speed;
};

