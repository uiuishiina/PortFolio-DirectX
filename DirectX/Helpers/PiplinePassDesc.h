#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../ClassModule/PiplinePass.h"

#include"../Container/RootSignatureContainer.h"
#include"../Container/PiplineStateContainer.h"
#include"../Container/PassContainer.h"

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
			/// パイプライン名前空間
			/// </summary>
			namespace Piplines {

				/// <summary>
				/// パイプラインパス外部参照補助構造体
				/// </summary>
				struct PiplinePassReference {

					/* ========== Publicメンバー変数 ========== */

					/// <summary>
					/// ルートシグネチャー登録名
					/// </summary>
					std::string root_name{};

					/// <summary>
					/// ルートシグネチャー設定列挙体
					/// </summary>
					ClassModule::RootState root_state{};

					/// <summary>
					/// パイプラインステート登録名
					/// </summary>
					std::string pipline_name{};

					/// <summary>
					/// 呼び出しパス登録名配列
					/// </summary>
					std::vector<std::string> pass_names{};

				};

				/// <summary>
				/// パイプラインパス設定定義
				/// </summary>
				using PiplinePassDesc = std::tuple<
					std::string,
					PiplinePassReference
				>;
			}
		}
	}
}