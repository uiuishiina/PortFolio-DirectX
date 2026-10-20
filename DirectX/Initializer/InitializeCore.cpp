
/* ========== Includeファイル ========== */

#include"InitializeCore.h"

#include"../Container/DescriptorHeapContainer.h"

using namespace DirectX;

/* ========== Publicメンバー関数 ========== */

/// <summary>
/// コア機能初期化関数
/// </summary>
/// <param name="context">DirectXオブジェクトインスタンス構造体参照</param>
/// <returns>初期化の成否</returns>
[[nodiscard]] HRESULT Initialize::InitializeCore::initialize_core(
	DirectXContext* context,
	std::uint32_t back_buffer_size,
	desc::CoreDesc& desc
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

	//	フレームリソース作成
	for (auto& resource : context->frame_resources) {

		//	描画用コマンドアロケーター作成
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
		desc.hwnd,
		desc.width,
		desc.height,
		back_buffer_size
	);
	if (FAILED(hr)) {
		return hr;
	}

	const auto frame_size = context->frame_resources.size();

	//	ディスクリプタヒープ作成
	for (auto& heap_desc : desc.heap_descs) {

		auto heap_manager = std::make_unique<ClassModule::HeapIndexManager>();

		hr = heap_manager->create_heap(
			context->device_->get(),
			heap_desc,
			static_cast<UINT>(frame_size)
		);
		if (FAILED(hr)) {
			return hr;
		}

		//	コンテナに追加
		if (!context->heap_container->add_heap_manager(
			Container::DescriptorHeapKey{ heap_desc.type_ },
			std::move(heap_manager)
		)) {

			return E_FAIL;
		}
	}

	{
		//	バックバッファ作成
		auto& back_buffers = context->back_buffers;
		auto rtv_heap = context->heap_container->get_heap_manager(
			Container::DescriptorHeapKey{ D3D12_DESCRIPTOR_HEAP_TYPE_RTV }
		)->get_heap();

		for (std::size_t i = 0; i < back_buffers.size(); ++i) {

			hr = back_buffers[i]->create_back_buffer(
				context->device_->get(),
				context->swapchain_->get(),
				rtv_heap->get_CPU_handle(static_cast<UINT>(i)),
				static_cast<UINT>(i)
			);
			if (FAILED(hr)) {
				return hr;
			}
		}
	}
	{

		//	デプスバッファ作成
		auto& depth_buffers = context->depth_buffers;
		auto dsv_heap = context->heap_container->get_heap_manager(
			Container::DescriptorHeapKey{ D3D12_DESCRIPTOR_HEAP_TYPE_DSV }
		)->get_heap();

		ClassObject::desc::DepthBufferDesc depth_desc{};

		depth_desc.width = desc.width;
		depth_desc.height = desc.height;

		for (std::size_t i = 0; i < depth_buffers.size(); ++i) {

			hr = depth_buffers[i]->creata_depth_buffer(
				context->device_->get(),
				dsv_heap->get_CPU_handle(static_cast<UINT>(i)),
				depth_desc
			);
			if (FAILED(hr)) {
				return hr;
			}
		}
	}

	return S_OK;
}