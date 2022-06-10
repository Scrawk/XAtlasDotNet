using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

using XAtlasDotNet.Core;


string dir1 = "F:/Projects/Visual Studio Projects/XAtlasDotNet/";
string dir2 = "F:/Projects/Visual Studio Projects/XAtlasDotNet/XAtlasDotNetConsole/bin/Release/net6.0/";

string filename = dir1 + "Models/gazebo.obj";
LOAD_FLAGS flags = LOAD_FLAGS.TRIANGULATION;

bool load_success = ObjLoader.LoadObj(filename, flags);
Console.WriteLine("load_success = " + load_success);

int shape_count = ObjLoader.GetShapeCount();

Shape shape;
ObjLoader.GetShape(0, out shape);

XAtlas.Create();

var error_code = XAtlas.AddMesh(0);

Console.WriteLine("Error code = " + error_code);

XAtlas.Generate();

Console.WriteLine(XAtlas.GetAtlasParams());

bool save_obj_success = XAtlas.SaveAllMeshsObj(dir2 + "example_mesh.obj");
Console.WriteLine("save_obj_success = " + save_obj_success);

bool save_chart_success = XAtlas.SaveChartImages(dir2 + "example_chart.tga");
Console.WriteLine("save_chart_success = " + save_chart_success);

bool save_mesh_success = XAtlas.SaveMeshImages(dir2 + "example_tri.tga");
Console.WriteLine("save_mesh_success = " + save_mesh_success);

ObjLoader.ClearBuffers();
XAtlas.Destroy();
