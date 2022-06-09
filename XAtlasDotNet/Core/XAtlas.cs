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
        public const string DLL_NAME = "XAtlasWrapper.dll";

        public const CallingConvention CDECL = CallingConvention.Cdecl;

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
    }
}
