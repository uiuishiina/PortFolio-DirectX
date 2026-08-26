#include"FrameResource.h"
#include"Factory&Builder&Helper/CommandObjectFactory.h"
#include"DirectXobject/ConstantBuffer.h"
#include<DirectXMath.h>

using namespace render::dx12::resources;

///====================================================================
/// 初期化時間数
///====================================================================

//@brief	=== フレームリソース作成関数 ===
//@param	device	DirectX12 デバイス
//@param	depth_desc	デプスバッファ設定
//@param	heaps_desc	ディスクリプタヒープ設定配列
//@return	作成の成否
[[nodiscard]] HRESULT FrameResource::create_frame_resource(
    ID3D12Device* device,
    desc::DepthBufferDesc depth_desc, const std::vector<desc::DescriptorHeapDesc>& heaps_desc) {

    //コマンドアロケーター作成
    {
        auto allocator = std::make_unique<object::CommandAllocator>();

        const auto hr = factory::CommandObjectFactory::create_graphics_command_allocator(device, *allocator);
        if (FAILED(hr)) {
            return hr;
        }

        graphics_allocator = std::move(allocator);
    }


    //  ディスクリプタヒープ作成
    {
        frame_heap_container = std::make_unique<container::StaticHeapContainer>();

        auto heap = heaps_desc;

        //  内部で用意(外部にするかは検討)
        heap.push_back({ D3D12_DESCRIPTOR_HEAP_TYPE_DSV,1,D3D12_DESCRIPTOR_HEAP_FLAG_NONE });
        heap.push_back({ D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,1,D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE });

        const auto hr = frame_heap_container->create_static_heap_container(device, heap);
        if (FAILED(hr)) {
            return hr;
        }
    }

    // デプスバッファ作成
    {
        auto depth = std::make_unique<object::DepthBuffer>();

        const auto hr = depth->create_depth_buffer(
            device,
            frame_heap_container->get_discriptor_heap(D3D12_DESCRIPTOR_HEAP_TYPE_DSV)->get_cpu_descriptor_handle(0),
            depth_desc);
        if (FAILED(hr)) {
            return hr;
        }

        depth_buffer = std::move(depth);
    }

    upload_resource_container = std::make_unique<container::UploadBufferContainer>();

    {
        DirectX::XMMATRIX transform = {};

        auto handle = frame_heap_container->get_handles(device, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 0);
        auto constantBuffer = std::make_unique<object::ConstantBuffer>();
        const auto hr = constantBuffer->create_constant_buffer(device, handle, &transform, sizeof(DirectX::XMMATRIX));
        if (FAILED(hr)) {
            return hr;
        }

        if (!upload_resource_container->register_buffer("constant", std::move(constantBuffer))) {
            return false;
        }
    }


	return S_OK;
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