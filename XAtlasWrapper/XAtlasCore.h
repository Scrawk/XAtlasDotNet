#pragma once

#include "XAtlasWrapper.h"
#include "Structs.h"
#include "xatlas.h"

extern "C"
{

	XATLAS_WRAPPER_API void XAtlas_Destroy();

	XATLAS_WRAPPER_API void XAtlas_Create();

	XATLAS_WRAPPER_API void XAtlas_SeedRand(int seed);

	XATLAS_WRAPPER_API xatlas::AddMeshError XAtlas_AddMesh(int index);

	XATLAS_WRAPPER_API xatlas::AddMeshError XAtlas_AddUVMesh(int index);

	XATLAS_WRAPPER_API void XAtlas_Generate(const xatlas::ChartOptions& chart_options, const xatlas::PackOptions& pack_options);

	XATLAS_WRAPPER_API void XAtlas_ComputeCharts(const xatlas::ChartOptions& options);

	XATLAS_WRAPPER_API void XAtlas_PackCharts(const xatlas::PackOptions& options);

	XATLAS_WRAPPER_API AtlasParams XAtlas_GetAtlasParams();

	XATLAS_WRAPPER_API BOOL XAtlas_SaveAllMeshsObj(const char* filename);

	XATLAS_WRAPPER_API BOOL XAtlas_SaveMeshObj(int index, const char* filename);

	XATLAS_WRAPPER_API BOOL XAtlas_SaveChartImages(const char* filename, const uint8_t* background_color, const uint8_t* line_color);

	XATLAS_WRAPPER_API BOOL XAtlas_SaveMeshImages(const char* filename, const uint8_t* background_color, const uint8_t* line_color);

}

