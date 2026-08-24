#include "DirectXRendererContext.h"

using namespace render::dx12;

///====================================================================
/// コンストラクタ
///====================================================================

//@breif	=== コンストラクタ ===
//@details	unique_ptr使用メンバー変数のインスタンスを作成する
//@details	フレームリソース各種は別でインスタンス作成
DirectXRendererContext::DirectXRendererContext() {

	//各種オブジェクト
	dxgi_ = std::make_unique<object::DXGI>();
	device_ = std::make_unique<object::Device>();

	graphics_queue = std::make_unique<object::CommandQueue>();
	graphics_list = std::make_unique<object::GraphicsCommandList>();
	swap_chain = std::make_unique<object::SwapChain>();
	fence_ = std::make_unique<object::Fence>();

	//各種コンテナクラス
	static_heap_container = std::make_unique<container::StaticHeapContainer>();
	shader_container = std::make_unique<container::StaticShaderContainer>();
	root_signature_container = std::make_unique<container::StaticRootSignatureContainer>();
	pipline_container = std::make_unique<container::StaticPiplineStateContainer>();
	static_buffer_container = std::make_unique<container::StaticBufferContainer>();

	static_draw_state_container = std::make_unique<container::StaticDrawStateContainer>();
	static_render_target_state_container = std::make_unique<container::StaticRenderTargetStateContainer>();
	static_draw_commands_container = std::make_unique<container::StaticDrawCommandsContainer>();
	static_draw_pass_container = std::make_unique<container::StaticDrawPassContainer>();

	static_draw_object_container = std::make_unique<container::StaticDrawObjectContainer>();
}