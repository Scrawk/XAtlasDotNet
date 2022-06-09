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
        ERROR, // Unspecified error.
        INDEX_OUT_OF_RANGE, // An index is >= MeshDecl vertexCount.
        INVALID_FACE_VERTEX_COUNT, // Must be >= 3.
        INVALID_INDEX_COUNT // Not evenly divisible by 3 - expecting triangles.
    }
}
