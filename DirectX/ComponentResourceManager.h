#pragma once

/* ========== Includeファイル ========== */

#include"Others/NonCopyableBase.h"

#include"Container/UnorderedMapBase.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {


	namespace Container {

		class PassContainer;
		class DrawObjectContainer;

	}


	class ComponentReosurceManager final : HandyItems::others::NonCopyableBase
	{
	public:

		explicit ComponentReosurceManager(
			Container::PassContainer* pass,
			Container::DrawObjectContainer* draw
		) :
			pass_{ pass },
			draw_{ draw } {};



	private:

		Container::PassContainer* pass_{};
		Container::DrawObjectContainer* draw_{};

		
	};
}