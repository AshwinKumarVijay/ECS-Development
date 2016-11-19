#pragma once

#include "../../RenderablesMetaData.h"

class RenderablesOfType
{
public:
	
	//	Default Renderables of Type Constructor.
	RenderablesOfType(const RenderableType & newRenderableType);

	//	Default Renderables of Type Destructor.
	virtual ~RenderablesOfType();

	//	Add the new Renderable.
	virtual void addRenderable(std::shared_ptr<RenderableMetaData> newRenderable);

	//	Update the Transform Matrix of the Renderable.
	virtual void updateTransformMatrix(std::shared_ptr<RenderableMetaData> updatedRenderable);

	//	View the type of Renderable stored here.
	std::shared_ptr<const RenderableType> viewRenderableType() const;

	//	Return the Renderable MetaDatas.
	std::shared_ptr<std::vector<std::shared_ptr<RenderableMetaData>>> getRenderableMetaDatas();

	//	Return the Renderable MetaDatas.
	std::shared_ptr<const std::vector<std::shared_ptr<RenderableMetaData>>> viewRenderableMetaDatas() const;

	//	Return the Renderable Transform Matrices.
	std::shared_ptr<std::vector<glm::mat4>> getRenderableTransformMatrices();

	//	Return the Renderable Transform Matices.
	std::shared_ptr<const std::vector<glm::mat4>> viewRenderableTransformMatrices() const;

	//	Return the number of Renderables held.
	virtual int getRenderablesofTypeCount();

	//	Update and return the Transform Matrices Buffer.
	virtual GLuint getTransformMatricesBuffer();

	//	Remove the Renderable.
	virtual void removeRenderable(std::shared_ptr<RenderableMetaData> deadRenderable);

private:

	//	The Type of Renderables that we are holding.
	std::shared_ptr<RenderableType> renderableType;

	//	The Vector of Renderable Transform Matrices.
	std::shared_ptr<std::vector<glm::mat4>> renderableTransformMatrices;

	//	The Vector of Renderable Meta Data.
	std::shared_ptr<std::vector<std::shared_ptr<RenderableMetaData>>> renderableMetaDatas;

	
	//	Transform Buffer State.
	GLuint transformMatrixBuffer;
	bool dirtyTransformMatrixBuffer;
	int maxBufferSize;
};