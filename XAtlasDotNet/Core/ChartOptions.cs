using System;
using System.Collections.Generic;

namespace XAtlasDotNet.Core
{
	public struct ChartOptions
	{
		//ParameterizeFunc paramFunc = nullptr;

		/// <summary>
		/// Don't grow charts to be larger than this. 0 means no limit.
		/// </summary>
		public float MaxChartArea = 0.0f;

		/// <summary>
		/// Don't grow charts to have a longer boundary than this. 0 means no limit.
		/// </summary>
		public float MaxBoundaryLength = 0.0f;

		// Weights determine chart growth. Higher weights mean higher cost for that metric.

		/// <summary>
		/// Angle between face and average chart normal.
		/// </summary>
		public float NormalDeviationWeight = 2.0f;
		
		/// <summary>
		/// 
		/// </summary>
		public float RoundnessWeight = 0.01f;

		/// <summary>
		/// 
		/// </summary>
		public float StraightnessWeight = 6.0f;

		/// <summary>
		/// If > 1000, normal seams are fully respected.
		/// </summary>
		public float NormalSeamWeight = 4.0f;

		/// <summary>
		/// 
		/// </summary>
		public float TextureSeamWeight = 0.5f;

		/// <summary>
		/// If total of all metrics * weights > maxCost, don't grow chart. Lower values result in more charts.
		/// </summary>
		public float MaxCost = 2.0f;

		/// <summary>
		/// Number of iterations of the chart growing and seeding phases. Higher values result in better charts.
		/// </summary>
		public uint MaxIterations = 1;

		/// <summary>
		/// Use vertexUvData for charts.
		/// </summary>
		public bool UseInputMeshUvs = false;

		/// <summary>
		/// Enforce consistent texture coordinate winding.
		/// </summary>
		public bool FixWinding = false; 

		/// <summary>
		/// 
		/// </summary>
		public static ChartOptions Default
        {
            get
            {
				return new ChartOptions();
            }
        }
	};
}
