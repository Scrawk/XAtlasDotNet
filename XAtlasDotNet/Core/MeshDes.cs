using System;
using System.Collections.Generic;

namespace XAtlasDotNet.Core
{
    public class MeshDes
    {
        public float[] Positions;

        public float[] Normals;

        public float[] Texcoords;

        public uint[] Indices;

        public int PositionsCount => Positions != null ? Positions.Length : 0;

        public int NormalsCount => Normals != null ? Normals.Length : 0;

        public int TexcoordsCount => Texcoords != null ? Texcoords.Length : 0;

        public int IndicesCount => Indices != null ? Indices.Length : 0;

        public override string ToString()
        {
            return String.Format("[MeshDes: Positions={0}, Normals={1}, Texcoords={2}, Indices={3}]", 
                PositionsCount, NormalsCount, TexcoordsCount, IndicesCount);
        }

    }
}
