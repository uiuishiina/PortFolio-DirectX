#pragma once

#include"../Component.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/* ========== 前方宣言 ========== */

	namespace ClassModule
	{
		class DrawObjectBase;
	}
}

namespace App
{

	class MeshComponent final : public IComponent
	{
	public:
		using Mesh = DirectX::ClassModule::DrawObjectBase;

		explicit MeshComponent(
			const ComponentUniqueID& id,
			Mesh* mesh,
			RemoveFunc func = {}
		) :
			mesh_{ mesh },
			IComponent{ id,func }
		{}

		const Mesh* get_mesh() const noexcept
		{
			return mesh_;
		}

	private:

		Mesh* mesh_{};

	};
}
