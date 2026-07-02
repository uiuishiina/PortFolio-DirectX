#include"FrameResource.h"

#include"CommandObjectFactory.h"

///====================================================================
/// 初期化時間数
///====================================================================

//@brief	=== フレームリソース作成関数 ===
//@param	device	DirectX12 デバイス
//@return	作成の成否
[[nodiscard]] HRESULT FrameResource::create_frame_resource(ID3D12Device* device) {

    auto allocator = std::make_unique<CommandAllocator>();

    auto hr = CommandObjectFactory::create_graphics_command_allocator(device, *allocator);
    if (FAILED(hr)) {
        return hr;
    }

    graphics_allocator = std::move(allocator);

	return S_OK;
}


///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	===	描画用コマンドアロケータークラス参照取得関数 ===
//@return	コマンドアロケータークラスインスタンス
[[nodiscard]] CommandAllocator* FrameResource::get_graphics_allocator()const noexcept {
	return graphics_allocator.get();
}