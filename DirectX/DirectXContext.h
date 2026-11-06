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
#include"ClassModule/DescriptorGroup/BackBufferGroup.h"
#include"ClassModule/DescriptorGroup/DepthBufferGroup.h"

#include"ClassModule/FrameResource.h"

#include"ClassModule/BackBufferIndex.h"
#include"ClassModule/FrameResourceIndex.h"

#include"ClassModule/DrawObject/MeshObject.h"

//	その他
#include<vector>
#include<optional>
#include<cstdint>
#include<memory>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/* ========== 前方宣言 ========== */

	namespace Container {

		class DescriptorHeapContainer;
		class PassContainer;
		class ShaderContainer;
		class RootSignatureContainer;
		class PiplineStateContainer;
		class DrawObjectContainer;
		class CameraObjectContainer;
	}


	/// <summary>
	/// DirectXオブジェクトインスタンスまとめクラス
	/// </summary>
	struct DirectXContext final : HandyItems::others::NonCopyableMovableBase
	{
		template<typename T>
		using UniquePtr = std::unique_ptr<T>;
	public:
		/* ========== Publicメンバー関数 ========== */

		/// <summary>
		/// コンストラクタ
		/// </summary>
		DirectXContext();

		/// <summary>
		/// デストラクタ
		/// </summary>
		~DirectXContext();

		/* ========== Publicメンバー変数 ========== */

		/* -- Container -- */

		/// <summary>
		/// ディスクリプタヒープコンテナインスタンス
		/// </summary>
		UniquePtr<Container::DescriptorHeapContainer> heap_container{};

		/// <summary>
		/// 描画パスコンテナインスタンス
		/// </summary>
		UniquePtr<Container::PassContainer> pass_container{};

		/// <summary>
		/// HLSLシェーダーコンテナインスタンス
		/// </summary>
		UniquePtr<Container::ShaderContainer> shader_container{};

		/// <summary>
		/// ルートシグネチャーコンテナインスタンス
		/// </summary>
		UniquePtr<Container::RootSignatureContainer> root_signature_container{};

		/// <summary>
		/// パイプラインステートコンテナインスタンス
		/// </summary>
		UniquePtr<Container::PiplineStateContainer> pipline_state_container{};

		/// <summary>
		/// 描画オブジェクトコンテナインスタンス
		/// </summary>
		UniquePtr<Container::DrawObjectContainer> draw_object_container{};

		/// <summary>
		/// カメラオブジェクトコンテナインスタンス
		/// </summary>
		UniquePtr<Container::CameraObjectContainer> camera_object_container{};

		/* -- Core -- */

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


		//疑似的にプレイヤーを生成
		UniquePtr<ClassModule::MeshObject> player{};

	};
}