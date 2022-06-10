using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Linq;

[assembly: InternalsVisibleTo("OpenGLDotNetConsole")]
[assembly: InternalsVisibleTo("OpenGLDotNetTest")]

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

        public static void Generate()
        {
            XAtlas_Generate();
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

        public static bool SaveChartImages(string filename)
        {
            return XAtlas_SaveChartImages(filename);
        }

        public static bool SaveMeshImages(string filename)
        {
            return XAtlas_SaveMeshImages(filename);
        }

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern void XAtlas_Destroy();

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern void XAtlas_Create();

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern MESH_ERROR XAtlas_AddMesh(int index);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern void XAtlas_Generate();

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern AtlasParams XAtlas_GetAtlasParams();

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern bool XAtlas_SaveAllMeshsObj([MarshalAs(LPSTR)] string filename);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern bool XAtlas_SaveMeshObj(int index, [MarshalAs(LPSTR)] string filename);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern bool XAtlas_SaveChartImages([MarshalAs(LPSTR)] string filename);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern bool XAtlas_SaveMeshImages([MarshalAs(LPSTR)] string filename);
    }
}
