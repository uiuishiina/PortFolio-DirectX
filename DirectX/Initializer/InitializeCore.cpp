
/* ========== Includeファイル ========== */

#include"InitializeCore.h"

#include"../Container/DescriptorHeapContainer.h"

#include"Debug/DebugLogSystem.h"

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
	std::uint32_t frame_resource_size,
	const desc::CoreDesc& desc
) {

	HRESULT hr{};
	{
		//	DXGI作成
		hr = context->dxgi_.initialize_DXGI();
		if (FAILED(hr)) {
			DEBUG_ERROR_LOG("initialize_DXGI FAILED");
			return hr;
		}

		//	Device作成
		hr = context->device_.create_device(context->dxgi_.get_adapter());
		if (FAILED(hr)) {
			DEBUG_ERROR_LOG("create_device FAILED");
			return hr;
		}
	}

	//	描画用コマンドキュー作成
	hr = context->graphic_queue.create_queue(
		context->device_,
		D3D12_COMMAND_LIST_TYPE_DIRECT
	);
	if (FAILED(hr)) {
		DEBUG_ERROR_LOG("create_queue FAILED");
		return hr;
	}

	//	フェンス作成
	hr = context->fence_.create_fence(
		context->device_
	);
	if (FAILED(hr)) {
		DEBUG_ERROR_LOG("create_fence FAILED");
		return hr;
	}

	//	フレームリソース作成
	context->frame_resources.resize(frame_resource_size);

	//	フレームリソース作成
	for (auto& resource : context->frame_resources) {

		resource = std::make_unique<ClassModule::FrameResource>();
		const auto hr = resource->initialize_resources(
			context->device_,
			&context->fence_
		);
		if (FAILED(hr)) {
			DEBUG_ERROR_LOG("initialize_resources FAILED");
			return hr;
		}
	}

	//	描画用コマンドリスト作成
	hr = context->graphic_list.create_list(
		context->device_,
		context->frame_resources[0]->get_allocator().get(),
		D3D12_COMMAND_LIST_TYPE_DIRECT
	);
	if (FAILED(hr)) {
		DEBUG_ERROR_LOG("create_list FAILED");
		return hr;
	}

	//	スワップチェーン作成
	hr = context->swapchain_.create_swapchain(
		context->dxgi_.get_factory(),
		context->graphic_queue.get(),
		desc.hwnd,
		desc.width,
		desc.height,
		back_buffer_size
	);
	if (FAILED(hr)) {
		DEBUG_ERROR_LOG("create_swapchain FAILED");
		return hr;
	}

	//	現在インデックス管理クラス作成
	if (!context->back_buffer_index->initialize_index(*context->swapchain_.get())) {
		DEBUG_ERROR_LOG("back_buffer_index FAILED");
		return E_FAIL;
	}

	if (!context->frame_resource_index->initialize_index(context->frame_resources.size())) {
		DEBUG_ERROR_LOG("frame_resource_index FAILED");
		return E_FAIL;
	}

	//	ディスクリプタヒープ作成
	for (auto& heap_desc : desc.heap_descs) {

		auto heap_manager = std::make_unique<ClassModule::DescriptorHeapAllocator>();

		hr = heap_manager->create_heap(
			context->device_,
			heap_desc,
			static_cast<UINT>(context->back_buffer_index->get_size()),
			static_cast<UINT>(context->frame_resource_index->get_size())
		);
		if (FAILED(hr)) {
			DEBUG_ERROR_LOG("create_heap FAILED");
			return hr;
		}

		//	コンテナに追加
		if (!context->heap_container->add_heap_allocator(
			Container::DescriptorHeapKey{ heap_desc.type_ },
			std::move(heap_manager)
		)) {
			DEBUG_ERROR_LOG("add_heap_allocator FAILED");
			return E_FAIL;
		}
	}

	{
		//	バックバッファ作成
		auto rtv_heap__allocator = context->heap_container->get_heap_allocator(
			Container::DescriptorHeapKey{ D3D12_DESCRIPTOR_HEAP_TYPE_RTV }
		);

		hr = context->back_buffer_group.create_back_buffer_group(
			context->device_,
			context->swapchain_.get(),
			rtv_heap__allocator,
			context->back_buffer_index.get()
		);
		if (FAILED(hr)) {
			DEBUG_ERROR_LOG("create_back_buffer_group FAILED");
			return hr;
		}
	}
	{

		//	デプスバッファ作成
		auto dsv_heap_allocator = context->heap_container->get_heap_allocator(
			Container::DescriptorHeapKey{ D3D12_DESCRIPTOR_HEAP_TYPE_DSV }
		);

		ClassObject::desc::DepthBufferDesc depth_desc{};

		depth_desc.width = desc.width;
		depth_desc.height = desc.height;

		hr = context->depth_buffer_group.create_depth_buffer_group(
			context->device_,
			dsv_heap_allocator,
			context->back_buffer_index.get(),
			depth_desc
		);
		if (FAILED(hr)) {
			DEBUG_ERROR_LOG("create_depth_buffer_group FAILED");
			return hr;
		}
	}

	return S_OK;
}