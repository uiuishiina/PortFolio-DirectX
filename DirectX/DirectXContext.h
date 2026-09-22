#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Others/NonCopyableBase.h"

//	DirectX
#include"ClassObject/DXGI.h"
#include"ClassObject/Device.h"
#include"ClassObject/CommandQueue.h"
#include"ClassObject/CommandList.h"
#include"ClassObject/Fence.h"
#include"ClassObject/SwapChain.h"
#include"ClassObject/DescriptorHeap.h"
#include"ClassObject/GPUResource/RenderTarget/BackBuffer.h"

#include"ClassModule/FrameResource.h"


//	その他
#include<vector>
#include<optional>
#include<cstdint>
#include<memory>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// DirectXオブジェクトインスタンスまとめクラス
	/// </summary>
	struct DirectXContext final : HandyItems::others::NonCopyableMovableBase
	{

		template<typename T>
		using UniquePtr = std::unique_ptr<T>;

	public:
		/* ========== Publicメンバー関数 ========== */

		//	コンストラクタ削除
		DirectXContext() = delete;

		/// <summary>
		/// 引数付きコンストラクタ
		/// </summary>
		/// <param name="back_buffer_size">バックバッファサイズ</param>
		/// <param name="frame_resource_size">フレームリソースサイズ</param>
		DirectXContext(
			std::uint32_t back_buffer_size,
			std::uint32_t frame_resource_size
		) {

			/* -- Core -- */

			dxgi_ = std::make_unique<ClassObject::DXGI>();
			device_ = std::make_unique<ClassObject::Device>();
			graphic_queue = std::make_unique<ClassObject::CommandQueue>();
			graphic_list = std::make_unique<ClassObject::CommandList>();
			fence_ = std::make_unique<ClassObject::Fence>();

			frame_resources.resize(frame_resource_size);

			for (auto& resource : frame_resources) {
				resource = std::make_unique<ClassModule::FrameResource>(fence_.get());
			}

			swapchain_ = std::make_unique<ClassObject::SwapChain>();
			heap_ = std::make_unique<ClassObject::DescriptorHeap>();

			back_buffers.resize(back_buffer_size);

			for (auto& back_buffer : back_buffers) {
				back_buffer = std::make_unique<ClassObject::BackBuffer>();
			}


			/* -- Container -- */

			//pass_container = std::make_unique<Container::PassContainer>();
		}

		/// <summary>
		/// デストラクタ
		/// </summary>
		~DirectXContext() = default;

		/* ========== Publicメンバー変数 ========== */

		/* -- Core -- */

		/// <summary>
		/// DXGIインスタンス
		/// </summary>
		UniquePtr<ClassObject::DXGI> dxgi_{};

		/// <summary>
		/// Deviceインスタンス
		/// </summary>
		UniquePtr<ClassObject::Device> device_{};

		/// <summary>
		/// 描画用コマンドキューインスタンス
		/// </summary>
		UniquePtr<ClassObject::CommandQueue> graphic_queue{};

		/// <summary>
		/// 描画用コマンドリストインスタンス
		/// </summary>
		UniquePtr<ClassObject::CommandList> graphic_list{};

		/// <summary>
		/// フェンスインスタンス
		/// </summary>
		UniquePtr<ClassObject::Fence> fence_{};

		/// <summary>
		/// フレームリソースインスタンス配列
		/// </summary>
		std::vector<UniquePtr<ClassModule::FrameResource>> frame_resources{};

		/// <summary>
		/// スワップチェーンインスタンス
		/// </summary>
		UniquePtr<ClassObject::SwapChain> swapchain_{};

		/// <summary>
		/// ディスクリプタヒープインスタンス
		/// </summary>
		UniquePtr<ClassObject::DescriptorHeap> heap_{};
		
		/// <summary>
		/// バックバッファインスタンス配列
		/// </summary>
		std::vector<UniquePtr<ClassObject::BackBuffer>> back_buffers{};


		/* -- Container -- */

		/// <summary>
		/// 描画パスコンテナインスタンス
		/// </summary>
		//UniquePtr<Container::PassContainer> pass_container{};

	};
}