#pragma once
#include"../RendererSystem.h"

#include"../../../DirectX/ContainerContext.h"
namespace App
{
	class CompileShaderFunc final
	{
		using Sharder = DirectX::ClassObject::ShaderCompiler;
		using ShaderDesc = DirectX::ClassObject::desc::ShaderDesc;
	public:

		RendererSystem::CreateResourceFunc compile_shader(
			const std::string& path,
			const std::string& name,
			const ShaderDesc& desc
		)
		{
			return [path, name, desc](
				DirectX::CoreContext* core,
				DirectX::ContainerContext* container,
				DebugSystem* debug
				) 
				{

					auto shader = std::make_unique<Sharder>();
					const auto hr = shader->compile_shader(desc);
					if (FAILED(hr))
					{
						if (debug)
						{
							debug->debug_error_log("Compile Shader Failed : Name = ", name);
						}
						return;
					}

					if (!container->shader_container.add_shader(
						DirectX::Container::ShaderKey{ name.c_str() },
						std::move(shader)
					)) {
						if (debug)
						{
							debug->debug_error_log("Add Shader Failed : Name = ", name);
						}
						return;
					}
			};
		}

	private:
		CompileShaderFunc() = default;
	};


	void func()
	{

	}
}