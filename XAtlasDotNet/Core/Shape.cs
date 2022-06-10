using System;
using System.Collections.Generic;

namespace XAtlasDotNet.Core
{
    public struct Shape
    {
        public MeshCount mesh;

        public override string ToString()
        {
            return string.Format("[Shape: Mesh={0}]", mesh);
        }
    }
}
