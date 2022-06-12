using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Linq;

[assembly: InternalsVisibleTo("XAtlasDotNetConsole")]
[assembly: InternalsVisibleTo("XAtlasDotNetTest")]

namespace XAtlasDotNet.Core
{
    public static class XAtlas
    {
        private const string DLL_NAME = "XAtlasWrapper.dll";

        private const CallingConvention CDECL = CallingConvention.Cdecl;

        private const UnmanagedType LPSTR = UnmanagedType.LPStr;

        public static void Destroy()
        {
            XAtlas_Destroy();
        }

        public static void Create()
        {
            XAtlas_Create();
        }

        public static MESH_ERROR AddMesh(int index)
        {
            return XAtlas_AddMesh(index);
        }

        public static MESH_ERROR AddUVMesh(int index)
        {
            return XAtlas_AddUVMesh(index);
        }

        public static void Generate()
        {
            XAtlas_Generate(ChartOptions.Default, PackOptions.Default);
        }

        public static void Generate(ChartOptions chart_options, PackOptions pack_options)
        {
            XAtlas_Generate(chart_options, pack_options);
        }

        public static void ComputeCharts(ChartOptions options)
        {
            XAtlas_ComputeCharts(options);
        }

        public static void PackCharts(PackOptions options)
        {
            XAtlas_PackCharts(options); 
        }

        public static AtlasParams GetAtlasParams()
        {
            return XAtlas_GetAtlasParams();  
        }

        public static bool SaveAllMeshsObj(string filename)
        {
            return XAtlas_SaveAllMeshsObj(filename); 
        }

        public static bool SaveMeshObj(int index, string filename)
        {
            return XAtlas_SaveMeshObj(index, filename);
        }

        public static bool SaveChartImages(string filename, byte[] background_color, byte[] line_color)
        {
            return XAtlas_SaveChartImages(filename, background_color, line_color);
        }

        public static bool SaveMeshImages(string filename, byte[] background_color, byte[] line_color)
        {
            return XAtlas_SaveMeshImages(filename, background_color, line_color);
        }

        public static MESH_ERROR Run(string input_filename, string output_filename)
        {
            return Run(input_filename, output_filename, ChartOptions.Default, PackOptions.Default);
        }

        public static MESH_ERROR Run(MeshDes input_mesh, string output_filename)
        {
            return Run(input_mesh, output_filename, ChartOptions.Default, PackOptions.Default);
        }

        public static MESH_ERROR Run(MeshDes input_mesh, out MeshDes output_mesh)
        {
            return Run(input_mesh, out output_mesh, ChartOptions.Default, PackOptions.Default);
        }

        public static MESH_ERROR Run(string input_filename, string output_filename, ChartOptions chart_options, PackOptions pack_options)
        {
            if (!ObjLoader.LoadObj(input_filename))
                return MESH_ERROR.FAILED_TO_LOAD;

            Create();

            var add_mesh_success = AddMesh(0);
            if (add_mesh_success != MESH_ERROR.SUCCESS)
                return MESH_ERROR.FALIED_TO_ADD_MESH;

            Generate(chart_options, pack_options);

            bool save_obj_success = SaveAllMeshsObj(output_filename);
            if (!save_obj_success)
                return MESH_ERROR.FALIED_TO_SAVE_IMAGE;

            ObjLoader.ClearBuffers();
            Destroy();

            return MESH_ERROR.SUCCESS;
        }

        public static MESH_ERROR Run(MeshDes input_mesh, string output_filename, ChartOptions chart_options, PackOptions pack_options)
        {

            ObjLoader.AddShape();

            if(input_mesh.PositionsCount != 0)
                ObjLoader.SetMeshPositions(0, input_mesh.Positions, input_mesh.PositionsCount);

            if (input_mesh.NormalsCount != 0)
                ObjLoader.SetMeshNormals(0, input_mesh.Normals, input_mesh.NormalsCount);

            if (input_mesh.TexcoordsCount != 0)
                ObjLoader.SetMeshIndices(0, input_mesh.Indices, input_mesh.IndicesCount);

            Create();

            var add_mesh_success = AddMesh(0);
            if (add_mesh_success != MESH_ERROR.SUCCESS)
                return MESH_ERROR.FALIED_TO_ADD_MESH;

            Generate(chart_options, pack_options);

            bool save_obj_success = SaveAllMeshsObj(output_filename);
            if (!save_obj_success)
                return MESH_ERROR.FALIED_TO_SAVE_IMAGE;

            ObjLoader.ClearBuffers();
            Destroy();

            return MESH_ERROR.SUCCESS;
        }

        public static MESH_ERROR Run(MeshDes input_mesh, out MeshDes output_mesh, ChartOptions chart_options, PackOptions pack_options)
        {
            output_mesh = null;
            ObjLoader.AddShape();

            if (input_mesh.PositionsCount != 0)
                ObjLoader.SetMeshPositions(0, input_mesh.Positions, input_mesh.PositionsCount);

            if (input_mesh.NormalsCount != 0)
                ObjLoader.SetMeshNormals(0, input_mesh.Normals, input_mesh.NormalsCount);

            if (input_mesh.TexcoordsCount != 0)
                ObjLoader.SetMeshIndices(0, input_mesh.Indices, input_mesh.IndicesCount);

            Create();

            var add_mesh_success = AddMesh(0);
            if (add_mesh_success != MESH_ERROR.SUCCESS)
                return MESH_ERROR.FALIED_TO_ADD_MESH;

            Generate(chart_options, pack_options);

            ObjLoader.GetShape(0, out Shape shape);

            output_mesh = new MeshDes();

            input_mesh.Positions = new float[shape.Mesh.Positions];
            ObjLoader.GetMeshPositions(0, input_mesh.Positions, input_mesh.Positions.Length);

            input_mesh.Normals = new float[shape.Mesh.Normals];
            ObjLoader.GetMeshNormals(0, input_mesh.Normals, input_mesh.Normals.Length);

            input_mesh.Texcoords = new float[shape.Mesh.Texcoords];
            ObjLoader.GetMeshTexcoords(0, input_mesh.Texcoords, input_mesh.Texcoords.Length);

            input_mesh.Indices = new uint[shape.Mesh.Indices];
            ObjLoader.GetMeshIndices(0, input_mesh.Indices, input_mesh.Indices.Length);

            ObjLoader.ClearBuffers();
            Destroy();

            return MESH_ERROR.SUCCESS;
        }

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern void XAtlas_Destroy();

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern void XAtlas_Create();

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern MESH_ERROR XAtlas_AddMesh(int index);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern MESH_ERROR XAtlas_AddUVMesh(int index);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern void XAtlas_Generate(ChartOptions chart_options, PackOptions pack_options);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern void XAtlas_ComputeCharts(ChartOptions options);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern void XAtlas_PackCharts(PackOptions options);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern AtlasParams XAtlas_GetAtlasParams();

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern bool XAtlas_SaveAllMeshsObj([MarshalAs(LPSTR)] string filename);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern bool XAtlas_SaveMeshObj(int index, [MarshalAs(LPSTR)] string filename);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern bool XAtlas_SaveChartImages([MarshalAs(LPSTR)] string filename, byte[] background_color, byte[] line_color);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern bool XAtlas_SaveMeshImages([MarshalAs(LPSTR)] string filename, byte[] background_color, byte[] line_color);
    }
}
