using System;
using System.Collections.Generic;

namespace XAtlasDotNet.Core
{
    public struct MeshCount
    {
        public int Positions;
        public int Normals;
        public int Texcoords;
        public int Indices;
        public int Vertices;
        public int Materials;   
        public int Tags;

        public override string ToString()
        {
            return string.Format("[MeshCount: positions={0}, normals={1}, texcoords={2}, indices={3}, vertices={4}, materials={5}, tags={6}]",
               Positions, Normals, Texcoords, Indices, Vertices, Materials, Tags);
        }
    }
}
