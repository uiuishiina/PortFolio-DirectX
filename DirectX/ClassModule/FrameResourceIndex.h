#pragma once

/* ========== Includeファイル ========== */

#include"CurrentIndexBase.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// オブジェクト機能統合名前空間
	/// </summary>
	namespace ClassModule {

		class FrameResourceIndex final : public CurrentIndexBase
		{
		public:

			[[nodiscard]] bool initialize_index(std::size_t size) {

				current_index = std::make_unique<HandyItems::others::CircularIndex>(size);

				return true;
			}

			void update_index() override {
				++*current_index.get();
			}

			[[nodiscard]] std::size_t get_current_index() const noexcept override {
				return *current_index.get();
			}

			[[nodiscard]] std::size_t get_size() const noexcept override {
				return current_index->size();
			}

		private:

			std::unique_ptr<HandyItems::others::CircularIndex> current_index{};

		};
	}
}