#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../DirectXContext.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// オブジェクト機能統合名前空間
	/// </summary>
	namespace ClassModule {

		

		struct FrameContext final : HandyItems::others::NonCopyableMovableBase {

			template<typename T>
			using UniquePtr = HandyItems::others::UniquePtr<T>;

			template<typename T>
			using WeakPtr = HandyItems::others::UniqueWeakPtr<T>;


			/* ========== Publicメンバー変数 ========== */

			/* -- Core -- */

			/// <summary>
			/// DXGI
			/// </summary>
			ClassObject::DXGI* dxgi_;

			/// <summary>
			/// Deviceインスタンス
			/// </summary>
			ClassObject::Device* device_;

			/// <summary>
			/// 描画用コマンドキューインスタンス
			/// </summary>
			ClassObject::CommandQueue* graphic_queue;

			/// <summary>
			/// 描画用コマンドリストインスタンス
			/// </summary>
			ClassObject::CommandList* graphic_list;

			/// <summary>
			/// フェンスインスタンス
			/// </summary>
			ClassObject::Fence* fence_;

			/// <summary>
			/// フレームリソースインスタンス配列
			/// </summary>
			ClassModule::FrameResource* frame_resource;

			/// <summary>
			/// スワップチェーンインスタンス
			/// </summary>
			ClassObject::SwapChain* swapchain_;

			/// <summary>
			/// ディスクリプタヒープインスタンス
			/// </summary>
			ClassObject::DescriptorHeap* heap_;

			/// <summary>
			/// バックバッファインスタンス配列
			/// </summary>
			ClassObject::BackBuffer* back_buffer;

			/* ========== Publicメンバー関数 ========== */

			//	コンストラクタ削除
			FrameContext() = delete;

			/// <summary>
			/// 引数付きコンストラクタ
			/// </summary>
			/// <param name="context"></param>
			/// <param name="current_back_buffer"></param>
			/// <param name="current_resource"></param>
			FrameContext(
				DirectXContext* context,
				UINT current_back_buffer,
				size_t current_resource
			) :
				dxgi_{ context->dxgi_.get() },
				device_{ context->device_.get() },
				graphic_queue{ context->graphic_queue.get() },
				graphic_list{ context->graphic_list.get() },
				fence_{ context->fence_.get() },
				frame_resource{ context->frame_resources[current_resource].get() },
				swapchain_{ context->swapchain_.get() },
				heap_{ context->heap_.get() },
				back_buffer{ context->back_buffers[current_back_buffer].get() } {}

			/// <summary>
			/// デストラクタ
			/// </summary>
			~FrameContext() = default;

		};
	}
}