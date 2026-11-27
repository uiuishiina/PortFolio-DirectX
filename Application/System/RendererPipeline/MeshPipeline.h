#pragma once
#include"IRendererPipeline.h"
#include"../../Component/RendererComponent/MeshComponent.h"

#include"../../../DirectX/CoreContext.h"
#include"../../../DirectX/ContainerContext.h"
#include"../../../DirectX/Resource/ShaderList.h"
#include"../../../DirectX/Resource/PiplineStateList.h"
#include"../DebugSystem.h"

namespace App
{

	class NormalMeshPipeline final : public IRendererPipeline
	{
		using RootSignature = DirectX::ClassObject::RootSignature;
		using PipelineState = DirectX::ClassObject::PipelineState;
		using CommandList = DirectX::ClassObject::CommandList;
	public:

		bool init_pipeline(
			DirectX::CoreContext* core,
			DirectX::ContainerContext* container,
			DebugSystem* debug
		) override
		{
			const auto& vertex = DirectX::Resource::Shaders::NormalVertex;
			const auto& pixel = DirectX::Resource::Shaders::NormalPixel;

			auto func = [&](const DirectX::Resource::Shaders::UsingShader& desc) {
				if (!container->shader_container.get_shader(
					DirectX::Container::ShaderKey{ desc.first.c_str() }
				))
				{
					auto shader = std::make_unique<DirectX::ClassObject::ShaderCompiler>();
					const auto hr = shader->compile_shader(desc.second);
					if (FAILED(hr))
					{
						if (debug)
						{
							debug->debug_error_log("Shader Compile Failed : Name = ", desc.first);
							debug->debug_error_log(debug->to_HRESULT(hr));
						}
						return false;
					}
					if (!container->shader_container.add_shader(
						DirectX::Container::ShaderKey{ desc.first.c_str() },
						std::move(shader)
					))
					{
						if (debug)
						{
							debug->debug_error_log("Add Create Failed : Name = ", desc.first);
						}
						return false;
					}
				}
				return true;
			};

			if (!func(vertex) || !func(pixel))
			{
				return false;
			}

			//	既存定義を活用
			const auto& root_desc = DirectX::Resource::RootSignatures::Normal;

			root_ = container->root_signature_container.get_root_signature(
				DirectX::Container::RootSignatureKey{ root_desc.first.c_str() }
			);
			if (!root_)
			{
				
				auto ins = std::make_unique<RootSignature>();
				const auto hr = ins->create_root_signature(
					core->device_,
					root_desc.second
				);
				if (FAILED(hr))
				{
					if (debug)
					{
						debug->debug_error_log("RootSignature Create Failed : Name = ", root_desc.first.c_str());
						debug->debug_error_log(debug->to_HRESULT(hr));
					}
					return false;
				}

				if (!container->root_signature_container.add_root_signature(
					DirectX::Container::RootSignatureKey{ root_desc.first.c_str() },
					std::move(ins)
				))
				{
					if (debug)
					{
						debug->debug_error_log("Add RootSignature Failed : Name = ", root_desc.first.c_str());
					}
					return false;
				}
				root_ = container->root_signature_container.get_root_signature(
					DirectX::Container::RootSignatureKey{ root_desc.first.c_str() }
				);
			}

			pipeline_ = container->pipline_state_container.get_pipline_state(
				DirectX::Container::PiplineStateKey{ "NormalPipeline" }
			);
			if (pipeline_)
			{
				return true;
			}

			//	既存定義を活用
			const auto& [name, ref, desc] = DirectX::Resource::PiplineStates::Normal;

			const auto copy_desc = DirectX::ClassObject::desc::Factory::PipelineStateDescFactory::create_desc(
				&container->root_signature_container,
				&container->shader_container,
				desc,
				ref
			);

			auto pipeline = std::make_unique<PipelineState>();
			const auto hr = pipeline->create_pipline(
				core->device_,
				copy_desc
			);
			if (FAILED(hr))
			{
				if (debug)
				{
					debug->debug_error_log("PipelineState Create Failed : Name = ", "NormalPipeline");
					debug->debug_error_log(debug->to_HRESULT(hr));
				}
				return false;
			}

			if (!container->pipline_state_container.add_pipline_state(
				DirectX::Container::PiplineStateKey{ "NormalPipeline" },
				std::move(pipeline)
			))
			{
				if (debug)
				{
					debug->debug_error_log("Add PipelineState Failed : Name = ", "NormalPipeline");
				}
				return false;
			}
			pipeline_ = container->pipline_state_container.get_pipline_state(
				DirectX::Container::PiplineStateKey{ "NormalPipeline" }
			);
			
			list_ = &core->graphic_list;
			if (!list_) {
				if (debug)
				{
					debug->debug_error_log("Get CommandList Failed : class Name = NormalMeshPipeline");
				}
				return false;
			}
			
			if (debug)
			{
				debug->debug_log("Create Pipeline SUCCEEDED : Name = NormalMeshPipeline");
			}

			return true;
		}

		void execute_pipeline(
			const std::span<Entity*> entitys
		) override
		{
			std::vector<MeshComponent*> vec{};

			for (auto& entity : entitys)
			{
				auto* component = entity->get_component<MeshComponent>();
				if (component)
				{
					vec.push_back(component);
				}
			}

			if (vec.empty())
			{
				return;
			}

			list_->get()->SetGraphicsRootSignature(root_->get());

			list_->get()->SetPipelineState(pipeline_->get());

			for (auto& component : vec)
			{
				component->get_mesh()->draw(list_->get());
			}
		}

	private:

		RootSignature* root_{};
		PipelineState* pipeline_{};

		CommandList* list_{};

	};

}