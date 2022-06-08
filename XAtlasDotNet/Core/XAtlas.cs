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
        /// <summary>
        /// 
        /// </summary>
        private const string DLL_NAME = "XAtlasWrapper.dll";

        /// <summary>
        /// 
        /// </summary>
        private const CallingConvention CDECL = CallingConvention.Cdecl;

        public static void ClearBuffers()
        {
            XAtlas_ClearBuffers();
        }

        public static int GetShapeCount()
        {
            return XAtlas_GetShapeCount();
        }

        public static int GetMaterialCount()
        {
            return XAtlas_GetMaterialCount();
        }

        public static void GetShape(int index, out Shape shape)
        {
            XAtlas_GetShape(index, out shape);  
        }

        public static bool LoadObj(
            string filename,
            uint flags)
        {
            return XAtlas_LoadObj(filename.ToCharArray(), null, flags);
        }

        public static float GetMeshPosition(int mesh, int index)
        {
            return XAtlas_GetMeshPosition(mesh, index);
        }

        public static float GetMeshNormal(int mesh, int index)
        {
            return XAtlas_GetMeshNormal(mesh, index);
        }

        public static float GetMeshUV(int mesh, int index)
        {
            return XAtlas_GetMeshUV(mesh, index);
        }

        public static int GetMeshIndice(int mesh, int index)
        {
            return XAtlas_GetMeshIndice(mesh, index);
        }

        public static int GetMeshVertex(int mesh, int index)
        {
            return XAtlas_GetMeshVertex(mesh, index);
        }

        public static int GetMeshMaterial(int mesh, int index)
        {
            return XAtlas_GetMeshMaterail(mesh, index);
        }

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern void XAtlas_ClearBuffers();

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern int XAtlas_GetShapeCount();

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern int XAtlas_GetMaterialCount();

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern void XAtlas_GetShape(int index, [Out] out Shape shape);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern float XAtlas_GetMeshPosition(int mesh, int index);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern float XAtlas_GetMeshNormal(int mesh, int index);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern float XAtlas_GetMeshUV(int mesh, int index);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern int XAtlas_GetMeshIndice(int mesh, int index);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern int XAtlas_GetMeshVertex(int mesh, int index);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern int XAtlas_GetMeshMaterail(int mesh, int index);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern bool XAtlas_LoadObj(
        char[] filename,
        char[] mtl_basepath,
        uint flags);
    }
}
