#pragma once

#include "XAtlasWrapper.h"
#include "Structs.h"
#include "xatlas.h"

extern "C"
{

	XATLAS_WRAPPER_API void XAtlas_Destroy();

	XATLAS_WRAPPER_API void XAtlas_Create();

	XATLAS_WRAPPER_API xatlas::AddMeshError XAtlas_AddMesh(int index);

	XATLAS_WRAPPER_API void XAtlas_Generate();

	XATLAS_WRAPPER_API AtlasParams XAtlas_GetAtlasParams();

}

