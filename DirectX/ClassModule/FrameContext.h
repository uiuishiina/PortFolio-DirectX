#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../DirectXContext.h"

#include<functional>

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
			/// DXGIインスタンス
			/// </summary>
			WeakPtr<ClassObject::DXGI> dxgi_;

			/// <summary>
			/// Deviceインスタンス
			/// </summary>
			WeakPtr<ClassObject::Device> device_;

			/// <summary>
			/// 描画用コマンドキューインスタンス
			/// </summary>
			WeakPtr<ClassObject::CommandQueue> graphic_queue;

			/// <summary>
			/// 描画用コマンドリストインスタンス
			/// </summary>
			WeakPtr<ClassObject::CommandList> graphic_list;

			/// <summary>
			/// フェンスインスタンス
			/// </summary>
			WeakPtr<ClassObject::Fence> fence_;

			/// <summary>
			/// フレームリソースインスタンス配列
			/// </summary>
			WeakPtr<ClassModule::FrameResource> frame_resource;

			/// <summary>
			/// スワップチェーンインスタンス
			/// </summary>
			WeakPtr<ClassObject::SwapChain> swapchain_;

			/// <summary>
			/// ディスクリプタヒープインスタンス
			/// </summary>
			WeakPtr<ClassObject::DescriptorHeap> heap_;

			/// <summary>
			/// バックバッファインスタンス配列
			/// </summary>
			WeakPtr<ClassObject::BackBuffer> back_buffer;

			/* ========== Publicメンバー関数 ========== */

			//	コンストラクタ削除
			FrameContext() = delete;

			FrameContext(
				DirectXContext* context,
				UINT current_back_buffer,
				size_t current_resource
			) :
				dxgi_{ HandyItems::others::make_unique_weak(context->dxgi_) },
				device_{ HandyItems::others::make_unique_weak(context->device_) },
				graphic_queue{ HandyItems::others::make_unique_weak(context->graphic_queue) },
				graphic_list{ HandyItems::others::make_unique_weak(context->graphic_list) },
				fence_{ HandyItems::others::make_unique_weak(context->fence_) },
				frame_resource{ HandyItems::others::make_unique_weak(context->frame_resources[current_resource]) },
				swapchain_{ HandyItems::others::make_unique_weak(context->swapchain_) },
				heap_{ HandyItems::others::make_unique_weak(context->heap_) },
				back_buffer{ HandyItems::others::make_unique_weak(context->back_buffers[current_back_buffer]) } {}


			/// <summary>
			/// デストラクタ
			/// </summary>
			~FrameContext() = default;

		};
	}
}