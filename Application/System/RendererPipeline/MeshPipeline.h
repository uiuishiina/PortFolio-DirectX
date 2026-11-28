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

	class MeshRedererPipelineBase : public IRendererPipeline
	{
		using RootSignature = DirectX::ClassObject::RootSignature;
		using PipelineState = DirectX::ClassObject::PipelineState;
		using CommandList = DirectX::ClassObject::CommandList;

		using UsingShader = DirectX::Resource::Shaders::UsingShader;
		using UsingRootSignature = DirectX::Resource::RootSignatures::UsingRootSignature;
		using UsingPiplineState = DirectX::Resource::PiplineStates::UsingPiplineState;

	public:

		using IRendererPipeline::init_pipeline;
		using IRendererPipeline::execute_pipeline;

	protected:

		RootSignature* root_{};
		PipelineState* pipeline_{};

		CommandList* list_{};

		struct pipelineRef
		{
			DirectX::CoreContext* core{};
			DirectX::ContainerContext* container{};
			DebugSystem* debug{};
		};


		bool create_shader(
			const pipelineRef& ref,
			const UsingShader& desc
		)
		{
			if (ref.container->shader_container.get_shader(
				DirectX::Container::ShaderKey{ desc.first.c_str() }
			))
			{
				return true;
			}

			auto shader = std::make_unique<DirectX::ClassObject::ShaderCompiler>();
			const auto hr = shader->compile_shader(desc.second);
			if (FAILED(hr))
			{
				if (ref.debug)
				{
					ref.debug->debug_error_log("Shader Compile Failed : Name = ", desc.first);
					ref.debug->debug_error_log(ref.debug->to_HRESULT(hr));
				}
				return false;
			}
			if (!ref.container->shader_container.add_shader(
				DirectX::Container::ShaderKey{ desc.first.c_str() },
				std::move(shader)
			))
			{
				if (ref.debug)
				{
					ref.debug->debug_error_log("Add Create Failed : Name = ", desc.first);
				}
				return false;
			}

			return true;
		}

		bool create_root(
			const pipelineRef& ref,
			const UsingRootSignature& desc
		)
		{
			if(ref.container->root_signature_container.get_root_signature(
				DirectX::Container::RootSignatureKey{ desc.first.c_str() }
			))
			{
				return true;
			}

			auto ins = std::make_unique<RootSignature>();
			const auto hr = ins->create_root_signature(
				ref.core->device_,
				desc.second
			);
			if (FAILED(hr))
			{
				if (ref.debug)
				{
					ref.debug->debug_error_log("RootSignature Create Failed : Name = ", desc.first.c_str());
					ref.debug->debug_error_log(ref.debug->to_HRESULT(hr));
				}
				return false;
			}

			if (!ref.container->root_signature_container.add_root_signature(
				DirectX::Container::RootSignatureKey{ desc.first.c_str() },
				std::move(ins)
			))
			{
				if (ref.debug)
				{
					ref.debug->debug_error_log("Add RootSignature Failed : Name = ", desc.first.c_str());
				}
				return false;
			}

			return true;
		}

		bool create_pipline(
			const pipelineRef& pipeline_ref,
			const UsingPiplineState& pipline_desc
		)
		{
			const auto& [name, ref, desc] = pipline_desc;

			if (pipeline_ref.container->pipline_state_container.get_pipline_state(
				DirectX::Container::PiplineStateKey{ name.c_str() }
			))
			{
				return true;
			}

			const auto copy_desc = DirectX::ClassObject::desc::Factory::PipelineStateDescFactory::create_desc(
				&pipeline_ref.container->root_signature_container,
				&pipeline_ref.container->shader_container,
				desc,
				ref
			);

			auto pipeline = std::make_unique<PipelineState>();
			const auto hr = pipeline->create_pipline(
				pipeline_ref.core->device_,
				copy_desc
			);
			if (FAILED(hr))
			{
				if (pipeline_ref.debug)
				{
					pipeline_ref.debug->debug_error_log("PipelineState Create Failed : Name = ", name);
					pipeline_ref.debug->debug_error_log(pipeline_ref.debug->to_HRESULT(hr));
				}
				return false;
			}

			if (!pipeline_ref.container->pipline_state_container.add_pipline_state(
				DirectX::Container::PiplineStateKey{ name.c_str() },
				std::move(pipeline)
			))
			{
				if (pipeline_ref.debug)
				{
					pipeline_ref.debug->debug_error_log("Add PipelineState Failed : Name = ", name);
				}
				return false;
			}
			return true;
		}
	};

	class NormalMeshPipeline final : public MeshRedererPipelineBase
	{
	public:

		bool init_pipeline(
			DirectX::CoreContext* core,
			DirectX::ContainerContext* container,
			DebugSystem* debug
		) override
		{
			const auto& vertex = DirectX::Resource::Shaders::NormalVertex;
			const auto& pixel = DirectX::Resource::Shaders::NormalPixel;

			MeshRedererPipelineBase::pipelineRef ref{ core ,container ,debug };

			if (!create_shader(ref,vertex) || !create_shader(ref,pixel))
			{
				return false;
			}

			//	既存定義を活用
			const auto& root_desc = DirectX::Resource::RootSignatures::Normal;

			if (!create_root(ref, root_desc))
			{
				return false;
			}

			root_ = container->root_signature_container.get_root_signature(
				DirectX::Container::RootSignatureKey{ root_desc.first.c_str() }
			);

			//	既存定義を活用
			const auto& pipline_desc = DirectX::Resource::PiplineStates::Normal;

			if (!create_pipline(ref, pipline_desc))
			{
				return false;
			}

			const auto& [name, refName, desc] = DirectX::Resource::PiplineStates::Normal;

			pipeline_ = container->pipline_state_container.get_pipline_state(
				DirectX::Container::PiplineStateKey{ name.c_str() }
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
			MainCamera* camera,
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

			camera->set_view_port(list_->get());
			
			for (auto& component : vec)
			{
				component->get_mesh()->draw(list_->get());
			}
		}

	};


	class TransformMeshPipeline final : public MeshRedererPipelineBase
	{
		
	public:

		bool init_pipeline(
			DirectX::CoreContext* core,
			DirectX::ContainerContext* container,
			DebugSystem* debug
		) override
		{

			const auto& vertex = DirectX::Resource::Shaders::ConstantVertex;
			const auto& pixel = DirectX::Resource::Shaders::ColorPixel;

			MeshRedererPipelineBase::pipelineRef ref{ core ,container ,debug };

			if (!create_shader(ref, vertex) || !create_shader(ref, pixel))
			{
				return false;
			}

			//	既存定義を活用
			const auto& root_desc = DirectX::Resource::RootSignatures::Constant;

			if (!create_root(ref, root_desc))
			{
				return false;
			}

			root_ = container->root_signature_container.get_root_signature(
				DirectX::Container::RootSignatureKey{ root_desc.first.c_str() }
			);

			//	既存定義を活用
			const auto& pipline_desc = DirectX::Resource::PiplineStates::Constant;

			if (!create_pipline(ref, pipline_desc))
			{
				return false;
			}

			const auto& [name, refName, desc] = pipline_desc;

			pipeline_ = container->pipline_state_container.get_pipline_state(
				DirectX::Container::PiplineStateKey{ name.c_str() }
			);

			list_ = &core->graphic_list;
			if (!list_) {
				if (debug)
				{
					debug->debug_error_log("Get CommandList Failed : class Name = TransformMeshPipeline");
				}
				return false;
			}
			
			if (debug)
			{
				debug->debug_log("Create Pipeline SUCCEEDED : Name = TransformMeshPipeline");
			}

			return true;
		}

		void execute_pipeline(
			MainCamera* camera,
			const std::span<Entity*> entitys
		) override
		{
			std::vector<
				std::tuple<
				MeshComponent*,
				TransformComponent*
				>
			> vec{};

			for (auto& entity : entitys)
			{
				auto* mesh = entity->get_component<MeshComponent>();
				auto* transform = entity->get_component<TransformComponent>();
				if (mesh && transform)
				{
					vec.push_back(
						std::make_tuple(
							mesh, 
							transform
						)
					);
				}
			}

			if (vec.empty())
			{
				return;
			}

			list_->get()->SetGraphicsRootSignature(root_->get());

			list_->get()->SetPipelineState(pipeline_->get());

			camera->set_view_port(list_->get());
			camera->set_buffer(
				0,
				list_->get()
			);
			
			auto* list = list_->get();

			for (auto& component : vec)
			{
				auto& [mesh, transform] = component;

				transform->get_transform_item()->get_buffer()->get_current_instance()
					->set_constant_buffer(
					1,
					list
				);
				mesh->get_mesh()->draw(list);
			}
		}
	};

}