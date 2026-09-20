#pragma once

/* ========== Includeファイル ========== */

#include"Others/NonCopyableBase.h"
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
		/// コマンドキュークラス
		/// </summary>
		class CommandQueue final : HandyItems::others::NonCopyableMovableBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			CommandQueue() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~CommandQueue() = default;

			/* ===== 初期化関数 ===== */
		
			/// <summary>
			/// コマンドキュー作成関数
			/// </summary>
			/// <param name="device_">Device参照</param>
			/// <param name="type">コマンドキュータイプ</param>
			/// <param name="priority">コマンドキュー設定... 初期設定[ D3D12_COMMAND_QUEUE_PRIORITY_NORMAL ]</param>
			/// <param name="flags">コマンドキューフラグ... 初期設定[ D3D12_COMMAND_QUEUE_FLAG_NONE ]</param>
			/// <param name="node">ノードマスク... 初期設定[ 0 ]</param>
			/// <returns>作成の成否</returns>
			[[nodiscard]] HRESULT create_queue(
				ID3D12Device* device_,
				D3D12_COMMAND_LIST_TYPE type,
				D3D12_COMMAND_QUEUE_PRIORITY priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL,
				D3D12_COMMAND_QUEUE_FLAGS flags = D3D12_COMMAND_QUEUE_FLAG_NONE,
				UINT node = 0
			) {

				D3D12_COMMAND_QUEUE_DESC desc{};
				desc.Type		= type;
				desc.Priority	= priority;
				desc.Flags		= flags;
				desc.NodeMask	= node;

				return device_->CreateCommandQueue(&desc, IID_PPV_ARGS(&command_queue));
			}

			/* ===== 取得関数 ===== */

			/// <summary>
			/// コマンドキュー参照取得関数
			/// </summary>
			/// <returns>コマンドキュー参照</returns>
			[[nodiscard]] ID3D12CommandQueue* get() const noexcept {

				return command_queue.Get();
			}

			/// <summary>
			/// コマンドキュー参照アロー演算子オーバーロード
			/// </summary>
			/// <returns>コマンドキュー参照</returns>
			[[nodiscard]] ID3D12CommandQueue* operator -> () const noexcept {

				return get();
			}

		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			/// コマンドキューインスタンス
			/// </summary>
			Microsoft::WRL::ComPtr<ID3D12CommandQueue> command_queue{};

		};
	}
}