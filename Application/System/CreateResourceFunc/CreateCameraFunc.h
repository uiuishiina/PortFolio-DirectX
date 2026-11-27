#pragma once

#include"../RendererSystem.h"

#include"../../../DirectX/CoreContext.h"
#include"../../../DirectX/ContainerContext.h"
#include"../../../DirectX/ClassModule/DrawObject/CameraObject.h"

namespace App
{
	class CreateCameraFunc final
	{
	public:
		using Camera = DirectX::ClassModule::DescriptorGroup::CameraObject;

		static RendererSystem::CreateResourceFunc create_camera_func(
			const std::string& name,
			const D3D12_VIEWPORT& view_,
			const D3D12_RECT& rect_
		)
		{
			return [name, view_, rect_](
				DirectX::CoreContext* core,
				DirectX::ContainerContext* container,
				DebugSystem* debug
				)
				{
					auto camera = std::make_unique<Camera>();
					auto hr = camera->create_camera_object(
						core->device_,
						container->heap_container.get_heap_allocator(
							DirectX::Container::DescriptorHeapKey{ D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV }
						),
						core->frame_resource_index.get(),
						view_,
						rect_
					);
					if (FAILED(hr)) {
						if (debug)
						{
							debug->debug_error_log(
								"Create CameraObject FAILED : =", name,
								debug->to_HRESULT(hr)
							);
						}
						return;
					}

					auto* pCamera = camera.get();

					if (!container->camera_object_container.add_camera_object(
						DirectX::Container::CameraObjectKey{ name.c_str() },
						std::move(camera)
					)) {
						if (debug)
						{
							debug->debug_error_log(
								"Add CameraObject FAILED", name,
								debug->to_HRESULT(hr)
							);
						}
						return;
					}

					if (debug)
					{
						debug->debug_log(
							"Create CameraObject SUCCEEDED : Name = ", name
						);
					}
				};
		}
	};
}