#pragma once


/* ========== Includeファイル ========== */

#include"../Entity/EntityManager.h"

/// <summary>
/// アプリケーション名前空間
/// </summary>
namespace App {

	class SystemBase : HandyItems::others::NonCopyableBase
	{
	public:

		virtual ~SystemBase() {
			on_destory();
		}

		virtual void initialize() = 0;

		virtual void update() = 0;

		virtual void fixed_update() = 0;

		virtual void on_destory() = 0;

		/*
			ResourceManagerは作成または紐づけ


		*/
	};
}