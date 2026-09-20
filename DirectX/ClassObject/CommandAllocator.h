#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Others/NonCopyableBase.h"

//	DirectX
#include<d3d12.h>
#include<wrl/client.h>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// DirectXオブジェクト名前空間
	/// </summary>
	namespace ClassObject {

		/// <summary>
		/// コマンドアロケータークラス
		/// </summary>
		class CommandAllocator final : HandyItems::others::NonCopyableMovableBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			CommandAllocator() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~CommandAllocator() = default;

			/* ===== 初期化関数 ===== */

			/// <summary>
			/// コマンドアロケーター作成関数
			/// </summary>
			/// <param name="device_">Device参照</param>
			/// <param name="type">コマンドアロケータータイプ</param>
			/// <returns>作成の成否</returns>
			[[nodiscard]] HRESULT create_allocator(
				ID3D12Device* device_,
				D3D12_COMMAND_LIST_TYPE type
			) {

				return device_->CreateCommandAllocator(type, IID_PPV_ARGS(&command_allocator));
			}

			/* ===== 実行関数 ===== */

			/// <summary>
			/// コマンドアロケーターリセット関数
			/// </summary>
			/// <returns>リセットの成否</returns>
			HRESULT reset_allocator() {

				return command_allocator->Reset();
			}

			/* ===== 取得関数 ===== */

			/// <summary>
			/// コマンドアロケーター参照取得関数
			/// </summary>
			/// <returns>コマンドアロケーター参照</returns>
			[[nodiscard]] ID3D12CommandAllocator* get() const noexcept {

				return command_allocator.Get();
			}

			/// <summary>
			/// コマンドアロケーター参照アロー演算子オーバーロード
			/// </summary>
			/// <returns>コマンドアロケーター参照</returns>
			[[nodiscard]] ID3D12CommandAllocator* operator -> () const noexcept {
				return get();
			}

		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			/// コマンドアロケータインスタンス
			/// </summary>
			Microsoft::WRL::ComPtr<ID3D12CommandAllocator> command_allocator{};

		};
	}
}