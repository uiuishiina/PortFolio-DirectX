#pragma once
#include"TextureResource.h"

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
			/// レンダーターゲット基底クラス
			/// </summary>
			class RenderTarget : public TextureResource
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				/// <details>
				/// 基底クラスの引数付きコンストラクタをコンストラクタで呼び出す
				/// </details>
				RenderTarget();

				/// <summary>
				/// デストラクタ
				/// </summary>
				virtual ~RenderTarget() = default;


				/* ========== Publicメンバー関数 ========== */

				/// <summary>
				/// RTVハンドル取得関数
				/// </summary>
				/// <returns>RTV CPUハンドル</returns>
				[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE get_rtv_handle() const noexcept;

			protected:
				/* ========== Privateメンバー変数 ========== */

				/// <summary>
				/// レンダーターゲットディスクリプタハンドル
				/// </summary>
				D3D12_CPU_DESCRIPTOR_HANDLE rtv_handle{};

			};
		}
	}
}