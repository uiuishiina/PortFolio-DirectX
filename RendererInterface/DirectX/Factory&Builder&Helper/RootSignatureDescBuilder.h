#pragma once
#include"../DirectXobject/RootSignature.h"

/// <summary>
/// 描画機能名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		/// <summary>
		/// Builder名前空間
		/// </summary>
		namespace builder {

			/// <summary>
			/// ルートシグネチャー設定作成クラス
			/// </summary>
			class RootSignatureDescBuilder final
			{
			public:
				/* ========== Publicメンバー関数 ========== */

				/* -- ルートパラメーター追加関数群 -- */

				/// <summary>
				/// CBV設定追加関数
				/// </summary>
				/// <param name="desc">設定構造体参照</param>
				/// <param name="shaderRegister">シェーダーレジスター(r0など)</param>
				/// <param name="registerSpace">レジスタースペース</param>
				/// <param name="visibility">参照可能シェーダー設定フラグ</param>
				static void add_CBV(
					desc::RootSignatureDesc& desc,
					UINT shaderRegister,
					UINT registerSpace = 0, 
					D3D12_SHADER_VISIBILITY visibility = D3D12_SHADER_VISIBILITY_ALL
				);

				/* -- サンプラー追加関数群 -- */

				/* -- パイプラインステートフラグ追加関数 -- */

				/// <summary>
				/// パイプラインステートフラグ追加関数
				/// </summary>
				/// <param name="desc">設定構造体参照</param>
				/// <param name="flags">パイプラインステートフラグ</param>
				static void add_flags(
					desc::RootSignatureDesc& desc,
					D3D12_ROOT_SIGNATURE_FLAGS flags
				);

			private:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				RootSignatureDescBuilder() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~RootSignatureDescBuilder() = default;

			};
		}
	}
}