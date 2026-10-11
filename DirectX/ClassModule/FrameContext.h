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

		/// <summary>
		/// 現在フレーム使用可能リソース集約構造体
		/// </summary>
		struct FrameContext final : HandyItems::others::NonCopyableMovableBase {

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
			/// バックバッファインスタンス配列
			/// </summary>
			ClassObject::BackBuffer* back_buffer;

			/// <summary>
			/// ディスクリプターヒープコンテナインスタンス
			/// </summary>
			/// <returns></returns>
			Container::DescriptorHeapContainer* static_heap_container;

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
				DirectXContext* context_,
				UINT current_back_buffer,
				std::size_t current_resource
			) :
				dxgi_{ context_->dxgi_.get() },
				device_{ context_->device_.get() },
				graphic_queue{ context_->graphic_queue.get() },
				graphic_list{ context_->graphic_list.get() },
				fence_{ context_->fence_.get() },
				frame_resource{ context_->frame_resources[current_resource].get() },
				swapchain_{ context_->swapchain_.get() },
				static_heap_container{ context_->heap_container.get() },
				back_buffer{ context_->back_buffers[current_back_buffer].get() }{}

			/// <summary>
			/// デストラクタ
			/// </summary>
			~FrameContext() = default;

		};
	}
}