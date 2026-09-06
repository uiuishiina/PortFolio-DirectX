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
			/// コマンドアロケータクラス
			/// </summary>
			class CommandAllocator final : public others::NonCopyableBase
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				CommandAllocator() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~CommandAllocator() = default;


				/* ========== Publicメンバー関数 ========== */

				/* -- 作成関数 -- */

				/// <summary>
				/// コマンドアロケータ作成関数
				/// </summary>
				/// <param name="device">DirectX12デバイス参照</param>
				/// <param name="type">コマンドリストタイプ</param>
				/// <returns>作成の成否</returns>
				[[nodiscard]] HRESULT create_command_allocator(
					ID3D12Device* device, 
					D3D12_COMMAND_LIST_TYPE type
				);

				/* -- リセット関数 -- */

				/// <summary>
				/// コマンドアロケータリセット関数
				/// </summary>
				void reset_command_allocator();

				/* -- 取得関数 -- */

				/// <summary>
				/// コマンドアロケータ取得関数
				/// </summary>
				/// <returns>コマンドアロケータ参照</returns>
				[[nodiscard]] ID3D12CommandAllocator* get_command_allocator() const noexcept;

			private:
				/* ========== Privateメンバー変数 ========== */

				/// <summary>
				/// コマンドアロケータインスタンス
				/// </summary>
				Microsoft::WRL::ComPtr<ID3D12CommandAllocator> command_allocator{};

			};
		}
	}
}