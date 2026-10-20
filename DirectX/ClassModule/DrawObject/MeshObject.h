#pragma once

/* ========== Includeファイル ========== */

#include"Mesh.h"
#include"../TransformBuffer.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// オブジェクト機能統合名前空間
	/// </summary>
	namespace ClassModule {

		class MeshObject : public DrawObjectBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			MeshObject() {

				mesh_ = std::make_unique<Mesh>();
				transform_ = std::make_unique<TransformBuffer>();
			}

			/// <summary>
			/// デストラクタ
			/// </summary>
			~MeshObject() = default;


			/* ===== 初期化関数 ===== */
			template<typename T>
			[[nodiscard]] HRESULT create_mesh_object(
				ID3D12Device* device_,
				ID3D12GraphicsCommandList* list_,
				Helper::DescriptorHeapHandles handles,
				UINT index,
				std::span<std::reference_wrapper<Microsoft::WRL::ComPtr<ID3D12Resource>>>& upload_resources,
				const desc::MeshDesc<T>& desc
			) {


				auto hr = mesh_->create_mesh(
					device_, 
					list_, 
					upload_resources, 
					desc
				);
				if (FAILED(hr)) {
					return hr;
				}

				hr = transform_->create_transform_buffer(
					device_,
					handles
				);
				if (FAILED(hr)) {
					return hr;
				}
				register_index = index;

				return hr;
			}

			/* ===== 実行関数 ===== */

			/// <summary>
			/// メッシュ描画関数
			/// </summary>
			/// <param name="list_">コマンドリスト参照</param>
			void draw(
				ID3D12GraphicsCommandList* list_
			) const noexcept override {

				transform_->set_buffer(
					register_index, 
					list_
				);

				mesh_->draw(list_);
			}

			/// <summary>
			/// トランスフォームバッファ参照取得関数
			/// </summary>
			/// <returns>取得したトランスフォームバッファ参照</returns>
			[[nodiscard]] TransformBuffer* get_transform_buffer() const noexcept {
				return transform_.get();
			}

		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			/// メッシュ
			/// </summary>
			std::unique_ptr<Mesh> mesh_{};

			/// <summary>
			/// トランスフォームバッファ
			/// </summary>
			std::unique_ptr<TransformBuffer> transform_{};

			/// <summary>
			/// コンスタントバッファレジスターインデックス
			/// </summary>
			UINT register_index{};

		};
	}
}