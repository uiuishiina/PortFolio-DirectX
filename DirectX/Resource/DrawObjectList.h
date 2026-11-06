#pragma once

/* ========== Includeファイル ========== */

#include"../Helpers/DrawObjectPathDesc.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// リソース名前空間
	/// </summary>
	namespace Resource {

		/// <summary>
		/// パス名前空間
		/// </summary>
		namespace Path {

			/// <summary>
			/// 描画オブジェクト名前空間
			/// </summary>
			namespace DrawObject {

				/*
					パス名称
					{
						描画オブジェクト名
					}
				*/

				const DrwObjectPathDesc NormalTest = {
					"DrawNormalObject",
					{
						{
							"NormalMesh"
						}
					}
				};

				const DrwObjectPathDesc ColorTest = {
					"DrawColorObject",
					{
						{
							"ColorMesh"
						}
					}
				};

			}
		}
	}
}