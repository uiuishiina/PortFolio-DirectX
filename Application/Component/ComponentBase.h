#pragma once

/* ========== Includeファイル ========== */

#include"Others/NonCopyableBase.h"
#include"ID/IDBase.h"

/// <summary>
/// アプリケーション名前空間
/// </summary>
namespace App {

	using ComponentID = std::uintptr_t;

	class ComponentBase : HandyItems::others::NonCopyableBase
	{
	public:

		virtual ~ComponentBase() = default;

		void set_active(bool flag) {
			is_active = flag;
		}

		[[nodiscard]] bool get_active() const noexcept {
			return is_active;
		}

		[[nodiscard]] virtual const ComponentID get_type_id() const noexcept = 0;

	private:

		bool is_active = true;

	};
}