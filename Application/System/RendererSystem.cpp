#include"RendererSystem.h"

#include"../../DirectX/CoreContext.h"
#include"../../DirectX/ContainerContext.h"
#include"../../DirectX/ClassModule/DescriptorGroup/ConstantBufferGroup.h"

using namespace DirectX;

namespace
{
	constexpr int transform_register_index = 0;
}

namespace App
{

	class InitializeRendererCore
	{
	public:

		static bool init_core(
			App::DebugSystem* debug,
			App::WindowsSystem* window,
			CoreContext* core,
			ContainerContext* container,
			uint32_t buffer_size,
			uint32_t resource_size,
			std::initializer_list<DirectX::ClassModule::desc::DescriptorHeapAllocatorDesc> heap_descs
		)
		{

			HRESULT hr{};
			{
				//	DXGI作成
				hr = core->dxgi_.initialize_DXGI();
				if (FAILED(hr)) {
					debug->debug_error_log(
						"initialize_DXGI FAILED",
						debug->to_HRESULT(hr)
					);
					return false;
				}

				//	Device作成
				hr = core->device_.create_device(core->dxgi_.get_adapter());
				if (FAILED(hr)) {
					debug->debug_error_log(
						"create_device FAILED",
						debug->to_HRESULT(hr)
					);
					return false;
				}
			}

			auto* device = core->device_.get();

			//	描画用コマンドキュー作成
			hr = core->graphic_queue.create_queue(
				device,
				D3D12_COMMAND_LIST_TYPE_DIRECT
			);
			if (FAILED(hr)) {
				debug->debug_error_log(
					"create_queue FAILED",
					debug->to_HRESULT(hr)
				);
				return false;
			}

			//	フェンス作成
			hr = core->fence_.create_fence(
				device
			);
			if (FAILED(hr)) {
				debug->debug_error_log(
					"create_fence FAILED",
					debug->to_HRESULT(hr)
				);
				return false;
			}

			//	フレームリソース作成
			core->frame_resources.resize(resource_size);

			//	フレームリソース作成
			for (auto& resource : core->frame_resources) {

				resource = std::make_unique<ClassModule::FrameResource>();
				const auto hr = resource->initialize_resources(
					device,
					&core->fence_
				);
				if (FAILED(hr)) {
					debug->debug_error_log(
						"initialize_resources FAILED",
						debug->to_HRESULT(hr)
					);
					return false;
				}
			}

			//	描画用コマンドリスト作成
			hr = core->graphic_list.create_list(
				device,
				core->frame_resources[0]->get_allocator().get(),
				D3D12_COMMAND_LIST_TYPE_DIRECT
			);
			if (FAILED(hr)) {
				debug->debug_error_log(
					"create_list FAILED",
					debug->to_HRESULT(hr)
				);
				return false;
			}

			auto [w, h] = window->get_window_size();

			//	スワップチェーン作成
			hr = core->swapchain_.create_swapchain(
				core->dxgi_.get_factory(),
				core->graphic_queue.get(),
				window->get_hwnd(),
				w,
				h,
				buffer_size
			);
			if (FAILED(hr)) {
				debug->debug_error_log(
					"create_swapchain FAILED",
					debug->to_HRESULT(hr)
				);
				return false;
			}

			//	現在インデックス管理クラス作成
			if (!core->back_buffer_index->initialize_index(core->swapchain_.get())) {
				debug->debug_error_log(
					"back_buffer_index FAILED",
					debug->to_HRESULT(hr)
				);
				return false;
			}

			if (!core->frame_resource_index->initialize_index(core->frame_resources.size())) {
				debug->debug_error_log(
					"frame_resource_index FAILED",
					debug->to_HRESULT(hr)
				);
				return false;
			}

			//	ディスクリプタヒープ作成
			for (auto& heap_desc : heap_descs) {

				auto heap_manager = std::make_unique<ClassModule::DescriptorHeapAllocator>();

				hr = heap_manager->create_heap(
					device,
					heap_desc,
					static_cast<UINT>(core->back_buffer_index->get_size()),
					static_cast<UINT>(core->frame_resource_index->get_size())
				);
				if (FAILED(hr)) {
					debug->debug_error_log(
						"create_heap FAILED",
						debug->to_HRESULT(hr)
					);
					return false;
				}

				//	コンテナに追加
				if (!container->heap_container.add_heap_allocator(
					Container::DescriptorHeapKey{ heap_desc.type_ },
					std::move(heap_manager)
				)) {
					debug->debug_error_log(
						"add_heap_allocator FAILED",
						debug->to_HRESULT(hr)
					);
					return false;
				}
			}

			{
				//	バックバッファ作成
				auto rtv_heap__allocator = container->heap_container.get_heap_allocator(
					Container::DescriptorHeapKey{ D3D12_DESCRIPTOR_HEAP_TYPE_RTV }
				);

				hr = core->back_buffer_group.create_back_buffer_group(
					device,
					core->swapchain_.get(),
					rtv_heap__allocator,
					core->back_buffer_index.get()
				);
				if (FAILED(hr)) {
					debug->debug_error_log(
						"create_back_buffer_group FAILED",
						debug->to_HRESULT(hr)
					);
					return false;
				}
			}
			{

				//	デプスバッファ作成
				auto dsv_heap_allocator = container->heap_container.get_heap_allocator(
					Container::DescriptorHeapKey{ D3D12_DESCRIPTOR_HEAP_TYPE_DSV }
				);

				ClassObject::desc::DepthBufferDesc depth_desc{};

				depth_desc.width = w;
				depth_desc.height = h;

				hr = core->depth_buffer_group.create_depth_buffer_group(
					device,
					dsv_heap_allocator,
					core->back_buffer_index.get(),
					depth_desc
				);
				if (FAILED(hr)) {
					debug->debug_error_log(
						"create_depth_buffer_group FAILED",
						debug->to_HRESULT(hr)
					);
					return false;
				}
			}

			return true;
		}

	};

	RendererSystem::RendererSystem()
	{
		ISystem::name_ = "RendererSystem";
	}
	RendererSystem::~RendererSystem() = default;

	bool RendererSystem::init_system(SystemManager& manager)
	{
		auto* entity = manager.get_system<EntityManager>();
		auto* window = manager.get_system<WindowsSystem>();
		auto* debug = manager.get_system<DebugSystem>();

		if (!entity ||!window || !debug)
		{
			return false;
		}
		if (
			!entity->is_initialize() ||
			!window->is_initialize() ||
			!debug->is_initialize()
			)
		{
			return false;
		}

		entity_ = entity;
		main_window = window;
		debug_ = debug;

		container_context = std::make_unique<ContainerContext>();
		core_context = std::make_unique<CoreContext>();

		if (!InitializeRendererCore::init_core(
			debug_,
			window,
			core_context.get(),
			container_context.get(),
			2,
			3,
			{
				{ 0, 1, 0, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, D3D12_DESCRIPTOR_HEAP_FLAG_NONE },
				{ 0, 1, 0, D3D12_DESCRIPTOR_HEAP_TYPE_DSV, D3D12_DESCRIPTOR_HEAP_FLAG_NONE },
				{ 0, 0, 10, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE }
			}
		))
		{
			container_context = nullptr;
			core_context = nullptr;
			return false;
		}

		//	ここでpipeline初期化


		is_init = true;
		return true;
	}

	void RendererSystem::update_system()
	{

		//	このUpdateで利用するインデックスに変更する
		core_context->back_buffer_index->update_index();
		core_context->frame_resource_index->update_index();

		auto current_resource_index = core_context->frame_resource_index->get_current_index();

		//	利用するインデックスから参照
		const auto wait = core_context->frame_resources[current_resource_index]
			->get_frame_value();

		//	使えるまで待機
		core_context->fence_.wait_to_completed_value(wait);

		//	フレームリソースリセット
		core_context->frame_resources[current_resource_index]->reset_frame_resource();

		//	コマンドアロケーター取得
		auto& allocator = core_context->frame_resources[current_resource_index]
			->get_allocator();

		//	コマンドリストリセット
		core_context->graphic_list.reset_list(allocator.get());

		{
			auto* list = core_context->graphic_list.get();
			auto* back_buffer = core_context->back_buffer_group.get_current_instance();
			auto* depth_buffer = core_context->depth_buffer_group.get_current_instance();

			back_buffer->barrier_transition(
				list,
				D3D12_RESOURCE_STATE_RENDER_TARGET
			);

			float color[4] = { 0,0,1,1 };
			list->ClearRenderTargetView(
				back_buffer->get_RTV_handle(),
				color,
				0,
				nullptr
			);
			list->ClearDepthStencilView(
				depth_buffer->get_DSV_handle(),
				D3D12_CLEAR_FLAG_DEPTH,
				1.0f,
				0,
				0,
				nullptr
			);

			//	ここでpipline実行

			back_buffer->barrier_transition(
				list,
				D3D12_RESOURCE_STATE_PRESENT
			);
		}

		//	コマンドリストをクローズ
		core_context->graphic_list->Close();

		//	コマンドキューにコマンドリストを送信
		ID3D12CommandList* ppCommandLists[] = { core_context->graphic_list.get() };
		core_context->graphic_queue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

		//	シグナルを送って配列に保存
		core_context->frame_resources[current_resource_index]
			->end_frame_signal(core_context->graphic_queue.get());

		auto hr = core_context->swapchain_.present();
		if (FAILED(hr))
		{
			debug_->debug_error_log(
				"create_depth_buffer_group FAILED",
				debug_->to_HRESULT(hr)
			);
		}

	}

	void RendererSystem::shutdown_system()
	{
		if (is_init)
		{
			//	GPUに投入済みのすべてのコマンドが完了するまで待機
			//	アプリケーション終了時は次フレームが存在しないため通常のフレーム同期ではなく終了用のFenceを使用する

			const auto signal = core_context->fence_.signal(core_context->graphic_queue.get());
			core_context->fence_.wait_to_completed_value(signal);


			entity_->remove_component_to_all<RendererComponent>();
			entity_->remove_component_to_all<TransformComponent>();

		}
	}



	TransformItem::TransformItem()
	{
		buffer_ = std::make_unique<TransformItem::transform_buffer>();
	}
	TransformItem::~TransformItem() = default;

	bool TransformItem::create_transform_item(
		DirectX::CoreContext* core,
		DirectX::ContainerContext* container
	)
	{
		const auto hr = buffer_->create_constant_buffer_group(
			core->device_.get(),
			container->heap_container.get_heap_allocator(
				Container::DescriptorHeapKey{ D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV }
			),
			core->frame_resource_index.get(),
			transform_.get_matrix()
		);

		previous_transform = transform_;
		index_size = core->frame_resource_index->get_size();

		return FAILED(hr) ? false : true;
	}

	TransformItem::transform_buffer* TransformItem::get_buffer() const noexcept
	{
		return buffer_.get();
	}

	void TransformItem::update_buffer()
	{
		if (transform_ != previous_transform)
		{
			previous_transform = transform_;
			dirty_size = index_size;
		}

		if (dirty_size > 0)
		{
			return;
		}

		buffer_->update_buffer(
			transform_.get_matrix()
		);

		--dirty_size;
	}

}