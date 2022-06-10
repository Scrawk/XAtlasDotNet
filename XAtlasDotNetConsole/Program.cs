using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

using XAtlasDotNet.Core;


string dir = "F:/Projects/Visual Studio Projects/XAtlasDotNet/";
string filename = dir + "Models/elephant.obj";

bool load_success = ObjLoader.LoadObj(filename);
Console.WriteLine("load_success = " + load_success);

int shape_count = ObjLoader.GetShapeCount();

Shape shape;
ObjLoader.GetShape(0, out shape);

Console.WriteLine("shape = " + shape);
Console.WriteLine();

XAtlas.Create();

var error_code = XAtlas.AddMesh(0);
Console.WriteLine("Error code = " + error_code);

XAtlas.Generate();

Console.WriteLine(XAtlas.GetAtlasParams());

bool save_obj_success = XAtlas.SaveAllMeshsObj("example_mesh.obj");
Console.WriteLine("save_obj_success = " + save_obj_success);

bool save_chart_success = XAtlas.SaveChartImages("example_chart.tga");
Console.WriteLine("save_chart_success = " + save_chart_success);

bool save_mesh_success = XAtlas.SaveMeshImages("example_tri.tga");
Console.WriteLine("save_mesh_success = " + save_mesh_success);

ObjLoader.ClearBuffers();
XAtlas.Destroy();

