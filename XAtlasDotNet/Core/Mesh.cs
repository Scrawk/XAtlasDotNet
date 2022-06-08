using System;
using System.Collections.Generic;

namespace XAtlasDotNet.Core
{
    public struct Mesh
    {
        public int positions;
        public int normals;
        public int texcoords;
        public int indices;
        public int vertexs;
        public int materials;   
        public int tags;

        public override string ToString()
        {
            return string.Format("[Mesh: positions={0}, normals={1}, texcoords={2}, indices={3}, vertices={4}, materials={5}, tags={6}]",
               positions, normals, texcoords, indices, vertexs, materials, tags);
        }
    }
}
