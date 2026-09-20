
/* ========== Includeファイル ========== */

#include "InitializeCore.h"


//	DirectX... [ 初期化するオブジェクトのみ #include ]
#include"../ClassObject/DXGI.h"
#include"../ClassObject/Device.h"
#include"../ClassObject/CommandQueue.h"
#include"../ClassObject/CommandList.h"
#include"../ClassObject/SwapChain.h"
#include"../ClassObject/DescriptorHeap.h"
#include"../ClassObject/GPUResource/RenderTarget/BackBuffer.h"

#include"../ClassModule/FrameResource.h"

using namespace DirectX;

/* ========== Publicメンバー関数 ========== */

/// <summary>
/// コア機能初期化関数
/// </summary>
/// <param name="context">DirectXオブジェクトインスタンス構造体参照</param>
/// <returns>初期化の成否</returns>
[[nodiscard]] HRESULT Initialize::InitializeCore::initialize_core(
	DirectXContext* context,
	HWND hwnd,
	std::uint32_t width,
	std::uint32_t height,
	UINT back_buffer_size
) {

	//	インスタンスチェック
	bool value[2] = {
		context->get_dxgi().check(),
		context->get_device().check()
	};

	for (auto p : value) {
		if (!p) {
			return E_FAIL;
		}
	}


	HRESULT hr{};

	//	DXGI作成
	hr = context->get_dxgi()->initialize_DXGI();
	if (FAILED(hr)) {
		return hr;
	}

	//	Device作成
	hr = context->get_device()->create_device(context->get_dxgi()->get_adapter());
	if (FAILED(hr)) {
		return hr;
	}

	//	描画用コマンドキュー作成
	hr = context->get_queue()->create_queue(
		context->get_device()->get(),
		D3D12_COMMAND_LIST_TYPE_DIRECT
	);
	if (FAILED(hr)) {
		return hr;
	}

	//	描画用コマンドアロケーター作成
	for (auto& resource : context->get_frame_resources()) {

		hr = resource->get_allocator()->create_allocator(
			context->get_device()->get(),
			D3D12_COMMAND_LIST_TYPE_DIRECT
		);
		if (FAILED(hr)) {
			return hr;
		}
	}

	//	描画用コマンドリスト作成
	hr = context->get_list()->create_list(
		context->get_device()->get(),
		context->get_frame_resource(0).value()->get_allocator()->get(),
		D3D12_COMMAND_LIST_TYPE_DIRECT
	);
	if (FAILED(hr)) {
		return hr;
	}

	//	フェンス作成
	hr = context->get_fence()->create_fence(
		context->get_device()->get()
	);
	if (FAILED(hr)) {
		return hr;
	}

	//	スワップチェーン作成
	hr = context->get_swapchain()->create_swapchain(
		context->get_dxgi()->get_factory(),
		context->get_queue()->get(),
		hwnd,
		width,
		height,
		back_buffer_size
	);
	if (FAILED(hr)) {
		return hr;
	}

	//	ディスクリプタヒープ作成
	hr = context->get_heap()->create_descriptor_heap(
		context->get_device()->get(),
		{ D3D12_DESCRIPTOR_HEAP_TYPE_RTV ,2,D3D12_DESCRIPTOR_HEAP_FLAG_NONE }
	);
	if (FAILED(hr)) {
		return hr;
	}

	//	バックバッファ作成
	auto buffers = context->get_back_buffers();
	for (std::size_t i = 0; i < buffers.size(); ++i) {

		hr = buffers[i]->create_back_buffer(
			context->get_device()->get(),
			context->get_swapchain()->get(),
			context->get_heap()->get_CPU_handle(static_cast<UINT>(i)),
			i
		);
		if (FAILED(hr)) {
			return hr;
		}
	}

	return S_OK;
}