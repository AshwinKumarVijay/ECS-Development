#include "MaterialData.h"


//	Default MaterialData Constructor
MaterialData::MaterialData(const MaterialValues & newMaterialValues, const MaterialMaps & newMaterialMaps)
{
	materialValues = newMaterialValues;
	materialMaps = newMaterialMaps;
}

//	Default MaterialData Destructor
MaterialData::~MaterialData()
{

}

//	Return the Material Values associated.
const MaterialValues & MaterialData::viewMaterialValues() const
{
	return materialValues;
}

//	Return the Material Maps associated.
const MaterialMaps & MaterialData::viewMaterialMaps() const
{
	return materialMaps;
}
