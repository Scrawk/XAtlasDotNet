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

    XATLAS_WRAPPER_API void ObjLoader_GetShape(int index, Shape& shape);

    XATLAS_WRAPPER_API float ObjLoader_GetMeshPosition(int mesh, int index);

    XATLAS_WRAPPER_API float ObjLoader_GetMeshNormal(int mesh, int index);

    XATLAS_WRAPPER_API float ObjLoader_GetMeshTexcoord(int mesh, int index);

    XATLAS_WRAPPER_API int ObjLoader_GetMeshIndice(int mesh, int index);

    XATLAS_WRAPPER_API int ObjLoader_GetMeshVertex(int mesh, int index);

    XATLAS_WRAPPER_API int ObjLoader_GetMeshMateral(int mesh, int index);

    XATLAS_WRAPPER_API BOOL ObjLoader_LoadObj(
        const char* filename, 
        const char* mtl_basepath,
        unsigned int flags);

}

xatlas::MeshDecl* ObjLoader_CreateMeshDecl(int index);

tinyobj::shape_t* ObjLoader_GetShape(int index);