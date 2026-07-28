#include"FrameResource.h"
#include"Factory&Builder&Helper/CommandObjectFactory.h"

using namespace render::dx12::resources;

///====================================================================
/// 初期化時間数
///====================================================================

//@brief	=== フレームリソース作成関数 ===
//@param	device	DirectX12 デバイス
//@return	作成の成否
[[nodiscard]] HRESULT FrameResource::create_frame_resource(ID3D12Device* device) {

    auto allocator = std::make_unique<object::CommandAllocator>();

    auto hr = factory::CommandObjectFactory::create_graphics_command_allocator(device, *allocator);
    if (FAILED(hr)) {
        return hr;
    }

    graphics_allocator = std::move(allocator);

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