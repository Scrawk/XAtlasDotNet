using System;
using System.Collections.Generic;

namespace XAtlasDotNet.Core
{
	public struct PackOptions
	{
		/// <summary>
		/// Charts larger than this will be scaled down. 0 means no limit.
		/// </summary>
		public uint MaxChartSize = 0;

		/// <summary>
		/// Number of pixels to pad charts with.
		/// </summary>
		public uint Padding = 0;

		/// <summary>
		/// Unit to texel scale. e.g. a 1x1 quad with texelsPerUnit of 32 will take up approximately 32x32 texels in the atlas.
		/// If 0, an estimated value will be calculated to approximately match the given resolution.
		/// If resolution is also 0, the estimated value will approximately match a 1024x1024 atlas
		/// </summary>
		public float TexelsPerUnit = 0.0f;

		/// <summary>
		/// If 0, generate a single atlas with texelsPerUnit determining the final resolution.
		/// If not 0, and texelsPerUnit is not 0, generate one or more atlases with that exact resolution.
		/// If not 0, and texelsPerUnit is 0, texelsPerUnit is estimated to approximately match the resolution.
		/// </summary>
		public uint Resolution = 0;

		/// <summary>
		/// Leave space around charts for texels that would be sampled by bilinear filtering.
		/// </summary>
		public bool Bilinear = true;

		/// <summary>
		/// Align charts to 4x4 blocks. Also improves packing speed, since there are fewer possible chart locations to consider.
		/// </summary>
		public bool BlockAlign = false;

		/// <summary>
		/// Slower, but gives the best result. If false, use random chart placement.
		/// </summary>
		public bool BruteForce = false;

		/// <summary>
		/// Create image for debugging.
		/// </summary>
		private bool CreateImage = false;

		/// <summary>
		/// Rotate charts to the axis of their convex hull.
		/// </summary>
		public bool RotateChartsToAxis = true;

		/// <summary>
		/// Rotate charts to improve packing.
		/// </summary>
		public bool RotateCharts = true;

		/// <summary>
		/// 
		/// </summary>
		public static PackOptions Default
        {
            get
            {
				return new PackOptions();	
            }
        }
    }
}
