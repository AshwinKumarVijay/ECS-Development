#pragma once

#include <map>
#include <memory>
#include <set>
#include <vector>

#include "GL\glew.h"
#include "glm\glm.hpp"

class Renderable;
struct RendererGeometryData;
class RenderablesOfType;
struct RenderableMetaData;
struct RenderableType;
struct GeometryTypeMetaData;

//	Description of a specific Type for a collection of Renderables.
struct RenderableType
{
	//	Construct a Type Key given the Shader Type, the Geometry Type and the Material Type.
	RenderableType(const std::string & newShaderType, const std::string & newGeometryType, const std::string & newMaterialType)
	{
		//	The Shader Type.
		shaderType = newShaderType;

		//	The Geometry Type.
		geometryType = newGeometryType;

		//	The Material Type.
		materialType = newMaterialType;
	}

	RenderableType(const RenderableType & other)
	{
		//	The Shader Type.
		shaderType = other.shaderType;

		//	The Geometry Type.
		geometryType = other.geometryType;

		//	The Material Type.
		materialType = other.materialType;
	}


	//	Overloaded Less Than Comparison Operator.
	bool operator< (const RenderableType & other) const
	{
		//	Compare the Shader Types first.
		if (shaderType < other.shaderType)
		{
			//	If the ShaderType is less than the other ShaderType.
			return true;
		}
		else if (shaderType == other.shaderType)
		{
			//	If the Shader Types are the same, compare the Geometry Types.
			if (geometryType < other.geometryType)
			{
				//	If the GeometryType is less than the other GeometryType.
				return true;
			}
			else if (geometryType == other.geometryType)
			{
				//	If the Shader Types and the Geometry Types are equal, then compare the material types.
				if (materialType < other.materialType)
				{
					//	If the MaterialType is less than the other MaterialType.
					return true;
				}
				else if (materialType == other.materialType)
				{
					//	If the ShaderType, the GeometryType and the MaterialTypes are all the same.
					return false;
				}
				else
				{
					//	If the MaterialType is greater than the other MaterialType.
					return false;
				}
			}
			else
			{
				//	If the GeometryType is greater than the other GeometryType.
				return false;
			}
		}
		else
		{
			//	If the ShaderType is greater than the other ShaderType.
			return false;
		}
	}

	//	The Shader Type.
	std::string shaderType;

	//	The Geometry Type.
	std::string geometryType;

	//	The Material Type.
	std::string materialType;
};


//	RenderableMetaData.
struct RenderableMetaData
{
	int renderableEntry;
	std::shared_ptr<Renderable> renderable;
	std::shared_ptr<RenderableType> renderableType;
};

//	VAO Meta Data.
struct VAOMetaData
{
	GLuint vaoID = 0;
	std::map<std::string, std::shared_ptr<GeometryTypeMetaData>> geometryTypeMetaDatas;
};

struct MaterialTypeMetaData
{
	GLuint transformMatricesVBO;
	std::shared_ptr<RenderablesOfType> renderablesOfType;
};

//	Geometry Type Meta Data.
struct GeometryTypeMetaData
{
	//	Comparing Meta Data is Simply Comparing VaoIDs first, and then comparing strings.
	bool operator< (const GeometryTypeMetaData & other) const
	{
		auto vaoMD = vaoMetaData.lock();
		auto othervaoMD = other.vaoMetaData.lock();

		if (vaoMD == NULL && othervaoMD == NULL)
		{
			return false;
		}
		else if (vaoMD != NULL && othervaoMD == NULL)
		{
			return false;
		}
		else if (vaoMD == NULL && othervaoMD != NULL)
		{
			return true;
		}
		else
		{
			if (vaoMetaData.lock()->vaoID < other.vaoMetaData.lock()->vaoID)
			{
				return true;
			}
			else if (vaoMetaData.lock()->vaoID == other.vaoMetaData.lock()->vaoID)
			{
				if (geometryType < other.geometryType)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}

	}

	//	Name of the Geometry Type we represent.
	std::string geometryType;

	//	Weak Pointer to the Associated VAO Meta Data.
	std::weak_ptr<VAOMetaData> vaoMetaData;

	//	Shared Pointer to the Renderer Geometry Data.
	std::shared_ptr<RendererGeometryData> rendererGeometryData;
};


//	Renderables of the Specified Type of Shader Type, Geometry Type and Material Type.
struct RenderablesOfSpecifiedType
{

	std::shared_ptr<RenderablesOfType> renderables;

};

struct VAOIDGeometryTypeKey
{
	//	Comparison for the 
	bool operator<(const VAOIDGeometryTypeKey& other) const
	{
		if (vaoID < other.vaoID)
		{
			return true;
		}
		else if (vaoID == other.vaoID)
		{
			if (geometryType < other.geometryType)
			{
				return true;
			}
			else if (geometryType == other.geometryType)
			{
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}

	}

	//	The VAO ID of this Key.
	GLuint vaoID = 0;

	//	The Geometry Type of this Key.
	std::string geometryType;
};


