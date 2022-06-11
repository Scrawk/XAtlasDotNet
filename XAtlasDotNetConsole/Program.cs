using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

using XAtlasDotNet.Core;


string file = "gazebo";
string dir = "F:/Projects/Visual Studio Projects/XAtlasDotNet/";
string filename = dir + "Models/" + file + ".obj";

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
if (shape_count == 0)
{
    Console.WriteLine("No shapes have been created.");
    return;
}

Shape shape;
ObjLoader.GetShape(0, out shape);
Console.WriteLine("Created shape = " + shape);

XAtlas.Create();

var add_mesh_success = XAtlas.AddMesh(0);
Console.WriteLine("Added mesh = " + add_mesh_success);

var o = PackOptions.Default;
o.Resolution = 2048;

XAtlas.Generate(ChartOptions.Default, o);

Console.WriteLine("Created atlas = " + XAtlas.GetAtlasParams());

bool save_obj_success = XAtlas.SaveAllMeshsObj(file + "_mesh.obj");
Console.WriteLine("save_obj_success = " + save_obj_success);

var background_color = new byte[] { 0, 0, 0 };
var line_color = new byte[] { 255, 255, 255 };

bool save_chart_success = XAtlas.SaveChartImages(file + "_chart.tga", background_color, line_color);
Console.WriteLine("save_chart_success = " + save_chart_success);

bool save_mesh_success = XAtlas.SaveMeshImages(file + "_tri.tga", background_color, line_color);
Console.WriteLine("save_mesh_success = " + save_mesh_success);

ObjLoader.ClearBuffers();
XAtlas.Destroy();

