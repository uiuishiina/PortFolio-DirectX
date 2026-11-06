
/* ========== Includeファイル ========== */

#include"DirectXContext.h"

#include"Container/DescriptorHeapContainer.h"
#include"Container/PassContainer.h"
#include"Container/ShaderContainer.h"
#include"Container/RootSignatureContainer.h"
#include"Container/PiplineStateContainer.h"
#include"Container/DrawObjectConteiner.h"
#include"Container/CameraObjectContainer.h"

using namespace DirectX;

/// <summary>
/// コンストラクタ
/// </summary>
DirectXContext::DirectXContext() {
	
	/* -- Container -- */

	heap_container = std::make_unique<Container::DescriptorHeapContainer>();
	pass_container = std::make_unique<Container::PassContainer>();
	shader_container = std::make_unique<Container::ShaderContainer>();
	root_signature_container = std::make_unique<Container::RootSignatureContainer>();
	pipline_state_container = std::make_unique<Container::PiplineStateContainer>();
	draw_object_container = std::make_unique<Container::DrawObjectContainer>();
	camera_object_container = std::make_unique<Container::CameraObjectContainer>();

	/* -- Core -- */

	back_buffer_index = std::make_unique<ClassModule::BackBufferIndex>();
	frame_resource_index = std::make_unique<ClassModule::FrameResourceIndex>();

	player = std::make_unique<ClassModule::MeshObject>();
}

/// <summary>
/// デストラクタ
/// </summary>
DirectXContext::~DirectXContext() = default;