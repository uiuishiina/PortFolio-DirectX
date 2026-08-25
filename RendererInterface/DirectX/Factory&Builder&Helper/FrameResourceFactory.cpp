#include"FrameResourceFactory.h"

using namespace render::dx12::factory;

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== フレームリソース作成関数 ===
//@param	context		DirectX描画機能インスタンス保存クラス
//@param	window_size	ウィンドウサイズ
//@param	size		フレームリソースサイズ
//@param	heaps_desc	ディスクリプタヒープ設定配列
//@return	作成の成否
[[nodiscard]] HRESULT FrameResourceFactory::create_frame_resources(DirectXRendererContext* context, WindowSize window_size,
	UINT size, const std::vector<desc::DescriptorHeapDesc>& heaps_desc) {

	context->frame_resources.resize(size);

	//	仮配列を作成
	std::vector<std::unique_ptr<resources::FrameResource>> temp{};
	temp.resize(size);

	//	ウィンドウのサイズ分のバッファを指定
	desc::DepthBufferDesc depth_desc{};
	depth_desc.width = window_size.width;
	depth_desc.height = window_size.height;

	//	サイズ分インスタンス & リソース作成
	for (UINT i = 0; i < size; i++) {
		temp[i] = std::make_unique<resources::FrameResource>();
		const auto hr = temp[i]->create_frame_resource(context->device_->get_device(),
			depth_desc, heaps_desc);
		if (FAILED(hr)) {
			return hr;
		}
	}
	//	作成できたならMoveで受け渡し
	context->frame_resources = std::move(temp);

	return S_OK;
}