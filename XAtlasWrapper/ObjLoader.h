#pragma once

#include "XAtlasWrapper.h"
#include "Structs.h"
#include "tiny_obj_loader.h"

extern "C"
{

    XATLAS_WRAPPER_API void XAtlas_ClearBuffers();

    XATLAS_WRAPPER_API int XAtlas_GetShapeCount();

    XATLAS_WRAPPER_API int XAtlas_GetMaterialCount();

    XATLAS_WRAPPER_API void XAtlas_GetShape(int index, Shape& shape);

    XATLAS_WRAPPER_API float XAtlas_GetMeshPosition(int mesh, int index);

    XATLAS_WRAPPER_API float XAtlas_GetMeshNormal(int mesh, int index);

    XATLAS_WRAPPER_API float XAtlas_GetMeshUV(int mesh, int index);

    XATLAS_WRAPPER_API int XAtlas_GetMeshIndice(int mesh, int index);

    XATLAS_WRAPPER_API int XAtlas_GetMeshVertex(int mesh, int index);

    XATLAS_WRAPPER_API int XAtlas_GetMeshMateral(int mesh, int index);

    XATLAS_WRAPPER_API BOOL XAtlas_LoadObj(
        const char* filename, 
        const char* mtl_basepath,
        unsigned int flags);

}