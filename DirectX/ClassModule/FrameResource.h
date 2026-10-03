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
			template<typename T>
			using UniquePtr = HandyItems::others::UniquePtr<T>;

			template<typename T>
			using WeakPtr = HandyItems::others::UniqueWeakPtr<T>;

		public:
			/* ========== Publicメンバー関数 ========== */

			//	コンストラクタ削除
			FrameResource() = delete;

			/// <summary>
			/// 引数付きコンストラクタ
			/// </summary>
			/// <param name="fence">フェンスインスタンスWeak参照</param>
			FrameResource(
				ClassObject::Fence* fence
			):
				fence_{ fence } {

				graphic_allocatpor = std::make_unique<ClassObject::CommandAllocator>();
				upload_resources = std::make_unique<ClassModule::UploadResources>();
			}

			/// <summary>
			/// デストラクタ
			/// </summary>
			~FrameResource() = default;

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

				upload_resources->clear();
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
			[[nodiscard]] ClassObject::CommandAllocator* get_allocator() const noexcept {

				return graphic_allocatpor.get();
			}

			/// <summary>
			/// UploadResources参照取得関数
			/// </summary>
			/// <returns>UploadResources参照</returns>
			[[nodiscard]] ClassModule::UploadResources* get_upload_resources() const noexcept {

				return upload_resources.get();
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
			ClassObject::Fence* fence_;

			/// <summary>
			/// 描画用コマンドアロケーターインスタンス
			/// </summary>
			std::unique_ptr<ClassObject::CommandAllocator> graphic_allocatpor{};

			/// <summary>
			/// UploadResourcesインスタンス
			/// </summary>
			std::unique_ptr<ClassModule::UploadResources> upload_resources{};

		};
	}
}