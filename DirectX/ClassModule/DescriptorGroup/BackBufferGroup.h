#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../../ClassObject/GPUResource/RenderTarget/BackBuffer.h"
#include"DescriptorGroupBase.h"

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


			class BackBufferGroup final : public DesctirptorGroupBase<ClassObject::BackBuffer>
			{
			public:
				/* ========== Publicメンバー関数 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				BackBufferGroup():
					DesctirptorGroupBase(State::HeapState::Buffering) {}

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
						const auto hr = initialize_resource_group(allocator);
						if (FAILED(hr)) {
							return hr;
						}
					}

					//	BackBuffer初期化
					{
						for (std::size_t i = 0; i < group_instances.size(); i++) {

							group_instances[i] = std::make_unique<ClassObject::BackBuffer>();

							auto handles = get_handles(i);
							if (!handles.has_value()) {
								return E_OUTOFMEMORY;
							}

							const auto hr = group_instances[i]->create_back_buffer(
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

			};
		}
	}
}