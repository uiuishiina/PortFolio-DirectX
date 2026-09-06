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
			/// 描画用コマンドリストクラス
			/// </summary>
			class GraphicsCommandList final : public others::NonCopyableBase
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				GraphicsCommandList() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~GraphicsCommandList() = default;


				/* ========== Publicメンバー関数 ========== */

				/* -- 作成関数 -- */

				/// <summary>
				/// 描画用コマンドリスト作成関数
				/// </summary>
				/// <param name="device">DirectX12デバイス参照</param>
				/// <param name="type">コマンドリストタイプ</param>
				/// <param name="allocator">コマンドアロケータ参照</param>
				/// <returns>作成の成否</returns>
				[[nodiscard]] HRESULT create_graphics_command_list(
					ID3D12Device* device, 
					D3D12_COMMAND_LIST_TYPE type, 
					ID3D12CommandAllocator* allocator
				);

				/* -- リセット関数 -- */

				/// <summary>
				/// 描画用コマンドリストリセット関数
				/// </summary>
				/// <param name="allocator">コマンドリストをリセットするコマンドアロケータ参照</param>
				void reset_command_list(ID3D12CommandAllocator* allocator);

				/* -- 取得関数 -- */

				/// <summary>
				/// 描画用コマンドリスト取得関数
				/// </summary>
				/// <returns>コマンドリスト参照</returns>
				[[nodiscard]] ID3D12GraphicsCommandList* get_graphics_command_list() const noexcept;

			private:
				/* ========== Privateメンバー関数 ========== */

				/// <summary>
				/// 描画用コマンドリストインスタンス
				/// </summary>
				Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> command_list{};

			};
		}
	}
}