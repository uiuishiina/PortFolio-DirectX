#pragma once

/* ========== Includeファイル ========== */

#include"CurrentIndexBase.h"

#include"../ClassObject/SwapChain.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// オブジェクト機能統合名前空間
	/// </summary>
	namespace ClassModule {

		class BackBufferIndex final : public CurrentIndexBase
		{
		public:

			[[nodiscard]] bool initialize_index(IDXGISwapChain4& swap) {
				swap_chain = &swap;

				DXGI_SWAP_CHAIN_DESC desc{};

				const auto hr = swap_chain->GetDesc(&desc);
				if (FAILED(hr)) {
					return false;
				}

				max_size = static_cast<std::size_t>(desc.BufferCount);

				return true;
			}

			void update_index() override {
				current_index = swap_chain->GetCurrentBackBufferIndex();
			}

			[[nodiscard]] std::size_t get_current_index() const noexcept override {
				return current_index;
			}

			[[nodiscard]] std::size_t get_size() const noexcept override {
				return max_size;
			}

		private:

			std::size_t current_index{};

			std::size_t max_size{};

			IDXGISwapChain4* swap_chain{};
		};
	}
}