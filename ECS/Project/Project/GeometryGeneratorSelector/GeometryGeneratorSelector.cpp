#include "GeometryGeneratorSelector.h"
#include "../Resources/ResourceData/GeometryData/GeometryData.h"

//	Default GeometryGeneratorSelector Constructor
GeometryGeneratorSelector::GeometryGeneratorSelector()
{


}

//	Generate the Geometry from the OBJ filename, and the parameters.
std::shared_ptr<std::vector<std::shared_ptr<GeometryData>>> GeometryGeneratorSelector::generateGeometry(std::string geometryType, std::string geometryFilename, std::string geometryParameters)
{
	//	Create a new Geometry Data.
	std::shared_ptr<std::vector<std::shared_ptr<GeometryData>>> newGeometryData = std::make_shared<std::vector<std::shared_ptr<GeometryData>>>();

	//	If the Geometry Type is that of an OBJ
	if (geometryType == "OBJ")
	{
		//	Load the Object From File, and write it into the new Geommetry Data.
		loadObjectFromFile(geometryFilename, newGeometryData);
	}

	//	Return the Geometry Data.
	return newGeometryData;

}

//	Load the Object Filename, and write it into the Geometry Data.
void GeometryGeneratorSelector::loadObjectFromFile(std::string objFileName, std::shared_ptr<std::vector<std::shared_ptr<GeometryData>>> newGeometryData)
{
	//	Use the tiny object loader.

	//	The attributes.
	tinyobj::attrib_t attrib;

	//	The shapes of the object.
	std::vector<tinyobj::shape_t> shapes;

	//	The materials of the object.
	std::vector<tinyobj::material_t> materials;

	//	The error string.
	std::string err;

	//	Load the Obj into the attribute, the shapes and the materials.
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, objFileName.c_str());

	//	Check if there is any error.
	if (!err.empty()) 
	{ 
		// `err` may contain warning message.
		std::cerr << err << std::endl;
	}

	//	Quit if there was a problem with loading the object.
	if (!ret) 
	{
		exit(1);
	}

	std::cout << "# of shapes    : " << shapes.size() << std::endl;
	std::cout << "# of materials : " << materials.size() << std::endl;

	//	Initialize to max to zero and min to infinite.
	glm::vec3 maxXYZ = glm::vec3(0.0);
	glm::vec3 minXYZ = glm::vec3(FP_INFINITE);


	//	The list of of lists of indices.
	std::vector<std::vector<int>> currentIndicesArrays;

	//	The list of of lists of vertices.
	std::vector<std::vector<Vertex>> currentVertexArrays;

	//	Iterate over the shapes.
	for (size_t s = 0; s < shapes.size(); s++) 
	{
		//	The list of Indices.
		std::vector<int> currentIndicesArray;

		//	The list of Vertices.
		std::vector<Vertex> currentVertexArray;
		
		//	The list of offsets.
		std::vector<glm::vec3> offsets;
		
		//	Create the offsets to zero the shape to the origin.
		for (size_t i = 0; i < shapes[s].mesh.indices.size(); i++)
		{
			//	Get the index of the current vertex.
			int currentVertexIndex = shapes[s].mesh.indices[i].vertex_index;

			//	Get the vertex details.
			float vx = attrib.vertices[3 * currentVertexIndex + 0];
			float vy = attrib.vertices[3 * currentVertexIndex + 1];
			float vz = attrib.vertices[3 * currentVertexIndex + 2];

			//	Create the position.
			glm::vec3 position = glm::vec3(vx, vy, vz);

			//	Compare the extremities to the position.
			if (maxXYZ.x < position.x) maxXYZ.x = position.x;
			if (maxXYZ.y < position.y) maxXYZ.y = position.y;
			if (maxXYZ.z < position.z) maxXYZ.z = position.z;

			if (minXYZ.x > position.x) minXYZ.x = position.x;
			if (minXYZ.y > position.y) minXYZ.y = position.y;
			if (minXYZ.z > position.z) minXYZ.z = position.z;

			//	Add the offset to the list of offsets. 
			offsets.push_back(position);
		}


		//	Iterate over the indices.
		for (size_t i = 0; i < shapes[s].mesh.indices.size(); i++)
		{
			//	Create a new VertexData.
			Vertex vertexData;

			//	Add it to the list of indices. 
			currentIndicesArray.push_back((int)i);

			//	Get the vertex index.
			int currentVertexIndex = shapes[s].mesh.indices[i].vertex_index;
		
			//	Create the position vector.
			float vx = attrib.vertices[3 * currentVertexIndex + 0];
			float vy = attrib.vertices[3 * currentVertexIndex + 1];
			float vz = attrib.vertices[3 * currentVertexIndex + 2];

			//	
			glm::vec3 position = glm::vec3(vx, vy, vz);
			vertexData.position = glm::vec4(position + offsets[i], 1.0);

			//	Get the normal vertex.
			int currentNormalIndex = shapes[s].mesh.indices[i].normal_index;

			//	Create the normal vector.
			float nx = attrib.normals[3 * currentNormalIndex + 0];
			float ny = attrib.normals[3 * currentNormalIndex + 1];
			float nz = attrib.normals[3 * currentNormalIndex + 2];

			glm::vec3 normal = glm::vec3(nx, ny, nz);
			vertexData.normal = normal;

			//	Get the texture index.
			int currentTextureIndex = shapes[s].mesh.indices[i].texcoord_index;

			currentVertexArray.push_back(vertexData);
		}
		
		//	Add this list of indices to the list of lists of indices.
		currentIndicesArrays.push_back(currentIndicesArray);

		//	Add this list of vertices to the list of lists of vertices.
		currentVertexArrays.push_back(currentVertexArray);	
	}

	

	//	Iterate over the list of lists of indices.	
	for (int dataIterator = 0; dataIterator < currentIndicesArrays.size(); dataIterator++)
	{
		//	Create the geometry data of this pair of indices and vertices.
		std::shared_ptr<GeometryData> newGeometryDataElement = std::make_shared<GeometryData>(GL_TRIANGLES, currentIndicesArrays[dataIterator], currentVertexArrays[dataIterator]);
		
		//	Add the geometry data elememt to the Geometry Data.
		newGeometryData->push_back(newGeometryDataElement);
	}

}


//	Default GeometryGeneratorSelector Destructor
GeometryGeneratorSelector::~GeometryGeneratorSelector()
{



}
