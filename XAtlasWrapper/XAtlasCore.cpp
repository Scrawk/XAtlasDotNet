
#include "XAtlasCore.h"
#include "ObjLoader.h"
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

void RandomColor(uint8_t* color)
{
	for (int i = 0; i < 3; i++)
		color[i] = uint8_t((rand() % 255 + 192) * 0.5f);
}

void SetPixel(uint8_t* dest, int destWidth, int x, int y, const uint8_t* color)
{
	uint8_t* pixel = &dest[x * 3 + y * (destWidth * 3)];
	pixel[0] = color[0];
	pixel[1] = color[1];
	pixel[2] = color[2];
}

// https://github.com/miloyip/line/blob/master/line_bresenham.c
// License: public domain.
void RasterizeLine(uint8_t* dest, int destWidth, const int* p1, const int* p2, const uint8_t* color)
{
	const int dx = abs(p2[0] - p1[0]), sx = p1[0] < p2[0] ? 1 : -1;
	const int dy = abs(p2[1] - p1[1]), sy = p1[1] < p2[1] ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int current[2];
	current[0] = p1[0];
	current[1] = p1[1];
	while (SetPixel(dest, destWidth, current[0], current[1], color), current[0] != p2[0] || current[1] != p2[1])
	{
		const int e2 = err;
		if (e2 > -dx) { err -= dy; current[0] += sx; }
		if (e2 < dy) { err += dx; current[1] += sy; }
	}
}

/*
https://github.com/ssloy/tinyrenderer/wiki/Lesson-2:-Triangle-rasterization-and-back-face-culling
Copyright Dmitry V. Sokolov
This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it freely,
subject to the following restrictions:
1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/
static void RasterizeTriangle(uint8_t* dest, int destWidth, const int* t0, const int* t1, const int* t2, const uint8_t* color)
{
	if (t0[1] > t1[1]) std::swap(t0, t1);
	if (t0[1] > t2[1]) std::swap(t0, t2);
	if (t1[1] > t2[1]) std::swap(t1, t2);
	int total_height = t2[1] - t0[1];
	for (int i = 0; i < total_height; i++) {
		bool second_half = i > t1[1] - t0[1] || t1[1] == t0[1];
		int segment_height = second_half ? t2[1] - t1[1] : t1[1] - t0[1];
		float alpha = (float)i / total_height;
		float beta = (float)(i - (second_half ? t1[1] - t0[1] : 0)) / segment_height;
		int A[2], B[2];
		for (int j = 0; j < 2; j++) {
			A[j] = int(t0[j] + (t2[j] - t0[j]) * alpha);
			B[j] = int(second_half ? t1[j] + (t2[j] - t1[j]) * beta : t0[j] + (t1[j] - t0[j]) * beta);
		}
		if (A[0] > B[0]) std::swap(A, B);
		for (int j = A[0]; j <= B[0]; j++)
			SetPixel(dest, destWidth, j, t0[1] + i, color);
	}
}

BOOL XAtlas_SaveChartImages(const char* filename)
{
	if (atlas->width <= 0 || atlas->height <= 0)
		return FALSE;

	std::vector<uint8_t> outputChartsImage;

	const uint32_t imageDataSize = atlas->width * atlas->height * 3;
	outputChartsImage.resize(atlas->atlasCount * imageDataSize);
	const uint8_t white[] = { 255, 255, 255 };

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
					RasterizeLine(imageData, atlas->width, verts[l], verts[(l + 1) % faceVertexCount], white);
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

BOOL XAtlas_SaveMeshImages(const char* filename)
{
	if (atlas->width <= 0 || atlas->height <= 0)
		return FALSE;

	std::vector<uint8_t> outputTrisImage;

	const uint32_t imageDataSize = atlas->width * atlas->height * 3;
	outputTrisImage.resize(atlas->atlasCount * imageDataSize);

	for (uint32_t i = 0; i < atlas->meshCount; i++)
	{
		const xatlas::Mesh& mesh = atlas->meshes[i];
		// Rasterize mesh triangles.
		const uint8_t white[] = { 255, 255, 255 };

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
				RasterizeLine(imageData, atlas->width, verts[j], verts[(j + 1) % faceVertexCount], white);

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


