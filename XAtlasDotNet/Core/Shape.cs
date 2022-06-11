using System;
using System.Collections.Generic;

namespace XAtlasDotNet.Core
{
    public struct Shape
    {
        public MeshCount Mesh;

        public override string ToString()
        {
            return string.Format("[Shape: Mesh={0}]", Mesh);
        }
    }
}
