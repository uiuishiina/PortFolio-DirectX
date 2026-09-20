
/* ========== Includeファイル ========== */

#include "DirectXContext.h"

//	DirectX
#include"ClassObject/DXGI.h"
#include"ClassObject/Device.h"
#include"ClassObject/CommandQueue.h"
#include"ClassObject/CommandList.h"
#include"ClassObject/Fence.h"
#include"ClassObject/SwapChain.h"
#include"ClassObject/DescriptorHeap.h"
#include"ClassObject/GPUResource/RenderTarget/BackBuffer.h"

#include"ClassModule/FrameResource.h"

using namespace DirectX;

/* ========== Publicメンバー関数 ========== */

/// <summary>
/// コンストラクタ
/// </summary>
DirectXContext::DirectXContext() {

	/* -- Core -- */

	dxgi_.register_unique(std::make_unique<ClassObject::DXGI>());
	device_.register_unique(std::make_unique<ClassObject::Device>());
	graphic_queue.register_unique(std::make_unique<ClassObject::CommandQueue>());
	graphic_list.register_unique(std::make_unique<ClassObject::CommandList>());
	fence_.register_unique(std::make_unique<ClassObject::Fence>());

	frame_resources.resize(frame_resource_size);

	for (auto& resource : frame_resources) {
		resource.register_unique(std::make_unique<ClassModule::FrameResource>(get_fence()));
	}

	swapchain_.register_unique(std::make_unique<ClassObject::SwapChain>());
	heap_.register_unique(std::make_unique<ClassObject::DescriptorHeap>());

	back_buffers.resize(back_buffer_size);

	for (auto& buffer : back_buffers) {
		buffer.register_unique(std::make_unique<ClassObject::BackBuffer>());
	}
}

/// <summary>
/// デストラクタ
/// </summary>
DirectXContext::~DirectXContext() = default;
