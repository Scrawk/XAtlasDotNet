#pragma once

#include "XAtlasWrapper.h"
#include "Structs.h"
#include "tiny_obj_loader.h"
#include "xatlas.h"

extern "C"
{

    XATLAS_WRAPPER_API void ObjLoader_ClearBuffers();

    XATLAS_WRAPPER_API int ObjLoader_GetShapeCount();

    XATLAS_WRAPPER_API int ObjLoader_GetMaterialCount();

    XATLAS_WRAPPER_API void ObjLoader_AddShape();

    XATLAS_WRAPPER_API void ObjLoader_GetShape(int index, Shape& shape);

    XATLAS_WRAPPER_API float ObjLoader_GetMeshPosition(int mesh_index, int index);

    XATLAS_WRAPPER_API BOOL ObjLoader_GetMeshPositions(int mesh_index, float* positions, int count);

    XATLAS_WRAPPER_API BOOL ObjLoader_SetMeshPositions(int mesh_index, float* positions, int count, BOOL append);

    XATLAS_WRAPPER_API float ObjLoader_GetMeshNormal(int mesh_index, int index);

    XATLAS_WRAPPER_API BOOL ObjLoader_GetMeshNormals(int mesh_index, float* normals, int count);

    XATLAS_WRAPPER_API BOOL ObjLoader_SetMeshNormals(int mesh_index, float* normals, int count, BOOL append);

    XATLAS_WRAPPER_API float ObjLoader_GetMeshTexcoord(int mesh_index, int index);

    XATLAS_WRAPPER_API BOOL ObjLoader_GetMeshTexcoords(int mesh_index, float* texcoords, int count);

    XATLAS_WRAPPER_API BOOL ObjLoader_SetMeshTexcoords(int mesh_index, float* texcoords, int count, BOOL append);

    XATLAS_WRAPPER_API unsigned int ObjLoader_GetMeshIndice(int mesh_index, int index);

    XATLAS_WRAPPER_API BOOL ObjLoader_GetMeshIndices(int mesh_index, unsigned int* indices, int count);

    XATLAS_WRAPPER_API BOOL ObjLoader_SetMeshIndices(int mesh_index, unsigned int* indices, int count, BOOL append);

    XATLAS_WRAPPER_API unsigned char ObjLoader_GetMeshVertex(int mesh_index, int index);

    XATLAS_WRAPPER_API BOOL ObjLoader_GetMeshVertices(int mesh_index, unsigned char* vertices, int count);

    XATLAS_WRAPPER_API BOOL ObjLoader_SetMeshVertices(int mesh_index, unsigned char* vertices, int count, BOOL append);

    XATLAS_WRAPPER_API int ObjLoader_GetMeshMaterialId(int mesh_index, int index);

    XATLAS_WRAPPER_API BOOL ObjLoader_GetMeshMaterialIds(int mesh_index, int* material_ids, int count);

    XATLAS_WRAPPER_API BOOL ObjLoader_SetMeshMaterialIds(int mesh_index, int* material_ids, int count, BOOL append);

    XATLAS_WRAPPER_API BOOL ObjLoader_LoadObj(
        const char* filename, 
        const char* mtl_basepath,
        unsigned int flags);

}

xatlas::MeshDecl* ObjLoader_CreateMeshDecl(int index);

tinyobj::shape_t* ObjLoader_GetShape(int index);