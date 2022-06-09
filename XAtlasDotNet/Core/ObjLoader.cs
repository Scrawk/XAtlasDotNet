using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Linq;

namespace XAtlasDotNet.Core
{
    public static class ObjLoader
    {

        public static void ClearBuffers()
        {
            ObjLoader_ClearBuffers();
        }

        public static int GetShapeCount()
        {
            return ObjLoader_GetShapeCount();
        }

        public static int GetMaterialCount()
        {
            return ObjLoader_GetMaterialCount();
        }

        public static void GetShape(int index, out Shape shape)
        {
            ObjLoader_GetShape(index, out shape);  
        }

        public static bool LoadObj(
            string filename,
            LOAD_FLAGS flags)
        {
            flags |= LOAD_FLAGS.TRIANGULATION;

            return ObjLoader_LoadObj(filename.ToCharArray(), null, (uint)flags);
        }

        public static float GetMeshPosition(int mesh, int index)
        {
            return ObjLoader_GetMeshPosition(mesh, index);
        }

        public static float GetMeshNormal(int mesh, int index)
        {
            return ObjLoader_GetMeshNormal(mesh, index);
        }

        public static float GetMeshTexcoord(int mesh, int index)
        {
            return ObjLoader_GetMeshTexcoord(mesh, index);
        }

        public static int GetMeshIndice(int mesh, int index)
        {
            return ObjLoader_GetMeshIndice(mesh, index);
        }

        public static int GetMeshVertex(int mesh, int index)
        {
            return ObjLoader_GetMeshVertex(mesh, index);
        }

        public static int GetMeshMaterial(int mesh, int index)
        {
            return ObjLoader_GetMeshMaterail(mesh, index);
        }

        [DllImport(XAtlas.DLL_NAME, CallingConvention = XAtlas.CDECL)]
        private static extern void ObjLoader_ClearBuffers();

        [DllImport(XAtlas.DLL_NAME, CallingConvention = XAtlas.CDECL)]
        private static extern int ObjLoader_GetShapeCount();

        [DllImport(XAtlas.DLL_NAME, CallingConvention = XAtlas.CDECL)]
        private static extern int ObjLoader_GetMaterialCount();

        [DllImport(XAtlas.DLL_NAME, CallingConvention = XAtlas.CDECL)]
        private static extern void ObjLoader_GetShape(int index, [Out] out Shape shape);

        [DllImport(XAtlas.DLL_NAME, CallingConvention = XAtlas.CDECL)]
        private static extern float ObjLoader_GetMeshPosition(int mesh, int index);

        [DllImport(XAtlas.DLL_NAME, CallingConvention = XAtlas.CDECL)]
        private static extern float ObjLoader_GetMeshNormal(int mesh, int index);

        [DllImport(XAtlas.DLL_NAME, CallingConvention = XAtlas.CDECL)]
        private static extern float ObjLoader_GetMeshTexcoord(int mesh, int index);

        [DllImport(XAtlas.DLL_NAME, CallingConvention = XAtlas.CDECL)]
        private static extern int ObjLoader_GetMeshIndice(int mesh, int index);

        [DllImport(XAtlas.DLL_NAME, CallingConvention = XAtlas.CDECL)]
        private static extern int ObjLoader_GetMeshVertex(int mesh, int index);

        [DllImport(XAtlas.DLL_NAME, CallingConvention = XAtlas.CDECL)]
        private static extern int ObjLoader_GetMeshMaterail(int mesh, int index);

        [DllImport(XAtlas.DLL_NAME, CallingConvention = XAtlas.CDECL)]
        private static extern bool ObjLoader_LoadObj(
        char[] filename,
        char[] mtl_basepath,
        uint flags);
    }
}
