#include "ObjLoader.h"

#include <string>
#include <vector>
#include <iostream>

std::vector<tinyobj::shape_t> _shapes;

std::vector<tinyobj::material_t> _materials;

void ObjLoader_ClearBuffers()
{
    _shapes.clear();
    _materials.clear();
}

int ObjLoader_GetShapeCount()
{
    return (int)_shapes.size();
}

int ObjLoader_GetMaterialCount()
{
    return (int)_materials.size();
}

void ObjLoader_GetShape(int index, Shape &shape)
{
    if (index < 0 || index >= _shapes.size())
        return;

    auto _shape = _shapes[index];

    shape.mesh.positions = (int)_shape.mesh.positions.size();
    shape.mesh.normals = (int)_shape.mesh.normals.size();
    shape.mesh.texcoords = (int)_shape.mesh.texcoords.size();
    shape.mesh.indices = (int)_shape.mesh.indices.size();
    shape.mesh.vertices = (int)_shape.mesh.num_vertices.size();
    shape.mesh.materials = (int)_shape.mesh.material_ids.size();
    shape.mesh.tags = (int)_shape.mesh.tags.size();
}

tinyobj::shape_t* ObjLoader_GetShape(int index)
{
    if (index < 0 || index >= _shapes.size())
        return nullptr;

    return &_shapes[index];
}

float ObjLoader_GetMeshPosition(int mesh, int index)
{
    if (mesh < 0 || index < 0 ||
        mesh >= _shapes.size() ||
        index >= _shapes[mesh].mesh.positions.size())
        return 0;

    return _shapes[mesh].mesh.positions[index];
}

float ObjLoader_GetMeshNormal(int mesh, int index)
{
    if (mesh < 0 || index < 0 ||
        mesh >= _shapes.size() ||
        index >= _shapes[mesh].mesh.normals.size())
        return 0;

    return _shapes[mesh].mesh.normals[index];
}

float ObjLoader_GetMeshTexcoord(int mesh, int index)
{
    if (mesh < 0 || index < 0 ||
        mesh >= _shapes.size() ||
        index >= _shapes[mesh].mesh.texcoords.size())
        return 0;

    return _shapes[mesh].mesh.texcoords[index];
}

int ObjLoader_GetMeshIndice(int mesh, int index)
{
    if (mesh < 0 || index < 0 ||
        mesh >= _shapes.size() ||
        index >= _shapes[mesh].mesh.indices.size())
        return NULL_INDEX;

    return _shapes[mesh].mesh.indices[index];
}

int ObjLoader_GetMeshVertex(int mesh, int index)
{
    if (mesh < 0 || index < 0 ||
        mesh >= _shapes.size() ||
        index >= _shapes[mesh].mesh.num_vertices.size())
        return NULL_INDEX;

    return _shapes[mesh].mesh.num_vertices[index];
}

int ObjLoader_GetMeshMateral(int mesh, int index)
{
    if (mesh < 0 || index < 0 ||
        mesh >= _shapes.size() ||
        index >= _shapes[mesh].mesh.material_ids.size())
        return NULL_INDEX;

    return _shapes[mesh].mesh.material_ids[index];
}

BOOL ObjLoader_LoadObj(
    const char* filename,
    const char* mtl_basepath,
    unsigned int flags)
{
    ObjLoader_ClearBuffers();

    std::string err;

    BOOL success = tinyobj::LoadObj(
        _shapes,
        _materials,
        err,
        filename,
        mtl_basepath,
        flags);

    return success;
}

xatlas::MeshDecl* ObjLoader_CreateMeshDecl(int index)
{
    if (index < 0 || index >= _shapes.size())
        return nullptr;

    xatlas::MeshDecl* meshDecl = new xatlas::MeshDecl();
    const tinyobj::mesh_t& objMesh = _shapes[index].mesh;

    meshDecl->vertexCount = (uint32_t)objMesh.positions.size() / 3;
    meshDecl->vertexPositionData = objMesh.positions.data();
    meshDecl->vertexPositionStride = sizeof(float) * 3;

    if (!objMesh.normals.empty()) {
        meshDecl->vertexNormalData = objMesh.normals.data();
        meshDecl->vertexNormalStride = sizeof(float) * 3;
    }
    if (!objMesh.texcoords.empty()) {
        meshDecl->vertexUvData = objMesh.texcoords.data();
        meshDecl->vertexUvStride = sizeof(float) * 2;
    }

    meshDecl->indexCount = (uint32_t)objMesh.indices.size();
    meshDecl->indexData = objMesh.indices.data();
    meshDecl->indexFormat = xatlas::IndexFormat::UInt32;

    return meshDecl;
}


