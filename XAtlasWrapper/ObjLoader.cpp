#include "ObjLoader.h"

#include <string>
#include <vector>
#include <iostream>

std::vector<tinyobj::shape_t> _shapes;

std::vector<tinyobj::material_t> _materials;

void XAtlas_ClearBuffers()
{
    _shapes.clear();
    _materials.clear();
}

int XAtlas_GetShapeCount()
{
    return (int)_shapes.size();
}

int XAtlas_GetMaterialCount()
{
    return (int)_materials.size();
}

void XAtlas_GetShape(int index, Shape &shape)
{
    auto _shape = _shapes[index];

    shape.mesh.positions = (int)_shape.mesh.positions.size();
    shape.mesh.normals = (int)_shape.mesh.normals.size();
    shape.mesh.texcoords = (int)_shape.mesh.texcoords.size();
    shape.mesh.indices = (int)_shape.mesh.indices.size();
    shape.mesh.vertices = (int)_shape.mesh.num_vertices.size();
    shape.mesh.materials = (int)_shape.mesh.material_ids.size();
    shape.mesh.tags = (int)_shape.mesh.tags.size();
}

float XAtlas_GetMeshPosition(int mesh, int index)
{
    return _shapes[mesh].mesh.positions[index];
}

float XAtlas_GetMeshNormal(int mesh, int index)
{
    return _shapes[mesh].mesh.normals[index];
}

float XAtlas_GetMeshUV(int mesh, int index)
{
    return _shapes[mesh].mesh.texcoords[index];
}

int XAtlas_GetMeshIndice(int mesh, int index)
{
    return _shapes[mesh].mesh.indices[index];
}

int XAtlas_GetMeshVertex(int mesh, int index)
{
    return _shapes[mesh].mesh.num_vertices[index];
}

int XAtlas_GetMeshMateral(int mesh, int index)
{
    return _shapes[mesh].mesh.material_ids[index];
}

BOOL XAtlas_LoadObj(
    const char* filename,
    const char* mtl_basepath,
    unsigned int flags)
{
    XAtlas_ClearBuffers();

    std::string err;

    BOOL success = tinyobj::LoadObj(
        _shapes,
        _materials,
        err,
        filename,
        mtl_basepath,
        flags);

    //std::cout << "Load obj" << std::endl;
    //std::cout << "err " << err << std::endl;

    return success;
}
