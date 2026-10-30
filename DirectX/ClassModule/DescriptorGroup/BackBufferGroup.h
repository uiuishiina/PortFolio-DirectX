#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../../ClassObject/GPUResource/RenderTarget/BackBuffer.h"
#include"../DescriptorResource.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// オブジェクト機能統合名前空間
	/// </summary>
	namespace ClassModule {

		/// <summary>
		/// ディスクリプターヒープグループ名前空間
		/// </summary>
		namespace DescriptorGroup {


			class BackBufferGroup final : protected DescriptorResource
			{
			public:
				/* ========== Publicメンバー関数 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				BackBufferGroup():
					DescriptorResource(State::HeapState::Buffering) {}

				/// <summary>
				/// デストラクタ
				/// </summary>
				~BackBufferGroup() = default;

				/* ===== 初期化関数 ===== */

				[[nodiscard]] HRESULT create_back_buffer_group(
					ID3D12Device* device_,
					IDXGISwapChain4* swapchain_,
					DescriptorHeapAllocator* allocator
				) {

					//	DescriptorResource初期化
					{
						const auto hr = initialize_resource(allocator);
						if (FAILED(hr)) {
							return hr;
						}
					}

					//	BackBuffer初期化
					{
						const auto size = get_handles_vec_size();
						back_vec.resize(size);

						for (std::size_t i = 0; i < size; i++) {

							back_vec[i] = std::make_unique<ClassObject::BackBuffer>();

							auto handles = get_handles(i);
							if (!handles.has_value()) {
								return E_OUTOFMEMORY;
							}

							const auto hr = back_vec[i]->create_back_buffer(
								device_,
								swapchain_,
								handles->cpu_handle,
								static_cast<UINT>(i)
							);
							if (FAILED(hr)) {
								return hr;
							}
						}
					}
					return S_OK;
				}

				/* ===== 取得関数 ===== */

				[[nodiscard]] ClassObject::BackBuffer* get_back_buffer(
					std::size_t index
				) const noexcept {

					if (index >= back_vec.size()) {
						return nullptr;
					}

					return back_vec[index].get();
				}

				[[nodiscard]] ClassObject::BackBuffer* operator [] (UINT index) const noexcept {
					return get_back_buffer(static_cast<std::size_t>(index));
				}

			private:
				/* ========== Privateメンバー変数 ========== */

				std::vector<std::unique_ptr<ClassObject::BackBuffer>> back_vec{};

			};
		}
	}
}