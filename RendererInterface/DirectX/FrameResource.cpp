#include"FrameResource.h"
#include"Factory&Builder&Helper/CommandObjectFactory.h"

using namespace render::dx12::resources;

///====================================================================
/// 初期化時間数
///====================================================================

//@brief	=== フレームリソース作成関数 ===
//@param	index	フレームリソースインデックス番号
//@param	device	DirectX12 デバイス
//@param	heap_container	ディスクリプターヒープコンテナクラス
//@param	depth_desc	デプスバッファ設定
//@return	作成の成否
[[nodiscard]] HRESULT FrameResource::create_frame_resource(
    UINT index, ID3D12Device* device,
    container::StaticHeapContainer* heap_container, desc::DepthBufferDesc depth_desc) {


    //コマンドアロケーター作成
    auto allocator = std::make_unique<object::CommandAllocator>();

    auto hr = factory::CommandObjectFactory::create_graphics_command_allocator(device, *allocator);
    if (FAILED(hr)) {
        return hr;
    }

    graphics_allocator = std::move(allocator);


    // デプスバッファ作成
    auto depth = std::make_unique<object::DepthBuffer>();

    hr = depth->create_depth_buffer(
        device,
        heap_container->get_discriptor_heap(D3D12_DESCRIPTOR_HEAP_TYPE_DSV)->get_cpu_descriptor_handle(index),
        depth_desc);

    if (FAILED(hr)) {
        return hr;
    }

    depth_buffer = std::move(depth);

	return hr;
}


///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== フレームフェンス保存変数変更関数 ===
//@param	value	変更する値
void FrameResource::set_frame_fence_value(const UINT64& value) {
    frame_fence_value = value;
}

//@brief	=== フレームフェンス保存変数取得関数 ===
//@return	フレームフェンス保存変数の値
[[nodiscard]] UINT64 FrameResource::get_frame_fence_value()const noexcept {
    return frame_fence_value;
}

//@brief	===	描画用コマンドアロケータークラス取得関数 ===
//@return	コマンドアロケータークラス参照
[[nodiscard]] render::dx12::object::CommandAllocator* FrameResource::get_graphics_allocator()const noexcept {
	return graphics_allocator.get();
}

//@brief	===	デプスバッファクラス取得関数 ===
//@return	デプスバッファクラス参照
[[nodiscard]] render::dx12::object::DepthBuffer* FrameResource::get_deprh_buffer()const noexcept {
    return depth_buffer.get();
}