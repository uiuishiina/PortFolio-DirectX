#pragma once
#include"../RendererSystem.h"

#include"../../../DirectX/CoreContext.h"
#include"../../../DirectX/ContainerContext.h"
#include"../../../DirectX/ClassModule/DrawObject/Mesh.h"

namespace App
{

	class CreateMeshFunc final
	{
	public:

		using Mesh = DirectX::ClassModule::Mesh;

		template<typename T>
		using MeshDesc = DirectX::ClassModule::desc::MeshDesc<T>;
		

		template<typename T>
		static RendererSystem::CreateResourceFunc create_mesh_func(
			const std::string& name,
			const MeshDesc<T>& desc
		)
		{
			return [name, desc](
				DirectX::CoreContext* core,
				DirectX::ContainerContext* container,
				DebugSystem* debug
				)
			{
					if (container->draw_object_container.get_draw_object(
						DirectX::Container::DrawObjectKey{ name.c_str() }
						))
					{
						if (debug)
						{
							debug->debug_error_log("Mesh Alrady Created: Name = ", name);
						}
						return;
					}

					auto& upload = core->frame_resources[
						core->frame_resource_index->get_current_index()
					]->get_upload_resources();

					upload.add_upload(2);
					auto ref_vec = upload.allocate_references(2);

					auto mesh = std::make_unique<Mesh>();

					const auto hr = mesh->create_mesh(
						core->device_.get(),
						core->graphic_list.get(),
						ref_vec,
						desc
					);
					if (FAILED(hr)) 
					{
						if (debug)
						{
							debug->debug_error_log("Create Mesh Failed : Name = ", name);
						}
						return;
					}

					//	登録
					if (!container->draw_object_container.add_draw_object(
						DirectX::Container::DrawObjectKey{ name.c_str() },
						std::move(mesh)
					)) {
						if (debug)
						{
							debug->debug_error_log("Add Mesh Failed : Name = ", name);
						}
						return;
					}
					if (debug)
					{
						debug->debug_log("Create Mesh SUCCEEDED : Name = ", name);
					}
			};
		}


	private:
		
		CreateMeshFunc() = default;
	};

}