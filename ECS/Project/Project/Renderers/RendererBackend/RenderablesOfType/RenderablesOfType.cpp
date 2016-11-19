#include "RenderablesOfType.h"
#include "../../Renderable/Renderable.h"

//	Default Renderables of Type Constructor.
RenderablesOfType::RenderablesOfType(const RenderableType & newRenderableType)
{

	renderableType = std::make_shared<RenderableType>(newRenderableType);
	renderableTransformMatrices = std::make_shared<std::vector<glm::mat4>>();
	renderableMetaDatas = std::make_shared<std::vector<std::shared_ptr<RenderableMetaData>>>();

	//	Generate and Bind the Buffer.
	glGenBuffers(1, &transformMatrixBuffer);

	//	Generate an initial buffer.
	int maxBufferSize = 20;
	glNamedBufferData(transformMatrixBuffer, maxBufferSize * sizeof(glm::mat4), NULL, GL_DYNAMIC_DRAW);

	//	
	dirtyTransformMatrixBuffer = true;
}

//	Default Renderables of Type Destructor.
RenderablesOfType::~RenderablesOfType()
{
	glDeleteBuffers(1, &transformMatrixBuffer);
}

//	Add Renderable.
void RenderablesOfType::addRenderable(std::shared_ptr<RenderableMetaData> newRenderable)
{
	if (newRenderable->renderableType == renderableType)
	{
		newRenderable->renderableEntry = renderableMetaDatas->size();
		renderableMetaDatas->push_back(newRenderable);
		renderableTransformMatrices->push_back(newRenderable->renderable->getTransformMatrix());

		//	
		dirtyTransformMatrixBuffer = true;
	}
}

//	Update the Transform Matrix.
void RenderablesOfType::updateTransformMatrix(std::shared_ptr<RenderableMetaData> updatedRenderable)
{
	if (updatedRenderable->renderableType == renderableType)
	{
		(*renderableTransformMatrices)[updatedRenderable->renderableEntry] = updatedRenderable->renderable->getTransformMatrix();
		dirtyTransformMatrixBuffer = true;
	}
}

//	
std::shared_ptr<const RenderableType> RenderablesOfType::viewRenderableType() const
{
	return renderableType;
}

//	Return the Renderable MetaDatas.
std::shared_ptr<std::vector<std::shared_ptr<RenderableMetaData>>> RenderablesOfType::getRenderableMetaDatas()
{
	return renderableMetaDatas;
}

//	Return the Renderable MetaDatas.
std::shared_ptr<const std::vector<std::shared_ptr<RenderableMetaData>>> RenderablesOfType::viewRenderableMetaDatas() const
{
	return renderableMetaDatas;
}

//	Return the Renderables.	
std::shared_ptr<std::vector<glm::mat4>> RenderablesOfType::getRenderableTransformMatrices()
{
	return renderableTransformMatrices;
}

//	View the Renderable Transform Matrices.
std::shared_ptr<const std::vector<glm::mat4>> RenderablesOfType::viewRenderableTransformMatrices() const
{
	return renderableTransformMatrices;
}

//	Return the Renderables of Type Count.
int RenderablesOfType::getRenderablesofTypeCount()
{
	return renderableMetaDatas->size();
}

//	Return the Transform Matrices Buffer.
GLuint RenderablesOfType::getTransformMatricesBuffer()
{
	//	Check if our Transform Matrix Buffer does not accurately reflect our buffer.
	if (dirtyTransformMatrixBuffer)
	{
		//	
		if (maxBufferSize <= renderableMetaDatas->size())
		{
			//	Double the size of the buffer, and delete the old one.
			maxBufferSize = maxBufferSize * 2;
			glDeleteBuffers(1, &transformMatrixBuffer);

			//	Generate a new buffer of twice the size.
			glGenBuffers(1, &transformMatrixBuffer);
			glNamedBufferData(transformMatrixBuffer, maxBufferSize * sizeof(glm::mat4), NULL, GL_DYNAMIC_DRAW);
			
		}
		
		//	Fill the new buffer.
		glNamedBufferSubData(transformMatrixBuffer, 0, renderableMetaDatas->size(), renderableTransformMatrices->data());
		dirtyTransformMatrixBuffer = false;
	}

	return transformMatrixBuffer;
}

//	Remove the Renderable.
void RenderablesOfType::removeRenderable(std::shared_ptr<RenderableMetaData> deadRenderable)
{
	//	Find the entry of the renderable.
	int renderableEntry = deadRenderable->renderableEntry;
	
	//	
	(*renderableMetaDatas)[renderableEntry] = (*renderableMetaDatas)[renderableMetaDatas->size() - 1];
	(*renderableTransformMatrices)[renderableEntry] = (*renderableTransformMatrices)[renderableTransformMatrices->size() - 1];

	//	
	renderableMetaDatas->pop_back();
	renderableTransformMatrices->pop_back();

	//	Mark the Transform Matrix Buffer as incorrect.
	dirtyTransformMatrixBuffer = true;
}

