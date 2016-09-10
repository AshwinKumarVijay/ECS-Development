#include "Transform.h"


//	Default Transform Constructor
Transform::Transform()
{
	transformPosition = glm::vec3(0.0);
	transformScale = glm::vec3(1.0);
	transformRotation = glm::quat();
	transformMatrix = std::make_shared<glm::mat4x4>(1.0f);
	dirtyMatrixFlag = true;
}

//	Default Transform Destructor
Transform::~Transform()
{

}

//	Translate the transform by some amount.
void Transform::translateBy(const glm::vec3 & moveAmount)
{
	transformPosition = transformPosition + moveAmount;
	dirtyMatrixFlag = true;
}

//	Scale the transform by some amount.
void Transform::scaleBy(const glm::vec3 & scaleAmount)
{
	transformScale = transformScale * scaleAmount;
	dirtyMatrixFlag = true;
}

//	Rotate this Transform
void Transform::rotateBy(const float angleRad, const glm::vec3 & axis)
{

	transformRotation = glm::angleAxis(angleRad, glm::normalize(axis)) * transformRotation;
	dirtyMatrixFlag = true;
}

//	Set the position of this Transform.
void Transform::setPosition(const glm::vec3 & newTransformPosition)
{
	transformPosition = glm::vec3(newTransformPosition);
	dirtyMatrixFlag = true;
}

//	Set the vector representing the scale of the transform.
void Transform::setScale(const glm::vec3 & newTransformScale)
{
	transformScale = glm::vec3(newTransformScale);
	dirtyMatrixFlag = true;
}

//	Set the rotation of this Transform.
void Transform::setRotation(const glm::quat & newTransformRotation)
{
	transformRotation = glm::quat(newTransformRotation);
	dirtyMatrixFlag = true;
}

//	Compute the Transform Matrix.
void Transform::computeTransformMatrix()
{
	glm::mat4x4 positionMatrix = glm::mat4x4();
	positionMatrix = glm::translate(positionMatrix, transformPosition);

	glm::mat4x4 scaleMatrix = glm::mat4x4();
	scaleMatrix = glm::scale(scaleMatrix, transformScale);

	*transformMatrix = positionMatrix *  glm::mat4_cast(transformRotation) * scaleMatrix;
	dirtyMatrixFlag = false;
}

//	Return the vector represeting the translation of the transform.
glm::vec3 Transform::getPosition() const
{
	return transformPosition;
}

//	Return the vector representing the scale of the transform.
glm::vec3 Transform::getScale() const
{
	return transformScale;
}

//	Return the quaternion representing the rotation of the transform.
glm::quat Transform::getRotation() const
{
	return transformRotation;
}

//	Return the vector representing the direction of the transform.
glm::vec3 Transform::getFowardDirection() const
{
	return glm::normalize(glm::vec3(glm::mat4_cast(transformRotation) * glm::vec4(0.0, 0.0, -1.0, 0.0))); // bug fixed: should NOT be (0,0,1,0)
}


//	Return the vector representing the right of the transform.
glm::vec3 Transform::getRightVector() const
{

	return glm::normalize(glm::vec3(glm::mat4_cast(transformRotation) * glm::vec4(1.0, 0.0, 0.0, 0.0)));
}

//	Return the vector representing the upward direction of the transform.
glm::vec3 Transform::getUpVector() const
{
	return glm::normalize(glm::vec3(glm::mat4_cast(transformRotation) * glm::vec4(0.0, 1.0, 0.0, 0.0)));
}

//	Return a pointer to the transform matrix.
std::shared_ptr<glm::mat4x4> Transform::getTransform() const
{
	return transformMatrix;
}