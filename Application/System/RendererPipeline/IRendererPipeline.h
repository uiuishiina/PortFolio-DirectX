#pragma once

#include"../System.h"

#include<span>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/* ========== 前方宣言 ========== */

	struct CoreContext;
	struct ContainerContext;

	namespace ClassModule
	{
		namespace DescriptorGroup
		{
			class CameraObject;
		}
	}
}

namespace App
{
	/* ========== 前方宣言 ========== */

	class DebugSystem;

	class IRendererPipeline
	{
	public:
		using MainCamera = DirectX::ClassModule::DescriptorGroup::CameraObject;

		virtual ~IRendererPipeline() = default;

		virtual bool init_pipeline(
			DirectX::CoreContext*,
			DirectX::ContainerContext*,
			DebugSystem*
		) = 0;

		virtual void execute_pipeline(
			MainCamera*,
			const std::span<Entity*>
		) = 0;

	};
}