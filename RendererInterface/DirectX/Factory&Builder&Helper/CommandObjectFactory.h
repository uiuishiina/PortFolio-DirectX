#pragma once
#include"../DirectXobject/CommandQueue.h"
#include"../DirectXobject/CommandAllocator.h"
#include"../DirectXobject/GraphicsCommandList.h"
#include<memory>
#include<vector>

/// <summary>
/// 描画機能名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		/// <summary>
		/// Factory名前空間
		/// </summary>
		namespace factory {

			/// <summary>
			/// コマンドオブジェクトファクトリー
			/// </summary>
			class CommandObjectFactory final
			{
			public:
				/* ========== Publicメンバー関数 ========== */

				/// <summary>
				/// 描画用コマンドキュー作成関数
				/// </summary>
				/// <param name="device">DirectX12デバイス参照</param>
				/// <param name="out">受け渡すインスタンス参照</param>
				/// <returns>作成の成否</returns>
				[[nodiscard]] static HRESULT create_graphics_command_queue(
					ID3D12Device* device, 
					object::CommandQueue& out
				);

				/// <summary>
				/// 描画用コマンドアロケーター作成関数
				/// </summary>
				/// <param name="device">DirectX12デバイス参照</param>
				/// <param name="out">受け渡すインスタンス</param>
				/// <returns>作成の成否</returns>
				[[nodiscard]] static HRESULT create_graphics_command_allocator(
					ID3D12Device* device, 
					object::CommandAllocator& out
				);

				/// <summary>
				/// 描画用コマンドリスト作成関数
				/// </summary>
				/// <param name="device">DirectX12デバイス参照</param>
				/// <param name="allocator">作成に利用する描画用アロケーター</param>
				/// <param name="out">受け渡すインスタンス</param>
				/// <returns>作成の成否</returns>
				[[nodiscard]] static HRESULT create_graphics_command_list(
					ID3D12Device* device,
					ID3D12CommandAllocator* allocator, 
					object::GraphicsCommandList& out
				);

			private:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				CommandObjectFactory() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~CommandObjectFactory() = default;

			};
		}
	}
}