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
		/// フェンスクラス
		/// </summary>
		class Fence final : HandyItems::others::NonCopyableMovableBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			Fence() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~Fence() = default;

			/* ===== 初期化関数 ===== */

			/// <summary>
			/// フェンス作成関数
			/// </summary>
			/// <param name="device_">Device参照</param>
			/// <returns>作成の成否</returns>
			[[nodiscard]] HRESULT create_fence(
				ID3D12Device* device_
			) {

				const auto hr = device_->CreateFence(
					0, 
					D3D12_FENCE_FLAG_NONE, 
					IID_PPV_ARGS(&fence_)
				);
				if (FAILED(hr)) {
					return hr;
				}

				//	フェンスイベント作成
				wait_event = CreateEvent(
					nullptr, 
					FALSE, 
					FALSE, 
					nullptr
				);
				if (!wait_event) {
					return E_FAIL;
				}

				return hr;
			}

			/* ===== 実行関数 ===== */

			/// <summary>
			/// シグナル関数
			/// </summary>
			/// <param name="queue_">シグナル先キュー</param>
			/// <returns>シグナルした値</returns>
			[[nodiscard]] const UINT64 signal(
				ID3D12CommandQueue* queue_
			) {

				fence_value++;

				const auto hr = queue_->Signal(fence_.Get(), fence_value);
				if (FAILED(hr)) {
					//	シグナルできない場合エラーを出すか検討
				}

				return fence_value;
			}

			/// <summary>
			/// フェンス待機関数
			/// </summary>
			/// <param name="completed_value">完了するまで待機する値</param>
			void wait_to_completed_value(
				const UINT64& completed_value
			) const noexcept {
				
				if (fence_value < completed_value) {

					/*
					フェンスにシグナルしている以上が来たとき、
					シグナルしている値以下ではないと無限に待機してしまう関係上
					待機できないため即return
					*/

					return;
				}
				else if(completed_value == 0){
					return;
				}

				const auto hr = fence_->SetEventOnCompletion(completed_value, wait_event);
				if (FAILED(hr)) {
					//	イベントセットできない場合エラーを出すか検討
				}

				WaitForSingleObject(wait_event, INFINITE);
			}

			/* ===== 取得関数 ===== */

			/* -- 本体 -- */

			/// <summary>
			/// フェンス参照取得関数
			/// </summary>
			/// <returns>フェンス参照</returns>
			[[nodiscard]] ID3D12Fence* get()const noexcept {

				return fence_.Get();
			}

			/// <summary>
			/// フェンス参照アロー演算子オーバーロード
			/// </summary>
			/// <returns>フェンス参照</returns>
			[[nodiscard]] ID3D12Fence* operator -> () const noexcept {

				return get();
			}

			/* -- フェンス値 -- */

			/// <summary>
			/// フェンス値取得関数
			/// </summary>
			/// <returns>動作完了したフェンス値</returns>
			[[nodiscard]] const UINT64 get_completed_value() const noexcept {

				return fence_->GetCompletedValue();
			}

			/// <summary>
			/// 現在シグナル値取得関数
			/// </summary>
			/// <details>
			/// 最後にシグナルした値
			/// </details>
			/// <returns>現在シグナル値</returns>
			[[nodiscard]] const UINT64 get_now_signal_value()const noexcept {

				return fence_value;
			}
			
		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			/// フェンスの値
			/// </summary>
			UINT64 fence_value{};

			/// <summary>
			/// フェンスインスタンス
			/// </summary>
			Microsoft::WRL::ComPtr<ID3D12Fence> fence_{};

			/// <summary>
			/// フェンスイベント
			/// </summary>
			HANDLE wait_event{};

		};
	}
}