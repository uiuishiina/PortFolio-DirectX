#pragma once
#include"Others/NonCopyableBase.h"
#include<memory>
#include<vector>

/* ==================================================================== */
// IncludeFile まとめ
/* ==================================================================== */

/* -- DirectXObject --*/
#include"DirectXobject/DXGI.h"
#include"DirectXobject/Device.h"
#include"DirectXobject/CommandQueue.h"
#include"DirectXobject/CommandAllocator.h"
#include"DirectXobject/GraphicsCommandList.h"
#include"DirectXobject/DescriptorHeap.h"
#include"DirectXobject/SwapChain.h"
#include"DirectXobject/RenderTarget.h"
#include"DirectXobject/BackBuffer.h"
#include"DirectXobject/DepthBuffer.h"
#include"DirectXobject/Fence.h"
#include"DirectXobject/RootSignature.h"
#include"DirectXobject/ShaderCompiler.h"
#include"DirectXobject/PipelineState.h"
#include"DirectXobject/Mesh.h"

/* -- DirectXObjectを利用したまとめクラス -- */
#include"FrameResource.h"
#include"Container/StaticHeapContainer.h"
#include"Container/StaticShaderContainer.h"
#include"Container/StaticRootSignatureContainer.h"
#include"Container/StaticPiplineStateContainer.h"
#include"Container/StaticBufferContainer.h"
#include"Container/StaticDrawStateContainer.h"
#include"Container/StaticRenderTargetStateContainer.h"
#include"Container/StaticDrawCommandsContainer.h"
#include"Container/StaticDrawPassContainer.h"
#include"Container/StaticDrawObjectContainer.h"

/// <summary>
/// 描画機能名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		/// <summary>
		/// DirectX描画機能インスタンス保存クラス
		/// </summary>
		class DirectXRendererContext final : public others::NonCopyableBase
		{
		public:
			/* ========== クラス設定 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			/// <details>
			/// unique_ptr使用メンバー変数のインスタンスを作成する
			/// フレームリソース各種は別でインスタンス作成
			/// </details>
			DirectXRendererContext();

			/// <summary>
			/// デストラクタ
			/// </summary>
			~DirectXRendererContext() = default;

			/* ========== Publicメンバー変数 ========== */

			/* -- 描画機能 -- */

			/// <summary>
			/// DXGIインスタンス
			/// </summary>
			std::unique_ptr<object::DXGI> dxgi_{};

			/// <summary>
			/// Deviceインスタンス
			/// </summary>
			std::unique_ptr<object::Device> device_{};

			/// <summary>
			/// 描画用コマンドキューインスタンス
			/// </summary>
			std::unique_ptr<object::CommandQueue> graphics_queue{};

			/// <summary>
			/// 描画用コマンドリストインスタンス
			/// </summary>
			std::unique_ptr<object::GraphicsCommandList> graphics_list{};

			/// <summary>
			/// スワップチェーンインスタンス
			/// </summary>
			std::unique_ptr<object::SwapChain> swap_chain{};

			/// <summary>
			/// Fenceインスタンス
			/// </summary>
			std::unique_ptr<object::Fence> fence_{};

			/// <summary>
			/// フレームリソースインスタンス配列
			/// </summary>
			std::vector<std::unique_ptr<resources::FrameResource>> frame_resources{};

			/// <summary>
			/// バックバッファインスタンス配列
			/// </summary>
			std::vector<std::unique_ptr<object::BackBuffer>> back_buffers{};


			/* -- 描画機能コンテナ -- */

			/// <summary>
			/// シェーダーコンテナインスタンス
			/// </summary>
			std::unique_ptr<container::StaticShaderContainer> shader_container{};

			/// <summary>
			/// ルートシグネチャーコンテナインスタンス
			/// </summary>
			std::unique_ptr<container::StaticRootSignatureContainer> root_signature_container{};

			/// <summary>
			/// パイプラインステートコンテナインスタンス
			/// </summary>
			std::unique_ptr<container::StaticPiplineStateContainer> pipline_container{};

			/// <summary>
			/// 描画パス設定コンテナインスタンス
			/// </summary>
			std::unique_ptr<container::StaticDrawStateContainer> static_draw_state_container{};

			/// <summary>
			/// 描画パス用レンダーターゲット設定コンテナインスタンス
			/// </summary>
			std::unique_ptr<container::StaticRenderTargetStateContainer> static_render_target_state_container{};

			/// <summary>
			/// 描画コマンドコンテナインスタンス
			/// </summary>
			std::unique_ptr<container::StaticDrawCommandsContainer> static_draw_commands_container{};

			/// <summary>
			/// 描画パスコンテナクラスインスタンス
			/// </summary>
			std::unique_ptr<container::StaticDrawPassContainer> static_draw_pass_container{};


			/* -- 描画リソース各種 -- */

			/// <summary>
			/// 初期作成ディスクリプタヒープコンテナインスタンス
			/// </summary>
			std::unique_ptr<container::StaticHeapContainer> static_heap_container{};

			/// <summary>
			/// 初期作成描画オブジェクトコンテナインスタンス
			/// </summary>
			std::unique_ptr<container::StaticDrawObjectContainer> static_draw_object_container{};

			/// <summary>
			/// 描画バッファリソースコンテナインスタンス
			/// </summary>
			std::unique_ptr<container::StaticBufferContainer> static_buffer_container{};

		};
	}
}