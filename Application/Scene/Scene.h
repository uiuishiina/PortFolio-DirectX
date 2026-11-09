#pragma once

/* ========== Includeファイル ========== */

#include"../Entity/EntityManager.h"

/// <summary>
/// アプリケーション名前空間
/// </summary>
namespace App {

	class Scene : HandyItems::others::NonCopyableBase
	{
	public:



	private:

		EntityManager entitiy_manager{};

	};
}