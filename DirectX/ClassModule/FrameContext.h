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

			UINT64 frame_count{};

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
			/// フレームリソースインスタンス
			/// </summary>
			ClassModule::FrameResource* frame_resource;

			/// <summary>
			/// スワップチェーンインスタンス
			/// </summary>
			ClassObject::SwapChain* swapchain_;

			/// <summary>
			/// バックバッファインスタンス
			/// </summary>
			ClassObject::BackBuffer* back_buffer;

			/// <summary>
			/// デプスバッファインスタンス
			/// </summary>
			ClassObject::DepthBuffer* depth_buffer;

			/// <summary>
			/// ディスクリプターヒープコンテナインスタンス
			/// </summary>
			/// <returns></returns>
			Container::DescriptorHeapContainer* heap_container;
			Container::CameraObjectContainer* camera_container;
			ClassModule::MeshObject* player_;

			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// 引数付きコンストラクタ
			/// </summary>
			explicit FrameContext(
				DirectXContext* context_,
				std::uint64_t frame
			) :
				frame_count{ frame },
				dxgi_{ &context_->dxgi_ },
				device_{ &context_->device_ },
				graphic_queue{ &context_->graphic_queue },
				graphic_list{ &context_->graphic_list },
				fence_{ &context_->fence_ },
				frame_resource{ context_->frame_resources[context_->frame_resource_index->get_current_index()].get()},
				swapchain_{ &context_->swapchain_ },
				back_buffer{ context_->back_buffer_group.get_current_instance() },
				depth_buffer{ context_->depth_buffer_group.get_current_instance() },
				heap_container{ context_->heap_container.get() },
				camera_container{ context_->camera_object_container.get() },
				player_{ context_ ->player.get()}
			{}

		};
	}
}