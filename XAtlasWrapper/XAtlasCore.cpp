
#include "XAtlasCore.h"
#include "ObjLoader.h"

#include <string>
#include <vector>
#include <iostream>

xatlas::Atlas* atlas = nullptr;

void XAtlas_Destroy()
{
	if (atlas == nullptr)
		return;

	xatlas::Destroy(atlas);
	atlas = nullptr;
}

void XAtlas_Create()
{
	XAtlas_Destroy();
	atlas = xatlas::Create();
}

xatlas::AddMeshError XAtlas_AddMesh(int index)
{
	auto mesh = ObjLoader_CreateMeshDecl(index);
	if (mesh == nullptr)
		return xatlas::AddMeshError::Error;

	auto shape_count = ObjLoader_GetShapeCount();

	auto error_code = xatlas::AddMesh(atlas, *mesh, shape_count);

	delete mesh;

	return error_code;
}

void XAtlas_Generate()
{
	xatlas::Generate(atlas);
}

AtlasParams XAtlas_GetAtlasParams()
{
	AtlasParams params;

	params.MeshCount = atlas->meshCount;
	params.Width = atlas->width;
	params.Height = atlas->height;
	params.AtlasCount = atlas->atlasCount;
	params.ChartCount = atlas->chartCount;
	params.TexelsPerUnit = atlas->texelsPerUnit;

	return params;
}


