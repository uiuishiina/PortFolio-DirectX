#pragma once
#include"Others/NonCopyableBase.h"
#include<d3d12.h>
#include<wrl/client.h>

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
			/// コマンドキュークラス
			/// </summary>
			class CommandQueue final : public others::NonCopyableBase
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				CommandQueue() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~CommandQueue() = default;


				/* ========== Publicメンバー関数 ========== */

				/* -- 作成関数 -- */

				/// <summary>
				/// コマンドキュー作成関数
				/// </summary>
				/// <param name="device">DirectX12デバイス参照</param>
				/// <param name="type">コマンドリストタイプ</param>
				/// <returns>作成の成否</returns>
				[[nodiscard]] HRESULT create_command_queue(
					ID3D12Device* device, 
					D3D12_COMMAND_LIST_TYPE type
				);

				/* -- 取得関数 -- */

				/// <summary>
				/// コマンドキュー取得関数
				/// </summary>
				/// <returns>コマンドキュー参照</returns>
				[[nodiscard]] ID3D12CommandQueue* get_command_queue() const noexcept;

			private:
				/* ========== Privateメンバー変数 ========== */

				/// <summary>
				/// コマンドキューインスタンス
				/// </summary>
				Microsoft::WRL::ComPtr<ID3D12CommandQueue> command_queue{};

			};
		}
	}
}