#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Others/NonCopyableBase.h"
#include"Others/UniquePtr.h"

//	DirectX
#include"../ClassObject/CommandAllocator.h"

#include"../ClassModule/UploadResources.h"

#include"../ClassObject/Fence.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// オブジェクト機能統合名前空間
	/// </summary>
	namespace ClassModule {

		/// <summary>
		/// フレームリソースクラス
		/// </summary>
		class FrameResource final : HandyItems::others::NonCopyableMovableBase 
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			[[nodiscard]] HRESULT initialize_resources(
				ID3D12Device* device_,
				ClassObject::Fence* fence
			) {
				auto hr = graphic_allocatpor.create_allocator(
					device_,
					D3D12_COMMAND_LIST_TYPE_DIRECT
				);
				if (FAILED(hr)) {
					return hr;
				}

				fence_ = fence;
				return hr;
			}

			/* ===== 実行関数 ===== */

			/// <summary>
			/// フレーム終了時
			/// </summary>
			/// <param name="queue_">コマンドキュー参照</param>
			void end_frame_signal(
				ID3D12CommandQueue* queue_
			) {

				frame_fence_value = fence_->signal(queue_);
			}

			/// <summary>
			/// フレームリソースリセット関数
			/// </summary>
			void reset_frame_resource() {

				graphic_allocatpor.reset_allocator();
				upload_resources.clear();
			}

			/* ===== 取得関数 ===== */

			/// <summary>
			/// フェンス値取得関数
			/// </summary>
			/// <returns>フェンス値</returns>
			[[nodiscard]] UINT64 get_frame_value() const noexcept {

				return frame_fence_value;
			}

			/// <summary>
			/// コマンドアロケーター参照取得関数
			/// </summary>
			/// <returns>コマンドアロケーター参照</returns>
			[[nodiscard]] ClassObject::CommandAllocator& get_allocator() {

				return graphic_allocatpor;
			}

			/// <summary>
			/// UploadResources参照取得関数
			/// </summary>
			/// <returns>UploadResources参照</returns>
			[[nodiscard]] ClassModule::UploadResources& get_upload_resources() {

				return upload_resources;
			}

		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			/// フェンス値
			/// </summary>
			UINT64 frame_fence_value{};

			/// <summary>
			/// フェンスインスタンスWeak参照
			/// </summary>
			ClassObject::Fence* fence_{};

			/// <summary>
			/// 描画用コマンドアロケーターインスタンス
			/// </summary>
			ClassObject::CommandAllocator graphic_allocatpor{};

			/// <summary>
			/// UploadResourcesインスタンス
			/// </summary>
			ClassModule::UploadResources upload_resources{};

		};
	}
}