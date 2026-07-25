#pragma once
#include"../DirectXobject/RootSignature.h"

///====================================================================
/// 描画名前空間
///====================================================================

namespace render {

	///====================================================================
	/// DirectX名前空間
	///====================================================================

	namespace dx12 {

		///====================================================================
		/// Builder名前空間
		///====================================================================

		namespace builder {

			///====================================================================
			/// RootSignatureDescBuilder クラス
			///====================================================================

			//@brief	=== ルートシグネチャー設定作成クラス ===
			class RootSignatureDescBuilder final
			{
			public:
				///====================================================================
				/// Public メンバー関数
				///====================================================================

				/* -- ルートパラメーター追加関数群 -- */

				//@brief	=== CBV設定追加関数 ===
				//@param	desc	設定を追加するインスタンス参照
				//@param	shaderRegister	シェーダーレジスター(r0など)
				//@param	registerSpace	レジスタースペース
				//@param	visibility	参照可能シェーダー設定フラグ
				static void add_CBV(desc::RootSignatureDesc& desc, UINT shaderRegister,
					UINT registerSpace = 0, D3D12_SHADER_VISIBILITY visibility = D3D12_SHADER_VISIBILITY_ALL);

				/* -- サンプラー追加関数群 -- */

				/* -- パイプラインステートフラグ追加関数 -- */

				//@brief	=== パイプラインステートフラグ追加関数　===
				//@param	desc 設定を追加するインスタンス参照
				//@param	flags パイプラインステートフラグ
				static void add_flags(desc::RootSignatureDesc& desc, D3D12_ROOT_SIGNATURE_FLAGS flags);

			private:
				///====================================================================
				/// クラス設定
				///====================================================================

				//コンストラクタ,デストラクタ
				RootSignatureDescBuilder() = default;
				~RootSignatureDescBuilder() = default;

			};
		};
	};
};