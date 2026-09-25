#pragma once

#include"../ClassObject/PiplineState.h"

#include<string>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/* ========== 前方宣言 ========== */

	struct DirectXContext;

	/// <summary>
	/// DirectXオブジェクト名前空間
	/// </summary>
	namespace ClassObject {

		/// <summary>
		/// DirectXオブジェクト設定構造体名前空間
		/// </summary>
		namespace desc {

			/// <summary>
			/// パイプラインステート外部参照補助構造体
			/// </summary>
			struct PiplineReferenceName {

				/* ========== Publicメンバー変数 ========== */

				/// <summary>
				/// ルートシグネチャー登録名
				/// </summary>
				std::string root_name{};

				/// <summary>
				/// 頂点シェーダー登録名
				/// </summary>
				std::string vs_name{};

				/// <summary>
				/// ピクセルシェーダー登録名
				/// </summary>
				std::string ps_name{};

				/// <summary>
				/// ジオメトリシェーダー登録名
				/// </summary>
				std::string gs_name{};

				/// <summary>
				/// ハルシェーダー登録名
				/// </summary>
				std::string hs_name{};

				/// <summary>
				/// ドメインシェーダー登録名
				/// </summary>
				std::string ds_name{};

				/* ========== Publicメンバー関数 ========== */

				/// <summary>
				/// 参照設定関数
				/// </summary>
				/// <details>
				/// 内部でコンテナから参照を取得し、desc に設定する関数
				/// </details>
				/// <param name="context">DirectXオブジェクトインスタンス構造体参照</param>
				/// <param name="desc">パイプラインステート設定構造体参照</param>
				void set(
					DirectXContext* context,
					ClassObject::desc::PipelineStateDesc& desc
				) const;

			};
		}
	}
}