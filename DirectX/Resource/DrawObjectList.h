#pragma once

/* ========== Includeファイル ========== */

#include"../Helpers/DrawObjectPassDesc.h"

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
		namespace Pass {

			/// <summary>
			/// 描画オブジェクト名前空間
			/// </summary>
			namespace DrawObject {

				const DrwObjectPassDesc NormalTest = {
					"DrawNormalObject",
					{
						{
							"NormalMesh"
						}
					},
					false
				};

				const DrwObjectPassDesc ColorTest = {
					"DrawColorObject",
					{
						{
							"ColorMesh"
						}
					},
					false
				};

			}
		}
	}
}