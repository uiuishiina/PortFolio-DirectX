#pragma once
#include"GPUResource.h"

/// <summary>
/// 描画機能名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		/// <summary>
		/// DX12オブジェクトラッパークラス名前空間
		/// </summary>
		namespace object {
			
			/// <summary>
			/// 描画リソース基底クラス
			/// </summary>
			class TextureResource : public GPUResourceBase
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ削除
				/// </summary>
				TextureResource() = delete;

				/// <summary>
				/// 引数付きコンストラクタ
				/// </summary>
				/// <param name="state">初期設定リソースステート</param>
				TextureResource(D3D12_RESOURCE_STATES state);

				/// <summary>
				/// デストラクタ
				/// </summary>
				virtual ~TextureResource() = default;


				/* ========== Publicメンバー関数 ========== */

				/// <summary>
				/// リソースバリア遷移関数
				/// </summary>
				/// <param name="list">描画用コマンドリスト参照</param>
				/// <param name="next_state">遷移先バリアステート</param>
				void  barrier_transition(
					ID3D12GraphicsCommandList* list, 
					D3D12_RESOURCE_STATES next_state
				);

			protected:
				/* ========== Protectedメンバー変数 ========== */

				/// <summary>
				/// 現在リソースステート
				/// </summary>
				D3D12_RESOURCE_STATES current_state{};

			};
		}
	}
}