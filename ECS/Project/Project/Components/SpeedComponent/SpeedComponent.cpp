#include "SpeedComponent.h"


//	Default SpeedComponent Constructor
SpeedComponent::SpeedComponent()
	:Component(ComponentType::SPEED_COMPONENT, ComponentTypeRequirement::SPEED_COMPONENT_REQUIREMENTS)
{
	speed = 0.0;
}

//	Default SpeedComponent Destructor
SpeedComponent::~SpeedComponent()
{

}

//	Return the Speed associated with this SpeedComponent.
float SpeedComponent::getSpeed() const
{
	return speed;
}

//	Set the Speed associated with this SpeedComponent.
void SpeedComponent::setSpeed(const float & newSpeed)
{
	speed = newSpeed;
}
