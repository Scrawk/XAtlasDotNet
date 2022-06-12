using System;
using System.Collections.Generic;

namespace XAtlasDotNet.Core
{
    public enum LOAD_FLAGS
    {
        TRIANGULATION = (1 << 0),
        CALCULATE_NORMALS = (1 << 1)
    }

    public enum MESH_ERROR
    {
        SUCCESS,
        // Unspecified error.
        ERROR,
        // An index is >= MeshDecl vertexCount.
        INDEX_OUT_OF_RANGE,
        // Must be >= 3.
        INVALID_FACE_VERTEX_COUNT,
        // Not evenly divisible by 3 - expecting triangles.
        INVALID_INDEX_COUNT,
        // Added errors not in original xatlas.
        FAILED_TO_LOAD,
        FAILED_TO_GET_SHAPE,
        FALIED_TO_ADD_MESH,
        FAILED_TO_SAVE_MESH,
        FALIED_TO_SAVE_IMAGE
    }
}
