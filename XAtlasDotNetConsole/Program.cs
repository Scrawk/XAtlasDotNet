using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

using XAtlasDotNet.Core;


string filename = "F:/Projects/Visual Studio Projects/XAtlasDotNet/Models/gazebo.obj";
LOAD_FLAGS flags = LOAD_FLAGS.TRIANGULATION;

bool b = ObjLoader.LoadObj(filename, flags);

int shape_count = ObjLoader.GetShapeCount();

Shape shape;
ObjLoader.GetShape(0, out shape);

XAtlas.Create();

var error_code = XAtlas.AddMesh(0);

Console.WriteLine("Error code = " + error_code);

XAtlas.Generate();

Console.WriteLine(XAtlas.GetAtlasParams());

XAtlas.Destroy();

/*
Loading 'F:/Projects/Visual Studio Projects/XAtlasDotNet/Models/gazebo.obj'...
   1 shapes
Adding mesh 0: 1568 vertices, 730 triangles
   1568 total vertices
   730 total faces
Generating atlas
Computing charts
   332 charts
      119 planar, 213 ortho, 0 LSCM, 0 piecewise
Packing 332 charts
   Estimating texelsPerUnit as 60.5763
   975x1013 resolution
   85.394188% utilization
Building output meshes
   Mesh 0: 1568 vertices, 730 triangles, 332 charts
   332 charts
   1 atlases
      0: 85.39 % utilization
   975x1013 resolution
   1568 total vertices
0.03 seconds (33 ms) elapsed total
Writing 'example_output.obj'...
Rasterizing result...
Writing 'example_tris00.tga'...
Writing 'example_charts00.tga'...
Done
*/


