
/* ========== Includeファイル ========== */

#include"DirectXContext.h"

#include"Container/PassContainer.h"
#include"Container/ShaderContainer.h"
#include"Container/RootSignatureContainer.h"
#include"Container/PiplineStateContainer.h"

using namespace DirectX;

DirectXContext::DirectXContext(std::uint32_t back_buffer_size, std::uint32_t frame_resource_size) {

		/* -- Core -- */

		dxgi_ = std::make_unique<ClassObject::DXGI>();
		device_ = std::make_unique<ClassObject::Device>();
		graphic_queue = std::make_unique<ClassObject::CommandQueue>();
		graphic_list = std::make_unique<ClassObject::CommandList>();
		fence_ = std::make_unique<ClassObject::Fence>();

		frame_resources.resize(frame_resource_size);

		for (auto& resource : frame_resources) {
			resource = std::make_unique<ClassModule::FrameResource>(fence_.get());
		}

		swapchain_ = std::make_unique<ClassObject::SwapChain>();
		heap_ = std::make_unique<ClassObject::DescriptorHeap>();

		back_buffers.resize(back_buffer_size);

		for (auto& back_buffer : back_buffers) {
			back_buffer = std::make_unique<ClassObject::BackBuffer>();
		}


		/* -- Container -- */

		pass_container = std::make_unique<Container::PassContainer>();
		shader_container = std::make_unique<Container::ShaderContainer>();
		root_signature_container = std::make_unique<Container::RootSignatureContainer>();
		pipline_state_container = std::make_unique<Container::PiplineStateContainer>();
}

DirectXContext::~DirectXContext() = default;