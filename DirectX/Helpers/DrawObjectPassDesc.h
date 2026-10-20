#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../ClassModule/DrawObjectPass.h"
#include"../Container/DrawObjectConteiner.h"

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

				/// <summary>
				/// 描画オブジェクトパス外部参照補助構造体
				/// </summary>
				struct DrawObjectPassReference {

					/// <summary>
					/// 描画オブジェクト登録名配列
					/// </summary>
					std::vector<std::string> draw_object_names{};
				};

				/// <summary>
				/// 描画オブジェクトパス設定定義
				/// </summary>
				using DrwObjectPassDesc = std::tuple<
					std::string,
					DrawObjectPassReference
				>;
			}
		}
	}
}