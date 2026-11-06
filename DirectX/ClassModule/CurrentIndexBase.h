#pragma once

/* ========== Includeファイル ========== */

#include"Others/NonCopyableBase.h"
#include"Others/CircularIndex.h"

#include<memory>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// オブジェクト機能統合名前空間
	/// </summary>
	namespace ClassModule {

		class CurrentIndexBase : HandyItems::others::NonCopyableBase
		{
		public:

			virtual ~CurrentIndexBase() = default;

			virtual void update_index() = 0;

			[[nodiscard]] virtual std::size_t get_current_index() const noexcept = 0;
	
			[[nodiscard]] virtual std::size_t get_size() const noexcept = 0;
		};
	}
}