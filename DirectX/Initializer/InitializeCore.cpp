
/* ========== Includeファイル ========== */

#include "InitializeCore.h"

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
	std::uint32_t back_buffer_size
) {

	HRESULT hr{};

	//	DXGI作成
	hr = context->dxgi_->initialize_DXGI();
	if (FAILED(hr)) {
		return hr;
	}

	//	Device作成
	hr = context->device_->create_device(context->dxgi_->get_adapter());
	if (FAILED(hr)) {
		return hr;
	}

	//	描画用コマンドキュー作成
	hr = context->graphic_queue->create_queue(
		context->device_->get(),
		D3D12_COMMAND_LIST_TYPE_DIRECT
	);
	if (FAILED(hr)) {
		return hr;
	}

	//	描画用コマンドアロケーター作成
	for (auto& resource : context->frame_resources) {

		hr = resource->get_allocator()->create_allocator(
			context->device_->get(),
			D3D12_COMMAND_LIST_TYPE_DIRECT
		);
		if (FAILED(hr)) {
			return hr;
		}
	}

	//	描画用コマンドリスト作成
	hr = context->graphic_list->create_list(
		context->device_->get(),
		context->frame_resources[0]->get_allocator()->get(),
		D3D12_COMMAND_LIST_TYPE_DIRECT
	);
	if (FAILED(hr)) {
		return hr;
	}

	//	フェンス作成
	hr = context->fence_->create_fence(
		context->device_->get()
	);
	if (FAILED(hr)) {
		return hr;
	}

	//	スワップチェーン作成
	hr = context->swapchain_->create_swapchain(
		context->dxgi_->get_factory(),
		context->graphic_queue->get(),
		hwnd,
		width,
		height,
		back_buffer_size
	);
	if (FAILED(hr)) {
		return hr;
	}

	//	ディスクリプタヒープ作成
	hr = context->heap_->create_descriptor_heap(
		context->device_->get(),
		{ D3D12_DESCRIPTOR_HEAP_TYPE_RTV ,2,D3D12_DESCRIPTOR_HEAP_FLAG_NONE }
	);
	if (FAILED(hr)) {
		return hr;
	}

	//	バックバッファ作成
	auto& buffers = context->back_buffers;
	for (std::size_t i = 0; i < buffers.size(); ++i) {

		hr = buffers[i]->create_back_buffer(
			context->device_->get(),
			context->swapchain_->get(),
			context->heap_->get_CPU_handle(static_cast<UINT>(i)),
			static_cast<UINT>(i)
		);
		if (FAILED(hr)) {
			return hr;
		}
	}

	return S_OK;
}