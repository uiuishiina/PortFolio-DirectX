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
}

namespace App
{
	/* ========== 前方宣言 ========== */

	class DebugSystem;

	class IRendererPipeline
	{
	public:

		virtual ~IRendererPipeline() = default;

		virtual bool init_pipeline(
			DirectX::CoreContext*,
			DirectX::ContainerContext*,
			DebugSystem*
		) = 0;

		virtual void execute_pipeline(
			const std::span<Entity*> entitys
		) = 0;

	};
}