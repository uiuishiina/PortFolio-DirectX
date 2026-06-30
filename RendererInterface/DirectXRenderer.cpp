
///====================================================================
/// 前方宣言用
///====================================================================

/* -- DirectXObject --*/ 
#include"DirectX/DirectXobject/DXGI.h"
#include"DirectX/DirectXobject/Device.h"
#include"DirectX/DirectXobject/CommandQueue.h"
#include"DirectX/DirectXobject/CommandAllocator.h"
#include"DirectX/DirectXobject/GraphicsCommandList.h"
#include"DirectX/DirectXobject/DescriptorHeap.h"

/* -- 各Factory -- */
#include"DirectX/GraphicsCommandObjectFactory.h"
#include"DirectX/StaticHeapContainer.h"

///====================================================================

#include"DirectXRenderer.h"

#include"../Debug/DebugLogSystem.h"

///====================================================================

DirectXRenderer::DirectXRenderer() = default;
DirectXRenderer::~DirectXRenderer() = default;

///====================================================================
/// 初期化関数
///====================================================================

//@brief	=== 描画機能作成関数 ===
//@param	window	ウィンドウインターフェース
//@details	作成したウィンドウに描画するため引数で参照を渡す
//@return	作成の成否
[[nodiscard]] bool DirectXRenderer::create_renderer(windowInterface* window) {

	//	DXGIインスタンス生成
	dxgi_ = std::make_unique<DXGI>();
	if (FAILED(dxgi_->initialize_DXGI())) {
		DEBUG_LOG("DirectXRenderer :: create_renderer() FAILED");
		return false;
	}

	//	Deviceインスタンス生成
	device_ = std::make_unique<Device>();
	if (FAILED(device_->initialize_Device(dxgi_->get_DXGI_adaptor()))) {
		DEBUG_LOG("DirectXRenderer :: create_renderer() FAILED");
		return false;
	}

	//	描画用コマンドオブジェクト構造体インスタンス生成
	graphics_command_object = std::make_unique<GraphicsCommandObject>(buffer_size);
	if (FAILED(GraphicsCommandObjectFactory::create_GraphicsCommandObject(device_->get_device(), *graphics_command_object))) {
		DEBUG_LOG("DirectXRenderer :: create_GraphicsCommandObject() FAILED");
		return false;
	}
	
	//	初期作成ディスクリプタヒープコンテナインスタンス生成
	static_heap_container = std::make_unique<StaticHeapContainer>();
	if (FAILED(static_heap_container->create_static_heap_container(device_->get_device(),
		{
			{D3D12_DESCRIPTOR_HEAP_TYPE_RTV,buffer_size,D3D12_DESCRIPTOR_HEAP_FLAG_NONE},//RTV
		}
	))) {
		DEBUG_LOG("DirectXRenderer :: create_static_heap_container() FAILED");
		return false;
	}


	DEBUG_LOG("DirectXRenderer :: create_renderer() SUCCESS");
	return true;
}

///====================================================================
/// 実行時処理関数群
///====================================================================

//簡易的な負荷
static void func() {
	for (int i = 0; i < 100000; i++) {
		auto j = i * i;
	}
}

//@brief	=== 描画更新関数 ===
//@details	毎フレーム更新される想定
void DirectXRenderer::update_renderer() {

	func();

	frame_count++;
}

//@brief	=== 描画機能終了処理関数 ===
//@details	描画機能破棄前最終処理(非同期処理の待機など)をするための関数
void DirectXRenderer::end_renderer() {
	DEBUG_LOG("DirectXRenderer :: end_renderer()");
	DEBUG_LOG("DirectXRenderer :: frame_count = ", frame_count);
}

//@brief	=== 描画更新前関数 ===
//@details	描画機能を更新する際に先に処理する必要があるものを呼び出す関数
void DirectXRenderer::begin_update_renderer() {

}

//@brief	=== 描画更新後関数 ===
//@details	描画機能を更新した後に処理する必要があるものを呼び出す関数
void DirectXRenderer::end_update_renderer() {

}