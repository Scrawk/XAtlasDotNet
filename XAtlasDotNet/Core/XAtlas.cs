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
