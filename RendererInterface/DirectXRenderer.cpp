
///====================================================================
/// 前方宣言用
///====================================================================

#include"DirectX/DXGI.h"
#include"DirectX/Device.h"

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
	if(FAILED(dxgi_->initialize_DXGI())) {
		DEBUG_LOG("DirectXRenderer :: create_renderer() FAILED");
		return false;
	}

	//	Deviceインスタンス生成
	device_ = std::make_unique<Device>();
	if(FAILED(device_->initialize_Device(dxgi_->get_DXGI_adaptor()))) {
		DEBUG_LOG("DirectXRenderer :: create_renderer() FAILED");
		return false;
	}



	DEBUG_LOG("DirectXRenderer :: create_renderer() SUCCESS");
	return true;
}

///====================================================================
/// 実行時処理関数群
///====================================================================

//@brief	=== 描画更新関数 ===
//@details	毎フレーム更新される想定
void DirectXRenderer::update_renderer() {

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