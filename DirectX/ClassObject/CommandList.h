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
		/// コマンドリストクラス
		/// </summary>
		class CommandList final : HandyItems::others::NonCopyableMovableBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			CommandList() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~CommandList() = default;

			/* ===== 初期化関数 ===== */

			/// <summary>
			/// コマンドリスト作成関数
			/// </summary>
			/// <param name="device_">Device参照</param>
			/// <param name="allocator_">コマンドアロケータ参照</param>
			/// <param name="type">コマンドリストタイプ</param>
			/// <param name="node">ノードマスク... 初期設定[ 0 ]</param>
			/// <param name="pipline_">パイプラインステート参照... 初期設定[ nullptr ]</param>
			/// <returns>作成の成否</returns>
			[[nodiscard]] HRESULT create_list(
				ID3D12Device* device_,
				ID3D12CommandAllocator* allocator_,
				D3D12_COMMAND_LIST_TYPE type,
				UINT node = 0,
				ID3D12PipelineState* pipline_ = nullptr
			) {

				//	コマンドリスト作成
				const auto hr = device_->CreateCommandList(
					node,						//	ノードマスク
					type,						//	コマンドリストタイプ
					allocator_,					//	コマンドアロケータ
					pipline_,					//	初期パイプラインステート（必要に応じて指定）
					IID_PPV_ARGS(&command_list) // コマンドリストの取得
				);
				if (FAILED(hr)) {
					return hr;
				}

				command_list->Close(); // コマンドリストは作成後にクローズする必要がある
				return hr;
			}

			/* ===== 実行関数 ===== */
			
			/// <summary>
			/// コマンドリストリセット関数
			/// </summary>
			/// <param name="allocator">コマンドアロケータ参照</param>
			/// <param name="pipline_">パイプラインステート参照... 初期設定[ nullptr ]</param>
			/// <returns>リセットの成否</returns>
			HRESULT reset_list(
				ID3D12CommandAllocator* allocator_,
				ID3D12PipelineState* pipline_ = nullptr
			) {

				return command_list->Reset(allocator_, pipline_);
			}

			/* ===== 取得関数 ===== */

			/// <summary>
			/// コマンドリスト参照取得関数
			/// </summary>
			/// <returns>コマンドリスト参照</returns>
			[[nodiscard]] ID3D12GraphicsCommandList* get() const noexcept {

				return command_list.Get();
			}

			/// <summary>
			/// コマンドリスト参照アロー演算子オーバーロード
			/// </summary>
			/// <returns>コマンドリスト参照</returns>
			[[nodiscard]] ID3D12GraphicsCommandList* operator -> () const noexcept {

				return get();
			}

		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			/// コマンドリストインスタンス
			/// </summary>
			Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> command_list{};

		};
	}
}