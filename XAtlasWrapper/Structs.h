#pragma once

#include <string>
#include <vector>

#include "tiny_obj_loader.h"


struct MeshCount 
{
    int positions;
    int normals;
    int texcoords;
    int indices;
    int vertices;
    int materials;  
    int tags;
};

struct Shape 
{
    //std::string name;
    MeshCount mesh;
};

struct AtlasParams
{
    int MeshCount;
    int Width;
    int Height;
    int AtlasCount;
    int ChartCount;
    float TexelsPerUnit;
};

/*
struct Material
{
    std::string name;

    float ambient[3];
    float diffuse[3];
    float specular[3];
    float transmittance[3];
    float emission[3];
    float shininess;
    float ior;
    float dissolve;
    int illum;

    //int dummy; // Suppress padding warning.

    //std::string ambient_texname;            // map_Ka
    //std::string diffuse_texname;            // map_Kd
    //std::string specular_texname;           // map_Ks
    //std::string specular_highlight_texname; // map_Ns
    //std::string bump_texname;               // map_bump, bump
    //std::string displacement_texname;       // disp
    //std::string alpha_texname;              // map_d

    //std::map<std::string, std::string> unknown_parameter;

    Material(tinyobj::material_t mat)
    {
        for (int i = 0; i < 3; i++)
        {
            ambient[i] = mat.ambient[i];
            diffuse[i] = mat.diffuse[i];
            specular[i] = mat.specular[i];
            transmittance[i] = mat.transmittance[i];
            emission[i] = mat.emission[i];
        }

        shininess = mat.shininess;
        ior = mat.ior;
        dissolve = mat.dissolve;
        illum = mat.illum;

    }

};

struct Tag
{
    std::string name;

    std::vector<int> intValues;
    std::vector<float> floatValues;
    std::vector<std::string> stringValues;
};
*/
