#pragma once

#include <memory>

#include "glm\glm.hpp"
#include "glm\matrix.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\quaternion.hpp"


class Transform
{

public:

	/**

	Name: Transform
	Parameters: -
	Purpose: Default Transform Constructor
	Return Value: -
	Other Output: -

	*/
	Transform();

	/**

	Name: ~Transform
	Parameters: -
	Purpose: Default Transform Destructor
	Return Value: -
	Other Output: -

	*/
	virtual ~Transform();


	/**

	Name: translateBy
	Parameters:
	- "moveAmount" - (vec3) (const) (&) - The vector by which we want to move this transform.
	Purpose: Move this Transform by some amount.
	Return Value: -
	Other Output: -

	*/
	void translateBy(const glm::vec3 & moveAmount);

	/**

	Name: scaleBy
	Parameters:
	- "scaleAmount" - (vec3) (const) (&) - The vector by which we want to scale this transform.
	Purpose: Scale this Transform by some amount.
	Return Value: -
	Other Output: -

	*/
	void scaleBy(const glm::vec3 & scaleAmount);


	/**

	Name: rotateBy
	Parameters:
	- "angleRad" - (float) (const) - The amount by which we want to rotate around the axis.
	- "axis" - (vec3) (const) (&) - The vector representing the axis around which we rotate.
	Purpose: Rotate this Transform by some amount around the axis.
	Return Value: -
	Other Output: -

	*/
	void rotateBy(const float angleRad, const glm::vec3 & axis);


	/**

	Name: setPosition
	Parameters:
	- "newTransformPosition" - (vec3) (const) (&) - Set the position of the Transform.
	Purpose: Default Entity Constructor
	Return Value: -
	Other Output: -

	*/
	void setPosition(const glm::vec3 & newTransformPosition);

	/**

	Name: setScale
	Parameters:
	- "newTransformScale" - (vec3) (const) (&) - Set the scale of the Transform.
	Purpose: Default Entity Constructor
	Return Value: -
	Other Output: -

	*/
	void setScale(const glm::vec3 & newTransformScale);

	/**

	Name: setRotation
	Parameters:
	- "newTransformRotation" - (quat) (const) (&) - Set the quaternion representing the rotation of the Transform.
	Purpose: Default Entity Constructor
	Return Value: -
	Other Output: -

	*/
	void setRotation(const glm::quat & newTransformRotation);

	/**

	Name: computeTransformMatrix
	Parameters: -
	Purpose: Compute the Transform Matrix of this Transform, independent of its hierarchy.
	Return Value: -
	Other Output: -

	*/
	void computeTransformMatrix();


	/**

	Name: getPosition
	Parameters: -
	Purpose: Return the current position of the Transform.
	Return Value:
	- (vec3) - The vector representing the position of the Transform.
	Other Output: -

	*/
	glm::vec3 getPosition() const;


	/**

	Name: getScale
	Parameters: -
	Purpose: Return the current scale of the Transform.
	Return Value: 
	- (vec3) - The vector representing the scale of the Transform.
	Other Output: -

	*/
	glm::vec3 getScale() const;


	/**

	Name: getRotation
	Parameters: -
	Purpose: Return the current rotation of the Transform.
	Return Value:
	- (quat) - The quaternion representing the rotation of the axis.
	Other Output: -

	*/

	glm::quat getRotation() const;


	/**

	Name: getDirection
	Parameters: -
	Purpose: Return the current facing/forward/viewing direction of the Transform.
	Return Value:
	- (vec3) - The vector representing the forward direction of the Transform.
	Other Output: -

	*/
	glm::vec3 getFowardDirection() const;

	/**

	Name: getRightVector
	Parameters: -
	Purpose: Return the current right direction of the Transform.
	Return Value:
	- (vec3) - The vector representing the right direction of the Transform.
	Other Output: -

	*/
	glm::vec3 getRightVector() const;



	/**

	Name: getUpVector
	Parameters: -
	Purpose: Return the current local up vector of the Transform.
	Return Value:
	- (vec3) - The vector representing the local up vector of the Transform.
	Other Output: -

	*/
	glm::vec3 getUpVector() const;


	/**

	Name: getTransform
	Parameters: -
	Purpose: Returns the Transform Matrix.
	Return Value:
	- (shared_ptr<mat4x4>) -
	Other Output: -

	*/

	std::shared_ptr<glm::mat4x4> getTransform() const;






private:

	//	The vector representing the position of the transform.
	glm::vec3 transformPosition;

	//	The vector representing the scale of the transform.
	glm::vec3 transformScale;

	//	The quaternion representing the rotation of the transform.
	glm::quat transformRotation;

	//	The matrix representing the translation * rotation * scale.
	std::shared_ptr<glm::mat4x4> transformMatrix;

	//	The boolean representing whether the transformMatrix accurately depicts the current position, scale and rotation. 
	bool dirtyMatrixFlag;
};

