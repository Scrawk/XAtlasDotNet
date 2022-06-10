
#include <mutex>
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <iostream>

#include "stb_image_write.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4201)
#endif
#include "tiny_obj_loader.h"
#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include "xatlas.h"

#ifdef _MSC_VER
#define FOPEN(_file, _filename, _mode) { if (fopen_s(&_file, _filename, _mode) != 0) _file = NULL; }
#define STRICMP _stricmp
#else
#define FOPEN(_file, _filename, _mode) _file = fopen(_filename, _mode)
#include <strings.h>
#define STRICMP strcasecmp
#endif

#define OBJ_TRIANGULATE 1 // Pass tinyobj::triangulation flag to tinyobjloader and treat all geometry as triangles.

static bool s_verbose = false;

class Stopwatch
{
public:
	Stopwatch() { reset(); }
	void reset() { m_start = clock(); }
	double elapsed() const { return (clock() - m_start) * 1000.0 / CLOCKS_PER_SEC; }
private:
	clock_t m_start;
};

static int Print(const char* format, ...)
{
	va_list arg;
	va_start(arg, format);
	printf("\r"); // Clear progress text.
	const int result = vprintf(format, arg);
	va_end(arg);
	return result;
}

// May be called from any thread.
static bool ProgressCallback(xatlas::ProgressCategory category, int progress, void* userData)
{
	// Don't interupt verbose printing.
	if (s_verbose)
		return true;
	Stopwatch* stopwatch = (Stopwatch*)userData;
	static std::mutex progressMutex;
	std::unique_lock<std::mutex> lock(progressMutex);
	if (progress == 0)
		stopwatch->reset();
	printf("\r   %s [", xatlas::StringForEnum(category));
	for (int i = 0; i < 10; i++)
		printf(progress / ((i + 1) * 10) ? "*" : " ");
	printf("] %d%%", progress);
	fflush(stdout);
	if (progress == 100)
		printf("\n      %.2f seconds (%g ms) elapsed\n", stopwatch->elapsed() / 1000.0, stopwatch->elapsed());
	return true;
}

static void RandomColor(uint8_t* color)
{
	for (int i = 0; i < 3; i++)
		color[i] = uint8_t((rand() % 255 + 192) * 0.5f);
}

static void SetPixel(uint8_t* dest, int destWidth, int x, int y, const uint8_t* color)
{
	uint8_t* pixel = &dest[x * 3 + y * (destWidth * 3)];
	pixel[0] = color[0];
	pixel[1] = color[1];
	pixel[2] = color[2];
}

// https://github.com/miloyip/line/blob/master/line_bresenham.c
// License: public domain.
static void RasterizeLine(uint8_t* dest, int destWidth, const int* p1, const int* p2, const uint8_t* color)
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
1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
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

#if !OBJ_TRIANGULATE
//  public-domain code by Darel Rex Finley, 2007
// http://alienryderflex.com/polygon_fill/
static void RasterizePolygon(uint8_t* dest, int destWidth, int vertices[][2], const int vertexCount, const uint8_t* color)
{
	int IMAGE_TOP = INT_MAX, IMAGE_BOT = 0, IMAGE_LEFT = INT_MAX, IMAGE_RIGHT = 0;
	for (int i = 0; i < vertexCount; i++) {
		const int* vertex = vertices[i];
		IMAGE_TOP = vertex[1] < IMAGE_TOP ? vertex[1] : IMAGE_TOP;
		IMAGE_BOT = vertex[1] > IMAGE_BOT ? vertex[1] : IMAGE_BOT;
		IMAGE_LEFT = vertex[0] < IMAGE_LEFT ? vertex[0] : IMAGE_LEFT;
		IMAGE_RIGHT = vertex[0] > IMAGE_RIGHT ? vertex[0] : IMAGE_RIGHT;
	}
	int  nodes, nodeX[255], pixelX, pixelY, i, j, swap;
	//  Loop through the rows of the image.
	for (pixelY = IMAGE_TOP; pixelY < IMAGE_BOT; pixelY++) {
		//  Build a list of nodes.
		nodes = 0; j = vertexCount - 1;
		for (i = 0; i < vertexCount; i++) {
			if (vertices[i][1] < (double)pixelY && vertices[j][1] >= (double)pixelY || vertices[j][1] < (double)pixelY && vertices[i][1] >= (double)pixelY) {
				nodeX[nodes++] = (int)(vertices[i][0] + (pixelY - vertices[i][1]) / (vertices[j][1] - vertices[i][1]) * (vertices[j][0] - vertices[i][0]));
			}
			j = i;
		}
		//  Sort the nodes, via a simple �Bubble� sort.
		i = 0;
		while (i < nodes - 1) {
			if (nodeX[i] > nodeX[i + 1]) {
				swap = nodeX[i]; nodeX[i] = nodeX[i + 1]; nodeX[i + 1] = swap; if (i) i--;
			}
			else {
				i++;
			}
		}
		//  Fill the pixels between node pairs.
		for (i = 0; i < nodes; i += 2) {
			if (nodeX[i] >= IMAGE_RIGHT)
				break;
			if (nodeX[i + 1] > IMAGE_LEFT) {
				if (nodeX[i] < IMAGE_LEFT)
					nodeX[i] = IMAGE_LEFT;
				if (nodeX[i + 1] > IMAGE_RIGHT)
					nodeX[i + 1] = IMAGE_RIGHT;
				for (pixelX = nodeX[i]; pixelX < nodeX[i + 1]; pixelX++)
					SetPixel(dest, destWidth, pixelX, pixelY, color);
			}
		}
	}
}
#endif

int main(int argc, char* argv[])
{

	std::string filename = "F:/Projects/Visual Studio Projects/XAtlasDotNet/Models/gazebo.obj";

	/*
	if (argc < 2) 
	{
		printf("Usage: %s input_file.obj [options]\n", argv[0]);
		printf("  Options:\n");
		printf("    -verbose\n");
		return 1;
	}
	*/

	//s_verbose = (argc >= 3 && STRICMP(argv[2], "-verbose") == 0);
	s_verbose = true;
	
	// Load object file.
	printf("Loading '%s'...\n", filename.c_str());
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;
	unsigned int flags = 0;

#if OBJ_TRIANGULATE
	flags = tinyobj::triangulation;
#endif

	if (!tinyobj::LoadObj(shapes, materials, err, filename.c_str(), NULL, flags)) {
		printf("Error: %s\n", err.c_str());
		return EXIT_FAILURE;
	}

	if (shapes.size() == 0) {
		printf("Error: no shapes in obj file\n");
		return EXIT_FAILURE;
	}

	printf("   %d shapes\n", (int)shapes.size());
	// Create empty atlas.
	xatlas::SetPrint(Print, s_verbose);
	xatlas::Atlas* atlas = xatlas::Create();
	// Set progress callback.
	Stopwatch globalStopwatch, stopwatch;
	xatlas::SetProgressCallback(atlas, ProgressCallback, &stopwatch);
	// Add meshes to atlas.
	uint32_t totalVertices = 0, totalFaces = 0;

	for (int i = 0; i < (int)shapes.size(); i++) 
	{
		const tinyobj::mesh_t& objMesh = shapes[i].mesh;
		xatlas::MeshDecl meshDecl;
		meshDecl.vertexCount = (uint32_t)objMesh.positions.size() / 3;
		meshDecl.vertexPositionData = objMesh.positions.data();
		meshDecl.vertexPositionStride = sizeof(float) * 3;
		if (!objMesh.normals.empty()) {
			meshDecl.vertexNormalData = objMesh.normals.data();
			meshDecl.vertexNormalStride = sizeof(float) * 3;
		}
		if (!objMesh.texcoords.empty()) {
			meshDecl.vertexUvData = objMesh.texcoords.data();
			meshDecl.vertexUvStride = sizeof(float) * 2;
		}
		meshDecl.indexCount = (uint32_t)objMesh.indices.size();
		meshDecl.indexData = objMesh.indices.data();
		meshDecl.indexFormat = xatlas::IndexFormat::UInt32;

#if !OBJ_TRIANGULATE
		if (objMesh.num_vertices.size() != objMesh.indices.size() / 3) {
			meshDecl.faceVertexCount = objMesh.num_vertices.data();
			meshDecl.faceCount = (uint32_t)objMesh.num_vertices.size();
		}
#endif

		xatlas::AddMeshError error = xatlas::AddMesh(atlas, meshDecl, (uint32_t)shapes.size());
		if (error != xatlas::AddMeshError::Success) {
			xatlas::Destroy(atlas);
			printf("\rError adding mesh %d '%s': %s\n", i, shapes[i].name.c_str(), xatlas::StringForEnum(error));
			return EXIT_FAILURE;
		}
		totalVertices += meshDecl.vertexCount;
		if (meshDecl.faceCount > 0)
			totalFaces += meshDecl.faceCount;
		else
			totalFaces += meshDecl.indexCount / 3; // Assume triangles if MeshDecl::faceCount not specified.
	}

	xatlas::AddMeshJoin(atlas); // Not necessary. Only called here so geometry totals are printed after the AddMesh progress indicator.
	printf("   %u total vertices\n", totalVertices);
	printf("   %u total faces\n", totalFaces);
	// Generate atlas.
	printf("Generating atlas\n");
	xatlas::Generate(atlas);
	printf("   %d charts\n", atlas->chartCount);
	printf("   %d atlases\n", atlas->atlasCount);
	for (uint32_t i = 0; i < atlas->atlasCount; i++)
		printf("      %d: %0.2f%% utilization\n", i, atlas->utilization[i] * 100.0f);
	printf("   %ux%u resolution\n", atlas->width, atlas->height);
	totalVertices = 0;

	for (uint32_t i = 0; i < atlas->meshCount; i++) {
		const xatlas::Mesh& mesh = atlas->meshes[i];
		totalVertices += mesh.vertexCount;
		// Input and output index counts always match.
		assert(mesh.indexCount == (uint32_t)shapes[i].mesh.indices.size());
	}

	printf("   %u total vertices\n", totalVertices);
	printf("%.2f seconds (%g ms) elapsed total\n", globalStopwatch.elapsed() / 1000.0, globalStopwatch.elapsed());
	// Write meshes.
	const char* modelFilename = "example_output.obj";
	printf("Writing '%s'...\n", modelFilename);
	FILE* file;
	FOPEN(file, modelFilename, "w");

	if (file) 
	{
		uint32_t firstVertex = 0;
		for (uint32_t i = 0; i < atlas->meshCount; i++) 
		{
			const xatlas::Mesh& mesh = atlas->meshes[i];
			for (uint32_t v = 0; v < mesh.vertexCount; v++) 
			{
				const xatlas::Vertex& vertex = mesh.vertexArray[v];
				const float* pos = &shapes[i].mesh.positions[vertex.xref * 3];
				fprintf(file, "v %g %g %g\n", pos[0], pos[1], pos[2]);

				if (!shapes[i].mesh.normals.empty()) 
				{
					const float* normal = &shapes[i].mesh.normals[vertex.xref * 3];
					fprintf(file, "vn %g %g %g\n", normal[0], normal[1], normal[2]);
				}

				fprintf(file, "vt %g %g\n", vertex.uv[0] / atlas->width, vertex.uv[1] / atlas->height);
			}

			fprintf(file, "o %s\n", shapes[i].name.c_str());
			fprintf(file, "s off\n");

#if !OBJ_TRIANGULATE
			auto faceCount = (const uint32_t)shapes[i].mesh.num_vertices.size();
			uint32_t currentIndex = 0;
			for (uint32_t f = 0; f < faceCount; f++) {
				fprintf(file, "f ");
				auto faceVertexCount = (const uint32_t)shapes[i].mesh.num_vertices[f];
				for (uint32_t j = 0; j < faceVertexCount; j++) {
					const uint32_t index = firstVertex + mesh.indexArray[currentIndex++] + 1; // 1-indexed
					fprintf(file, "%d/%d/%d%c", index, index, index, j == (faceVertexCount - 1) ? '\n' : ' ');
				}
			}
#else
			for (uint32_t f = 0; f < mesh.indexCount; f += 3) {
				fprintf(file, "f ");
				for (uint32_t j = 0; j < 3; j++) {
					const uint32_t index = firstVertex + mesh.indexArray[f + j] + 1; // 1-indexed
					fprintf(file, "%d/%d/%d%c", index, index, index, j == 2 ? '\n' : ' ');
				}
			}
#endif
			firstVertex += mesh.vertexCount;
		}
		fclose(file);
	}

	if (atlas->width > 0 && atlas->height > 0) {
		printf("Rasterizing result...\n");
		// Dump images.
		std::vector<uint8_t> outputTrisImage, outputChartsImage;
		const uint32_t imageDataSize = atlas->width * atlas->height * 3;
		outputTrisImage.resize(atlas->atlasCount * imageDataSize);
		outputChartsImage.resize(atlas->atlasCount * imageDataSize);
		for (uint32_t i = 0; i < atlas->meshCount; i++) {
			const xatlas::Mesh& mesh = atlas->meshes[i];
			// Rasterize mesh triangles.
			const uint8_t white[] = { 255, 255, 255 };
#if OBJ_TRIANGULATE
			const uint32_t faceCount = mesh.indexCount / 3;
#else
			auto faceCount = (const uint32_t)shapes[i].mesh.num_vertices.size();
#endif
			uint32_t faceFirstIndex = 0;
			for (uint32_t f = 0; f < faceCount; f++) {
				int32_t atlasIndex = -1;
				int verts[255][2];

#if OBJ_TRIANGULATE
				const uint32_t faceVertexCount = 3;
#else
				const uint32_t faceVertexCount = shapes[i].mesh.num_vertices[f];
#endif

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

#if OBJ_TRIANGULATE
				RasterizeTriangle(imageData, atlas->width, verts[0], verts[1], verts[2], color);
#else
				if (faceVertexCount == 3)
					RasterizeTriangle(imageData, atlas->width, verts[0], verts[1], verts[2], color);
				else
					RasterizePolygon(imageData, atlas->width, verts, (int)faceVertexCount, color);
#endif
				for (uint32_t j = 0; j < faceVertexCount; j++)
					RasterizeLine(imageData, atlas->width, verts[j], verts[(j + 1) % faceVertexCount], white);
				faceFirstIndex += faceVertexCount;
			}
			// Rasterize mesh charts.
			for (uint32_t j = 0; j < mesh.chartCount; j++) 
			{
				const xatlas::Chart* chart = &mesh.chartArray[j];
				uint8_t color[3];
				RandomColor(color);

				for (uint32_t k = 0; k < chart->faceCount; k++) 
				{
					const uint32_t face = chart->faceArray[k];

#if OBJ_TRIANGULATE
					const uint32_t faceVertexCount = 3;
					faceFirstIndex = face * 3;
#else
					const uint32_t faceVertexCount = shapes[i].mesh.num_vertices[face];
					faceFirstIndex = 0;
					for (uint32_t l = 0; l < face; l++)
						faceFirstIndex += shapes[i].mesh.num_vertices[l];
#endif

					int verts[255][2];
					for (uint32_t l = 0; l < faceVertexCount; l++) 
					{
						const xatlas::Vertex& v = mesh.vertexArray[mesh.indexArray[faceFirstIndex + l]];
						verts[l][0] = int(v.uv[0]);
						verts[l][1] = int(v.uv[1]);
					}

					uint8_t* imageData = &outputChartsImage[chart->atlasIndex * imageDataSize];

#if OBJ_TRIANGULATE
					RasterizeTriangle(imageData, atlas->width, verts[0], verts[1], verts[2], color);
#else
					if (faceVertexCount == 3)
						RasterizeTriangle(imageData, atlas->width, verts[0], verts[1], verts[2], color);
					else
						RasterizePolygon(imageData, atlas->width, verts, (int)faceVertexCount, color);
#endif

					for (uint32_t l = 0; l < faceVertexCount; l++)
						RasterizeLine(imageData, atlas->width, verts[l], verts[(l + 1) % faceVertexCount], white);
				}
			}
		}

		for (uint32_t i = 0; i < atlas->atlasCount; i++) 
		{
			char filename[256];
			snprintf(filename, sizeof(filename), "example_tris%02u.tga", i);
			printf("Writing '%s'...\n", filename);
			stbi_write_tga(filename, atlas->width, atlas->height, 3, &outputTrisImage[i * imageDataSize]);
			snprintf(filename, sizeof(filename), "example_charts%02u.tga", i);
			printf("Writing '%s'...\n", filename);
			stbi_write_tga(filename, atlas->width, atlas->height, 3, &outputChartsImage[i * imageDataSize]);
		}
	}

	// Cleanup.
	xatlas::Destroy(atlas);
	printf("Done\n");
	return EXIT_SUCCESS;
}
