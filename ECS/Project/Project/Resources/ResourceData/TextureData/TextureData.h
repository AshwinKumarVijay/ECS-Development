#pragma once
#include <memory>
#include <vector>

#include "GL\glew.h"

#include "glm\glm.hpp"

#include "../ResourceData.h"
#include "TextureBufferData\TextureBufferData.h"


struct Texture2D
{
	std::shared_ptr<TextureBufferData> texture;
};

struct TextureCube
{
	std::shared_ptr<TextureBufferData> textureCubeUp;
	std::shared_ptr<TextureBufferData> textureCubeDown;
	std::shared_ptr<TextureBufferData> textureCubeForward;
	std::shared_ptr<TextureBufferData> textureCubeBackward;
	std::shared_ptr<TextureBufferData> textureCubeRight;
	std::shared_ptr<TextureBufferData> textureCubeLeft;
};

class TextureData : public ResourceData
{

public:

	//	Default TextureData Constructor.
	TextureData(GLenum newTextureType);

	//	Default TextureData Destructor.
	virtual ~TextureData();

	//	Return the TextureType.
	GLenum getTextureType() const;

	//	Add Comments - TO DO
	void addTextureBufferData(int textureIndex, std::shared_ptr<TextureBufferData> newTextureBufferData);

	//	Add Comments - TO DO
	std::shared_ptr<const TextureBufferData> viewTextureBufferData(int textureIndex) const;

	//	Add Comments - TO DO
	std::shared_ptr<TextureBufferData> getTextureBufferData(int textureIndex);

	//	Add Comments - TO DO
	void deleteTextureBufferData(int textureIndex);


private:

	//	The Texture Type.
	GLenum textureType;

	Texture2D texture2D;
	TextureCube textureCube;

	//	The Texture Buffer Data.
	std::shared_ptr<TextureBufferData> textureBuffers[6];

};

