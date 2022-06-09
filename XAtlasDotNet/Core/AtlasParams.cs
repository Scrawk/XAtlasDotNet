using System;
using System.Collections.Generic;

namespace XAtlasDotNet.Core
{
    public struct AtlasParams
    {

		// Number of output meshes. Equal to the number of times AddMesh was called.
		public int MeshCount;

		// Atlas width in texels.
		public int Width;

		// Atlas height in texels.
		public int Height;

		// Number of sub-atlases. Equal to 0 unless PackOptions resolution is changed from default (0).
		public int AtlasCount;

		// Total number of charts in all meshes.
		public int ChartCount;

		// Equal to PackOptions texelsPerUnit if texelsPerUnit > 0,
		// otherwise an estimated value to match PackOptions resolution.
		public float TexelsPerUnit;

		public override string ToString()
        {
			return String.Format("[AtlasParams: MeshCount={0}, Width={1}, Height={2}, AtlasCount={3}, ChartCount={4}, TexelsPerUnit={5}]",
				MeshCount,  Width, Height, AtlasCount, ChartCount, TexelsPerUnit);
        }
    }
}
