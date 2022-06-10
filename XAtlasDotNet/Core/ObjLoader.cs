using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Linq;

namespace XAtlasDotNet.Core
{
    public static class ObjLoader
    {
        private const string DLL_NAME = "XAtlasWrapper.dll";

        private const CallingConvention CDECL = CallingConvention.Cdecl;

        private const UnmanagedType LPSTR = UnmanagedType.LPStr;

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

        public static void AddShape()
        {
            ObjLoader_AddShape();
        }

        public static void GetShape(int index, out Shape shape)
        {
            ObjLoader_GetShape(index, out shape);  
        }

        public static bool LoadObj(string filename)
        {
            var flags = LOAD_FLAGS.TRIANGULATION;
            return ObjLoader_LoadObj(filename, null, (uint)flags);
        }

        //-----------------------------------Positions------------------------------------------------------------------------//

        public static float GetMeshPosition(int mesh_index, int index)
        {
            return ObjLoader_GetMeshPosition(mesh_index, index);
        }

        public static bool GetMeshPositions(int mesh_index, float[] positions, int count)
        {
            return ObjLoader_GetMeshPositions(mesh_index, positions, count);
        }

        public static bool SetMeshPositions(int mesh_index, float[] positions, int count, bool append = false)
        {
            return ObjLoader_SetMeshPositions(mesh_index, positions, count, append);
        }

        //-----------------------------------Normals------------------------------------------------------------------------//

        public static float GetMeshNormal(int mesh_index, int index)
        {
            return ObjLoader_GetMeshNormal(mesh_index, index);
        }

        public static bool GetMeshNormals(int mesh_index, float[] normals, int count)
        {
            return ObjLoader_GetMeshNormals(mesh_index, normals, count);
        }

        public static bool SetMeshNormals(int mesh_index, float[] normals, int count, bool append = false)
        {
            return ObjLoader_SetMeshNormals(mesh_index, normals, count, append);
        }

        //-----------------------------------Texcoords------------------------------------------------------------------------//

        public static float GetMeshTexcoord(int mesh_index, int index)
        {
            return ObjLoader_GetMeshTexcoord(mesh_index, index);
        }

        public static bool GetMeshTexcoords(int mesh_index, float[] texcoords, int count)
        {
            return ObjLoader_GetMeshTexcoords(mesh_index, texcoords, count);
        }

        public static bool SetMeshTexcoords(int mesh_index, float[] texcoords, int count, bool append = false)
        {
            return ObjLoader_SetMeshTexcoords(mesh_index, texcoords, count, append);
        }

        //-----------------------------------Indices------------------------------------------------------------------------//

        public static uint GetMeshIndice(int mesh_index, int index)
        {
            return ObjLoader_GetMeshIndice(mesh_index, index);
        }

        public static bool GetMeshIndices(int mesh_index, uint[] indices, int count)
        {
            return ObjLoader_GetMeshIndices(mesh_index, indices, count);
        }

        public static bool SetMeshIndices(int mesh_index, uint[] indices, int count, bool append = false)
        {
            return ObjLoader_SetMeshIndices(mesh_index, indices, count, append);
        }

        //-----------------------------------Vertices------------------------------------------------------------------------//

        public static byte GetMeshVertex(int mesh_index, int index)
        {
            return ObjLoader_GetMeshVertex(mesh_index, index);
        }

        public static bool GetMeshVertices(int mesh_index, byte[] vertices, int count)
        {
            return ObjLoader_GetMeshVertices(mesh_index, vertices, count);
        }

        public static bool SetMeshVertices(int mesh_index, byte[] vertices, int count, bool append = false)
        {
            return ObjLoader_SetMeshVertices(mesh_index, vertices, count, append);
        }

        //-----------------------------------Materials------------------------------------------------------------------------//

        public static int GetMeshMaterialId(int mesh_index, int index)
        {
            return ObjLoader_GetMeshMaterialId(mesh_index, index);
        }

        public static bool GetMeshMaterialIds(int mesh_index, int[] material_id, int count)
        {
            return ObjLoader_GetMeshMaterialIds(mesh_index, material_id, count);
        }

        public static bool SetMeshMaterialIds(int mesh_index, int[] material_id, int count, bool append = false)
        {
            return ObjLoader_SetMeshMaterialIds(mesh_index, material_id, count, append);
        }

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ///                                    EXTERN FUNCTIONS                                                            ///
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern void ObjLoader_ClearBuffers();

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern int ObjLoader_GetShapeCount();

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern int ObjLoader_GetMaterialCount();

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern void ObjLoader_AddShape();

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern void ObjLoader_GetShape(int index, [Out] out Shape shape);

        //-----------------------------------Positions------------------------------------------------------------------------//

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern float ObjLoader_GetMeshPosition(int mesh_index, int index);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern bool ObjLoader_GetMeshPositions(int mesh_index, [Out] float[] positions, int count);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern bool ObjLoader_SetMeshPositions(int mesh_index, float[] positions, int count, bool append);

        //-----------------------------------Normals--------------------------------------------------------------------------//

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern float ObjLoader_GetMeshNormal(int mesh_index, int index);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern bool ObjLoader_GetMeshNormals(int mesh_index, [Out] float[] normals, int count);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern bool ObjLoader_SetMeshNormals(int mesh_index, float[] normals, int count, bool append);

        //-----------------------------------Texcoords------------------------------------------------------------------------//

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern float ObjLoader_GetMeshTexcoord(int mesh_index, int index);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern bool ObjLoader_GetMeshTexcoords(int mesh_index, [Out] float[] texcoords, int count);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern bool ObjLoader_SetMeshTexcoords(int mesh_index, float[] texcoords, int count, bool append);

        //-----------------------------------Indices------------------------------------------------------------------------//

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern uint ObjLoader_GetMeshIndice(int mesh_index, int index);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern bool ObjLoader_GetMeshIndices(int mesh_index, [Out] uint[] indices, int count);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern bool ObjLoader_SetMeshIndices(int mesh_index, uint[] indices, int count, bool append);

        //-----------------------------------Vertex---------------------------------------------------------------------------//

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern byte ObjLoader_GetMeshVertex(int mesh_index, int index);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern bool ObjLoader_GetMeshVertices(int mesh_index, [Out] byte[] vertices, int count);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern bool ObjLoader_SetMeshVertices(int mesh_index, byte[] vertices, int count, bool append);

        //-----------------------------------MATERIALS------------------------------------------------------------------------//

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern int ObjLoader_GetMeshMaterialId(int mesh_index, int index);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern bool ObjLoader_GetMeshMaterialIds(int mesh_index, [Out] int[] material_ids, int count);

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern bool ObjLoader_SetMeshMaterialIds(int mesh_index, int[] material_ids, int count, bool append);

        //-------------------------------------------------------------------------------------------------------------------//

        [DllImport(DLL_NAME, CallingConvention = CDECL)]
        private static extern bool ObjLoader_LoadObj(
        [MarshalAs(LPSTR)] string filename,
        [MarshalAs(LPSTR)] string mtl_basepath,
        uint flags);
    }
}
