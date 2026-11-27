#pragma once

#include"../Component.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/* ========== 前方宣言 ========== */

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
	class CameraComponent final : public IComponent
	{
	public:
		using Camera = DirectX::ClassModule::DescriptorGroup::CameraObject;

		explicit CameraComponent(
			const ComponentUniqueID& id,
			Camera* camera,
			RemoveFunc func = {}
		) :
			camera_{ camera },
			IComponent{ id,func }
		{}

		Camera* get_camera() const noexcept
		{
			return camera_;
		}

	private:
		Camera* camera_{};

	};
}