
#include "XAtlasCore.h"
#include "ObjLoader.h"
#include "Rasterizer.h"
#include "stb_image_write.h"

#include <vector>
#include <iostream>

#ifdef _MSC_VER
#define FOPEN(_file, _filename, _mode) { if (fopen_s(&_file, _filename, _mode) != 0) _file = NULL; }
#define STRICMP _stricmp
#else
#define FOPEN(_file, _filename, _mode) _file = fopen(_filename, _mode)
#include <strings.h>
#define STRICMP strcasecmp
#endif


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

void XAtlas_SeedRand(int seed)
{
	SeedRand(seed);
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

xatlas::AddMeshError XAtlas_AddUVMesh(int index)
{
	auto shape = ObjLoader_GetShape(index);
	if (shape == nullptr)
		return xatlas::AddMeshError::Error;

	const tinyobj::mesh_t& objMesh = shape->mesh;

	xatlas::UvMeshDecl meshDecl;
	meshDecl.faceMaterialData = (const uint32_t*)objMesh.material_ids.data();
	meshDecl.vertexCount = (int)objMesh.texcoords.size() / 2;
	meshDecl.vertexUvData = objMesh.texcoords.data();
	meshDecl.vertexStride = sizeof(float) * 2;
	meshDecl.indexCount = (int)objMesh.indices.size();
	meshDecl.indexData = objMesh.indices.data();
	meshDecl.indexFormat = xatlas::IndexFormat::UInt32;

	return xatlas::AddUvMesh(atlas, meshDecl);
}

void XAtlas_Generate(const xatlas::ChartOptions& chart_options, const xatlas::PackOptions& pack_options)
{
	xatlas::Generate(atlas, chart_options, pack_options);
}

void XAtlas_ComputeCharts(const xatlas::ChartOptions& options)
{
	xatlas::ComputeCharts(atlas, options);
}

void XAtlas_PackCharts(const xatlas::PackOptions& options)
{
	xatlas::PackCharts(atlas, options);
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

BOOL XAtlas_SaveAllMeshsObj(const char* filename)
{
	FILE* file;
	FOPEN(file, filename, "w");
	if (!file)
		return FALSE;
		
	uint32_t firstVertex = 0;
	for (uint32_t i = 0; i < atlas->meshCount; i++)
	{
		const xatlas::Mesh& mesh = atlas->meshes[i];

		tinyobj::shape_t* shape = ObjLoader_GetShape(i);
		if (shape == nullptr)
			continue;

		for (uint32_t v = 0; v < mesh.vertexCount; v++)
		{

			const xatlas::Vertex& vertex = mesh.vertexArray[v];
			const float* pos = &shape->mesh.positions[vertex.xref * 3];

			fprintf(file, "v %g %g %g\n", pos[0], pos[1], pos[2]);

			if (!shape->mesh.normals.empty())
			{
				const float* normal = &shape->mesh.normals[vertex.xref * 3];
				fprintf(file, "vn %g %g %g\n", normal[0], normal[1], normal[2]);
			}

			fprintf(file, "vt %g %g\n", vertex.uv[0] / atlas->width, vertex.uv[1] / atlas->height);
		}

		fprintf(file, "o %s\n", shape->name.c_str());
		fprintf(file, "s off\n");

		for (uint32_t f = 0; f < mesh.indexCount; f += 3)
		{
			fprintf(file, "f ");
			for (uint32_t j = 0; j < 3; j++) {
				const uint32_t index = firstVertex + mesh.indexArray[f + j] + 1; // 1-indexed
				fprintf(file, "%d/%d/%d%c", index, index, index, j == 2 ? '\n' : ' ');
			}
		}

		firstVertex += mesh.vertexCount;
	}

	fclose(file);
	return TRUE;
}

BOOL XAtlas_SaveMeshObj(int index, const char* filename)
{
	FILE* file;
	FOPEN(file, filename, "w");
	if (file == nullptr) 
		return FALSE;

	uint32_t firstVertex = 0;
	const xatlas::Mesh& mesh = atlas->meshes[index];

	tinyobj::shape_t* shape = ObjLoader_GetShape(index);
	if (shape == nullptr)
	{
		fclose(file);
		return FALSE;
	}
		
	for (uint32_t v = 0; v < mesh.vertexCount; v++)
	{

		const xatlas::Vertex& vertex = mesh.vertexArray[v];
		const float* pos = &shape->mesh.positions[vertex.xref * 3];

		fprintf(file, "v %g %g %g\n", pos[0], pos[1], pos[2]);

		if (!shape->mesh.normals.empty())
		{
			const float* normal = &shape->mesh.normals[vertex.xref * 3];
			fprintf(file, "vn %g %g %g\n", normal[0], normal[1], normal[2]);
		}

		fprintf(file, "vt %g %g\n", vertex.uv[0] / atlas->width, vertex.uv[1] / atlas->height);
	}

	fprintf(file, "o %s\n", shape->name.c_str());
	fprintf(file, "s off\n");

	for (uint32_t f = 0; f < mesh.indexCount; f += 3)
	{
		fprintf(file, "f ");
		for (uint32_t j = 0; j < 3; j++) {
			const uint32_t index = firstVertex + mesh.indexArray[f + j] + 1; // 1-indexed
			fprintf(file, "%d/%d/%d%c", index, index, index, j == 2 ? '\n' : ' ');
		}
	}

	firstVertex += mesh.vertexCount;

	fclose(file);
	return TRUE;
}

BOOL XAtlas_SaveChartImages(const char* filename, const uint8_t* background_color, const uint8_t* line_color)
{
	if (atlas->width <= 0 || atlas->height <= 0)
		return FALSE;

	std::vector<uint8_t> outputChartsImage;

	const uint32_t imageDataSize = atlas->width * atlas->height * 3;
	outputChartsImage.resize(atlas->atlasCount * imageDataSize);

	for (int i = 0; i < imageDataSize / 3; i++)
	{
		outputChartsImage[i * 3 + 0] = background_color[0];
		outputChartsImage[i * 3 + 1] = background_color[1];
		outputChartsImage[i * 3 + 2] = background_color[2];
	}

	for (uint32_t i = 0; i < atlas->meshCount; i++)
	{
		const xatlas::Mesh& mesh = atlas->meshes[i];

		// Rasterize mesh charts.
		for (uint32_t j = 0; j < mesh.chartCount; j++)
		{
			const xatlas::Chart* chart = &mesh.chartArray[j];
			uint8_t color[3];
			RandomColor(color);

			for (uint32_t k = 0; k < chart->faceCount; k++)
			{
				const uint32_t face = chart->faceArray[k];

				const uint32_t faceVertexCount = 3;
				const uint32_t faceFirstIndex = face * 3;

				int verts[255][2];
				for (uint32_t l = 0; l < faceVertexCount; l++)
				{
					const xatlas::Vertex& v = mesh.vertexArray[mesh.indexArray[faceFirstIndex + l]];
					verts[l][0] = int(v.uv[0]);
					verts[l][1] = int(v.uv[1]);
				}

				uint8_t* imageData = &outputChartsImage[chart->atlasIndex * imageDataSize];

				RasterizeTriangle(imageData, atlas->width, verts[0], verts[1], verts[2], color);

				for (uint32_t l = 0; l < faceVertexCount; l++)
					RasterizeLine(imageData, atlas->width, verts[l], verts[(l + 1) % faceVertexCount], line_color);
			}
		}
	}

	for (uint32_t i = 0; i < atlas->atlasCount; i++)
	{
		std::string name(filename);

		if (atlas->atlasCount > 1)
		{
			name = name.substr(0, name.size() - 4);
			name += std::to_string(i) + ".tga";
		}

		stbi_write_tga(name.c_str(), atlas->width, atlas->height, 3, &outputChartsImage[i * imageDataSize]);
	}

	return TRUE;
}

BOOL XAtlas_SaveMeshImages(const char* filename, const uint8_t* background_color, const uint8_t* line_color)
{
	if (atlas->width <= 0 || atlas->height <= 0)
		return FALSE;

	std::vector<uint8_t> outputTrisImage;

	const uint32_t imageDataSize = atlas->width * atlas->height * 3;
	outputTrisImage.resize(atlas->atlasCount * imageDataSize);

	for (int i = 0; i < imageDataSize / 3; i++)
	{
		outputTrisImage[i * 3 + 0] = background_color[0];
		outputTrisImage[i * 3 + 1] = background_color[1];
		outputTrisImage[i * 3 + 2] = background_color[2];
	}

	for (uint32_t i = 0; i < atlas->meshCount; i++)
	{
		const xatlas::Mesh& mesh = atlas->meshes[i];
		// Rasterize mesh triangles.
		const uint32_t faceCount = mesh.indexCount / 3;

		uint32_t faceFirstIndex = 0;
		for (uint32_t f = 0; f < faceCount; f++)
		{
			int32_t atlasIndex = -1;
			int verts[255][2];

			const uint32_t faceVertexCount = 3;

			for (uint32_t j = 0; j < faceVertexCount; j++)
			{
				const xatlas::Vertex& v = mesh.vertexArray[mesh.indexArray[faceFirstIndex + j]];
				atlasIndex = v.atlasIndex; // The same for every vertex in the face.
				verts[j][0] = int(v.uv[0]);
				verts[j][1] = int(v.uv[1]);
			}

			if (atlasIndex < 0)
				continue; // Skip faces that weren't atlased.

			uint8_t color[3];
			RandomColor(color);
			uint8_t* imageData = &outputTrisImage[atlasIndex * imageDataSize];

			RasterizeTriangle(imageData, atlas->width, verts[0], verts[1], verts[2], color);

			for (uint32_t j = 0; j < faceVertexCount; j++)
				RasterizeLine(imageData, atlas->width, verts[j], verts[(j + 1) % faceVertexCount], line_color);

			faceFirstIndex += faceVertexCount;
		}
	}

	for (uint32_t i = 0; i < atlas->atlasCount; i++)
	{
		std::string name(filename);

		if (atlas->atlasCount > 1)
		{
			name = name.substr(0, name.size() - 4);
			name += std::to_string(i) + ".tga";
		}

		stbi_write_tga(name.c_str(), atlas->width, atlas->height, 3, &outputTrisImage[i * imageDataSize]);
	}

	return TRUE;
}


