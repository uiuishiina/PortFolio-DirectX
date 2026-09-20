#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"GPUResourceBase.h"
#include"ResourceBarrier.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// DirectXオブジェクト名前空間
	/// </summary>
	namespace ClassObject {

		/// <summary>
		/// 描画先クラス
		/// </summary>
		class RenderTarget : public GPUResourceBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			///* ===== 実行関数 ===== */

			/// <summary>
			/// リソースバリア遷移関数
			/// </summary>
			/// <param name="list">コマンドリスト参照</param>
			/// <param name="next_state">遷移先バリアステート</param>
			void barrier_transition(
				ID3D12GraphicsCommandList* list,
				D3D12_RESOURCE_STATES next_state
			) {

				barrier_.barrier_transition(
					list, 
					resource_.Get(), 
					next_state
				);
			}

			/* ===== 取得関数 ===== */

			/// <summary>
			/// RTVハンドル取得関数
			/// </summary>
			/// <returns>RTV CPUハンドル</returns>
			[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE get_RTV_handle() const noexcept {

				return rtv_handle;
			}

		protected:
			/* ========== Protectedメンバー関数 ========== */

			//	コンストラクタ削除
			RenderTarget() = delete;

			/// <summary>
			/// リソースステート設定コンストラクタ
			/// </summary>
			/// <param name="state">初期設定リソースステート</param>
			RenderTarget(
				D3D12_RESOURCE_STATES state
			) :
				barrier_{ state } {}

			/// <summary>
			/// デストラクタ
			/// </summary>
			virtual ~RenderTarget() = default;

			/* ========== Protectedメンバー変数 ========== */

			/// <summary>
			/// レンダーターゲットディスクリプタハンドル
			/// </summary>
			D3D12_CPU_DESCRIPTOR_HANDLE rtv_handle{};

			/// <summary>
			/// リソースバリア管理クラス
			/// </summary>
			ResourceBarrier barrier_;

		};
	}
}