#include "ObjLoader.h"

#include <string>
#include <vector>
#include <iostream>

std::vector<tinyobj::shape_t> _shapes;

std::vector<tinyobj::material_t> _materials;

bool IsNotInShapeBounds(int index)
{
    if (index < 0 || index >= _shapes.size())
        return true;
    else
        return false;
}

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

void ObjLoader_AddShape()
{
    _shapes.push_back(tinyobj::shape_t());
}

void ObjLoader_GetShape(int index, Shape &shape)
{
    if (IsNotInShapeBounds(index))
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
    if (IsNotInShapeBounds(index))
        return nullptr;

    return &_shapes[index];
}

//-----------------------------------Positions------------------------------------------------------------------------//

float ObjLoader_GetMeshPosition(int mesh, int index)
{
    if (IsNotInShapeBounds(mesh) ||
        index < 0 || index >= _shapes[mesh].mesh.positions.size())
        return 0;

    return _shapes[mesh].mesh.positions[index];
}

BOOL ObjLoader_GetMeshPositions(int mesh_index, float* positions, int count)
{
    if (IsNotInShapeBounds(mesh_index))
        return FALSE;

    const tinyobj::mesh_t& mesh = _shapes[mesh_index].mesh;

    if (count > mesh.positions.size())
        return FALSE;

    for (int i = 0; i < count; i++)
        positions[i] = mesh.positions[i];

    return TRUE;
}

BOOL ObjLoader_SetMeshPositions(int mesh_index, float* positions, int count, BOOL append)
{
    if (IsNotInShapeBounds(mesh_index))
        return FALSE;

    tinyobj::mesh_t& mesh = _shapes[mesh_index].mesh;

    if(!append)
        mesh.positions.clear();

    for (int i = 0; i < count; i++)
        mesh.positions.push_back(positions[i]);

    return TRUE;
}

//-----------------------------------Normals------------------------------------------------------------------------//

float ObjLoader_GetMeshNormal(int mesh, int index)
{
    if (IsNotInShapeBounds(mesh) ||
        index < 0 || index >= _shapes[mesh].mesh.normals.size())
        return 0;

    return _shapes[mesh].mesh.normals[index];
}

BOOL ObjLoader_GetMeshNormals(int mesh_index, float* normals, int count)
{
    if (IsNotInShapeBounds(mesh_index))
        return FALSE;

    const tinyobj::mesh_t& mesh = _shapes[mesh_index].mesh;

    if (count > mesh.normals.size())
        return FALSE;

    for (int i = 0; i < count; i++)
        normals[i] = mesh.normals[i];

    return TRUE;
}

BOOL ObjLoader_SetMeshNormals(int mesh_index, float* normals, int count, BOOL append)
{
    if (IsNotInShapeBounds(mesh_index))
        return FALSE;

    tinyobj::mesh_t& mesh = _shapes[mesh_index].mesh;

    if (!append)
        mesh.normals.clear();

    for (int i = 0; i < count; i++)
        mesh.normals.push_back(normals[i]);

    return TRUE;
}

//-----------------------------------Texcoords------------------------------------------------------------------------//

float ObjLoader_GetMeshTexcoord(int mesh, int index)
{
    if (IsNotInShapeBounds(mesh) ||
        index < 0 || index >= _shapes[mesh].mesh.texcoords.size())
        return 0;

    return _shapes[mesh].mesh.texcoords[index];
}

BOOL ObjLoader_GetMeshTexcoords(int mesh_index, float* texcoords, int count)
{
    if (IsNotInShapeBounds(mesh_index))
        return FALSE;

    const tinyobj::mesh_t& mesh = _shapes[mesh_index].mesh;

    if (count > mesh.texcoords.size())
        return FALSE;

    for (int i = 0; i < count; i++)
        texcoords[i] = mesh.texcoords[i];

    return TRUE;
}

BOOL ObjLoader_SetMeshTexcoords(int mesh_index, float* texcoords, int count, BOOL append)
{
    if (IsNotInShapeBounds(mesh_index))
        return FALSE;

    tinyobj::mesh_t& mesh = _shapes[mesh_index].mesh;

    if (!append)
        mesh.texcoords.clear();

    for (int i = 0; i < count; i++)
        mesh.texcoords.push_back(texcoords[i]);

    return TRUE;
}

//-----------------------------------Indices------------------------------------------------------------------------//

unsigned int ObjLoader_GetMeshIndice(int mesh, int index)
{
    if (IsNotInShapeBounds(mesh) ||
        index < 0 || index >= _shapes[mesh].mesh.indices.size())
        return 0;

    return _shapes[mesh].mesh.indices[index];
}

BOOL ObjLoader_GetMeshIndices(int mesh_index, unsigned int* indices, int count)
{
    if (IsNotInShapeBounds(mesh_index))
        return FALSE;

    const tinyobj::mesh_t& mesh = _shapes[mesh_index].mesh;

    if (count > mesh.indices.size())
        return FALSE;

    for (int i = 0; i < count; i++)
        indices[i] = mesh.indices[i];

    return TRUE;
}

BOOL ObjLoader_SetMeshIndices(int mesh_index, unsigned int* indices, int count, BOOL append)
{
    if (IsNotInShapeBounds(mesh_index))
        return FALSE;

    tinyobj::mesh_t& mesh = _shapes[mesh_index].mesh;

    if (!append)
        mesh.indices.clear();

    for (int i = 0; i < count; i++)
        mesh.indices.push_back(indices[i]);

    return TRUE;
}

//-----------------------------------Vertices------------------------------------------------------------------------//

unsigned char ObjLoader_GetMeshVertex(int mesh, int index)
{
    if (IsNotInShapeBounds(mesh) ||
        index < 0 || index >= _shapes[mesh].mesh.num_vertices.size())
        return 0;

    return _shapes[mesh].mesh.num_vertices[index];
}

BOOL ObjLoader_GetMeshVertices(int mesh_index, unsigned char* vertices, int count)
{
    if (IsNotInShapeBounds(mesh_index))
        return FALSE;

    const tinyobj::mesh_t& mesh = _shapes[mesh_index].mesh;

    if (count > mesh.num_vertices.size())
        return FALSE;

    for (int i = 0; i < count; i++)
        vertices[i] = mesh.num_vertices[i];

    return TRUE;
}

BOOL ObjLoader_SetMeshVertices(int mesh_index, unsigned char* vertices, int count, BOOL append)
{
    if (IsNotInShapeBounds(mesh_index))
        return FALSE;

    tinyobj::mesh_t& mesh = _shapes[mesh_index].mesh;

    if (!append)
        mesh.num_vertices.clear();

    for (int i = 0; i < count; i++)
        mesh.num_vertices.push_back(vertices[i]);

    return TRUE;
}

//-----------------------------------Materials------------------------------------------------------------------------//

int ObjLoader_GetMeshMaterialId(int mesh, int index)
{
    if (IsNotInShapeBounds(mesh) ||
        index < 0 || index >= _shapes[mesh].mesh.material_ids.size())
        return NULL_INDEX;

    return _shapes[mesh].mesh.material_ids[index];
}

BOOL ObjLoader_GetMeshMaterialIds(int mesh_index, int* material_ids, int count)
{
    if (IsNotInShapeBounds(mesh_index))
        return FALSE;

    const tinyobj::mesh_t& mesh = _shapes[mesh_index].mesh;

    if (count > mesh.material_ids.size())
        return FALSE;

    for (int i = 0; i < count; i++)
        material_ids[i] = mesh.material_ids[i];

    return TRUE;
}

BOOL ObjLoader_SetMeshMaterialIds(int mesh_index, int* material_ids, int count, BOOL append)
{
    if (IsNotInShapeBounds(mesh_index))
        return FALSE;

    tinyobj::mesh_t& mesh = _shapes[mesh_index].mesh;

    if (!append)
        mesh.material_ids.clear();

    for (int i = 0; i < count; i++)
        mesh.material_ids.push_back(material_ids[i]);

    return TRUE;
}

//-------------------------------------------------------------------------------------------------------------------//

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


