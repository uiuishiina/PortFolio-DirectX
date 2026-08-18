#pragma once
#include"NonMovable.h"
#include<memory>
#include<vector>

///====================================================================
/// IncludeFile 参照まとめ
///====================================================================

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

///====================================================================
/// 描画名前空間
///====================================================================

namespace render {

	///====================================================================
	/// DirectX名前空間
	///====================================================================

	namespace dx12 {

		///====================================================================
		/// DirectXRendererContext クラス
		///====================================================================

		//@brief	=== DirectX描画機能インスタンス保存クラス ===
		class DirectXRendererContext final : public NonMovableBase
		{
		public:
			///====================================================================
			/// クラス設定
			///====================================================================

			//コンストラクタ,デストラクタ
			DirectXRendererContext();
			~DirectXRendererContext() = default;

			///====================================================================
			/// public メンバー変数
			///====================================================================

			/* -- 描画機能 -- */

			//@brief	== DXGIインスタンス ==
			std::unique_ptr<object::DXGI> dxgi_{};

			//@brief	== Deviceインスタンス ==
			std::unique_ptr<object::Device> device_{};

			//@brief	== 描画用コマンドキューインスタンス ==
			std::unique_ptr<object::CommandQueue> graphics_queue{};

			//@brief	== 描画用コマンドリストインスタンス ==
			std::unique_ptr<object::GraphicsCommandList> graphics_list{};

			//@brief	== スワップチェーンインスタンス ==
			std::unique_ptr<object::SwapChain> swap_chain{};

			//@brief	== Fenceインスタンス ==
			std::unique_ptr<object::Fence> fence_{};

			//@brief	== フレームリソース配列インスタンス ==
			std::vector<std::unique_ptr<resources::FrameResource>> frame_resources{};

			//@brief	== バックバッファ配列インスタンス ==
			std::vector<std::unique_ptr<object::BackBuffer>> back_buffers{};

			/* -- 描画機能コンテナ -- */

			//@brief	== シェーダーコンテナインスタンス ==
			std::unique_ptr<container::StaticShaderContainer> shader_container{};

			//@brief	== ルートシグネチャーコンテナインスタンス ==
			std::unique_ptr<container::StaticRootSignatureContainer> root_signature_container{};

			//@brief	== パイプラインステートコンテナインスタンス ==
			std::unique_ptr<container::StaticPiplineStateContainer> pipline_container{};

			//@brief	== 描画設定コンテナインスタンス ==
			std::unique_ptr<container::StaticDrawStateContainer> static_draw_state_container{};

			//@brief	== 描画パス用レンダーターゲット設定コンテナインスタンス ==
			std::unique_ptr<container::StaticRenderTargetStateContainer> static_render_target_state_container{};

			//@brief	== 描画パスコマンドコンテナインスタンス ==
			std::unique_ptr<container::StaticDrawCommandsContainer> static_draw_commands_container{};

			//@brief	== 描画パスコンテナクラスインスタンス ==
			std::unique_ptr<container::StaticDrawPassContainer> static_draw_pass_container{};


			/* -- 描画リソース各種 -- */

			//@brief	== 初期作成ディスクリプタヒープコンテナインスタンス ==
			std::unique_ptr<container::StaticHeapContainer> static_heap_container{};

			//@brief	== 初期作成描画オブジェクトコンテナインスタンス ==
			std::unique_ptr<container::StaticDrawObjectContainer> static_draw_object_container{};

			//@brief	== 描画バッファリソースコンテナインスタンス ==
			std::unique_ptr<container::StaticBufferContainer> static_buffer_container{};

		};
	};
};