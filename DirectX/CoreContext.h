#pragma once


#include"ClassObject/DXGI.h"
#include"ClassObject/Device.h"
#include"ClassObject/CommandQueue.h"
#include"ClassObject/CommandList.h"
#include"ClassObject/Fence.h"
#include"ClassObject/SwapChain.h"
#include"ClassModule/DescriptorGroup/BackBufferGroup.h"
#include"ClassModule/DescriptorGroup/DepthBufferGroup.h"

#include"ClassModule/FrameResource.h"
#include"ClassModule/BackBufferIndex.h"
#include"ClassModule/FrameResourceIndex.h"


/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	struct CoreContext
	{
		explicit CoreContext():
			back_buffer_index{std::make_unique<ClassModule::BackBufferIndex>()},
			frame_resource_index{std::make_unique<ClassModule::FrameResourceIndex>()}
		{
		}

		template<typename T>
		using UniquePtr = std::unique_ptr<T>;

		/// <summary>
		/// DXGIインスタンス
		/// </summary>
		ClassObject::DXGI dxgi_{};

		/// <summary>
		/// Deviceインスタンス
		/// </summary>
		ClassObject::Device device_{};

		/// <summary>
		/// 描画用コマンドキューインスタンス
		/// </summary>
		ClassObject::CommandQueue graphic_queue{};

		/// <summary>
		/// 描画用コマンドリストインスタンス
		/// </summary>
		ClassObject::CommandList graphic_list{};

		/// <summary>
		/// フェンスインスタンス
		/// </summary>
		ClassObject::Fence fence_{};

		/// <summary>
		/// フレームリソースインスタンス配列
		/// </summary>
		std::vector<UniquePtr<ClassModule::FrameResource>> frame_resources{};

		/// <summary>
		/// スワップチェーンインスタンス
		/// </summary>
		ClassObject::SwapChain swapchain_{};

		/// <summary>
		/// バックバッファインデックス管理クラス
		/// </summary>
		UniquePtr<ClassModule::BackBufferIndex> back_buffer_index{};

		/// <summary>
		/// フレームリソースインデックス管理クラス
		/// </summary>
		UniquePtr<ClassModule::FrameResourceIndex> frame_resource_index{};

		/// <summary>
		/// バックバッファグループインスタンス
		/// </summary>
		ClassModule::DescriptorGroup::BackBufferGroup back_buffer_group{};

		/// <summary>
		/// デプスバッファグループインスタンス
		/// </summary>
		ClassModule::DescriptorGroup::DepthBufferGroup depth_buffer_group{};

	};
}