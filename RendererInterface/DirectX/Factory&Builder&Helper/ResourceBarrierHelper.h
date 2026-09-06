#pragma once
#include<d3d12.h>

/// <summary>
/// 描画機能名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		/// <summary>
		/// Helper名前空間
		/// </summary>
		namespace helper {

			/// <summary>
			/// リソースバリア作成ヘルパークラス
			/// </summary>
			class ResourceBarrierHelper final
			{
			public:
				/* ========== Publicメンバー関数 ========== */

				/// <summary>
				/// リソースバリア作成関数
				/// </summary>
				/// <param name="resource">リソースバリアを作成するリソース</param>
				/// <param name="from">リソースの現在の状態</param>
				/// <param name="to">リソースの遷移先の状態</param>
				/// <returns>作成されたリソースバリア</returns>
				[[nodiscard]] static D3D12_RESOURCE_BARRIER create_resource_barrier(
					ID3D12Resource* resource,
					D3D12_RESOURCE_STATES from, 
					D3D12_RESOURCE_STATES to
				) noexcept;

			private:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				ResourceBarrierHelper() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~ResourceBarrierHelper() = default;

			};
		}
	}
}