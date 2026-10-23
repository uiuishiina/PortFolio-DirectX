#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../../ClassObject/GPUResource/DepthBuffer.h"
#include"../DescriptorResource.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// オブジェクト機能統合名前空間
	/// </summary>
	namespace ClassModule {


		namespace DescriptorGroup {


			class DepthBufferGroup final : protected DescriptorResource
			{
			public:
				/* ========== Publicメンバー関数 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				DepthBufferGroup() :
					DescriptorResource(State::HeapState::Buffering) {}

				/// <summary>
				/// デストラクタ
				/// </summary>
				~DepthBufferGroup() = default;

				/// <summary>
				/// デプスバッファグループ作成関数
				/// </summary>
				/// <param name="device_">Device参照</param>
				/// <param name="allocator">[DSV] ディスクリプターヒープアロケータ参照</param>
				/// <param name="desc">デプスバッファ設定構造体</param>
				/// <returns>作成の成否</returns>
				[[nodiscard]] HRESULT create_depth_buffer_group(
					ID3D12Device* device_,
					DescriptorHeapAllocator* allocator,
					ClassObject::desc::DepthBufferDesc desc
				) {

					//	DescriptorResource初期化s
					{
						const auto hr = initialize_resource(allocator);
						if (FAILED(hr)) {
							return hr;
						}
					}

					//	DepthBuffer初期化
					{
						const auto size = get_handles_vec_size();
						depth_vec.resize(size);

						for (std::size_t i = 0; i < size; i++) {

							depth_vec[i] = std::make_unique<ClassObject::DepthBuffer>();

							auto handles = get_handles(i);
							if (!handles.has_value()) {
								return E_OUTOFMEMORY;
							}

							const auto hr = depth_vec[i]->creata_depth_buffer(
								device_,
								handles->cpu_handle,
								desc
							);
							if (FAILED(hr)) {
								return hr;
							}
						}
					}
					return S_OK;
				}

				/// <summary>
				/// デプスバッファクラス参照取得関数
				/// </summary>
				/// <param name="index">取得するインデックス</param>
				/// <returns>取得したデプスバッファクラス参照</returns>
				[[nodiscard]] ClassObject::DepthBuffer* get_depth_buffer(
					std::size_t index
				) const noexcept {
					if (index >= depth_vec.size()) {
						return nullptr;
					}

					return depth_vec[index].get();
				}

				[[nodiscard]] ClassObject::DepthBuffer* operator [] (UINT index) const noexcept {
					return get_depth_buffer(static_cast<std::size_t>(index));
				}

			private:
				/* ========== Privateメンバー変数 ========== */

				/// <summary>
				/// デプスバッファインスタンス配列
				/// </summary>
				std::vector<std::unique_ptr<ClassObject::DepthBuffer>> depth_vec{};

			};
		}
	}
}