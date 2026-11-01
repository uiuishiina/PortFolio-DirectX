#pragma once

/* ========== Includeファイル ========== */

#include"Mesh.h"
#include"../DescriptorGroup/TransformBufferGroup.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// オブジェクト機能統合名前空間
	/// </summary>
	namespace ClassModule {

		class MeshObject : HandyItems::others::NonCopyableBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			MeshObject() :
				transform_{},
				transform_buffers{ std::make_unique<DescriptorGroup::TransformBufferGroup>() } {}

			/// <summary>
			/// デストラクタ
			/// </summary>
			~MeshObject() = default;


			/* ===== 初期化関数 ===== */
			template<typename T>
			[[nodiscard]] HRESULT create_mesh_object(
				ID3D12Device* device_,
				ID3D12GraphicsCommandList* list_,
				DescriptorHeapAllocator* allocator,
				UINT index,
				Mesh* mesh
			) {

				if (!mesh) {
					return E_FAIL;
				}
				mesh_ = mesh;

				const auto hr = transform_buffers->create_constant_buffer_group(
					device_,
					allocator,
					transform_
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
			) const noexcept {

				transform_buffers->get_current_instance()->set_buffer(
					register_index, 
					list_
				);

				mesh_->draw(list_);
			}

			void update_mesh_object() {

				transform_buffers->update_index();
			}

			/// <summary>
			/// トランスフォームバッファグループ参照取得関数
			/// </summary>
			/// <returns>取得したトランスフォームバッファグループ参照</returns>
			[[nodiscard]] DescriptorGroup::TransformBufferGroup* get_transform_buffer_group() const noexcept {
				return transform_buffers.get();
			}

			[[nodiscard]] HandyItems::Math::Transform& get_transform() {
				return transform_;
			}

		private:
			/* ========== Privateメンバー変数 ========== */

			HandyItems::Math::Transform transform_{};

			/// <summary>
			/// メッシュ
			/// </summary>
			Mesh* mesh_{};

			/// <summary>
			/// トランスフォームバッファ
			/// </summary>
			std::unique_ptr<DescriptorGroup::TransformBufferGroup> transform_buffers{};

			/// <summary>
			/// コンスタントバッファレジスターインデックス
			/// </summary>
			UINT register_index{};

			UINT current_index{};

		};
	}
}