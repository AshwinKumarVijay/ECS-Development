#pragma once

#include <memory>
#include <map>
#include <vector>

#include "GL\glew.h"

struct RendererGeometryData;

class VAOStorage
{

public:
	
	//	Default VAOStorage Constructor.
	VAOStorage();

	//	Default VAOStorage Destructor.
	virtual ~VAOStorage();

	//	Create and Initialize the VAO.
	virtual void initializeVAO();

	//	Add Geometry to Storage.
	void addGeometryToStorage(std::shared_ptr<RendererGeometryData> newGeometry);
	
	//	Return the VAO ID.
	GLuint getVAOID() const;

	//	View the Geometry Names associated with this VAO.
	const std::vector<std::string> & viewGeometryNames() const;

	//	View the Geometry Datas.
	const std::vector<std::shared_ptr<RendererGeometryData>> & viewGeometryDatas() const;

	//	Remove Geometry from the VAOStorage.
	void removeGeometryFromStorage(std::string deadGeometryName);

	//	Clear the VAO of all Geometry.
	virtual void clearVAO();

	//	Delete the VAO.
	virtual void deleteVAO();

private:


	//	The list of Geometry Types.
	std::vector<std::string> geometryNames;

	//	The RendererGeometryData.
	std::vector<std::shared_ptr<RendererGeometryData>> rendererGeometryDatas;

	//	The VAO ID.
	GLuint vaoID;
	
};

