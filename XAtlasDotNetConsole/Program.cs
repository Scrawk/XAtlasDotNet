using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

using XAtlasDotNet.Core;

string dir = "F:/Projects/Visual Studio Projects/XAtlasDotNet/";
string filename = dir + "Models/gazebo.obj";

if(!ObjLoader.LoadObj(filename))
{
    Console.WriteLine("Failed to load obj file " + filename);
    return;
}
else
{
    Console.WriteLine("Loaded obj file " + filename);
}

int shape_count = ObjLoader.GetShapeCount();

Shape shape;
ObjLoader.GetShape(0, out shape);
Console.WriteLine("Created shape = " + shape);

XAtlas.Create();

var add_mesh_success = XAtlas.AddMesh(0);
Console.WriteLine("Added mesh = " + add_mesh_success);

XAtlas.Generate();

//XAtlas.ComputeCharts(ChartOptions.Default);
//XAtlas.PackCharts(PackOptions.Default);

Console.WriteLine("Created atlas = " + XAtlas.GetAtlasParams());

bool save_obj_success = XAtlas.SaveAllMeshsObj("example_mesh.obj");
Console.WriteLine("save_obj_success = " + save_obj_success);

bool save_chart_success = XAtlas.SaveChartImages("example_chart.tga");
Console.WriteLine("save_chart_success = " + save_chart_success);

bool save_mesh_success = XAtlas.SaveMeshImages("example_tri.tga");
Console.WriteLine("save_mesh_success = " + save_mesh_success);

ObjLoader.ClearBuffers();
XAtlas.Destroy();

