#pragma once

/* ========== Includeファイル ========== */

#include"Mesh.h"
#include"Math/BaseStruct/Transform.h"
#include"../DescriptorGroup/ConstantBufferGroup.h"

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

			/* ===== 初期化関数 ===== */

			[[nodiscard]] HRESULT create_mesh_object(
				ID3D12Device* device_,
				ID3D12GraphicsCommandList* list_,
				DescriptorHeapAllocator* allocator,
				const CurrentIndexBase* index,
				UINT register_,
				DrawObjectBase* mesh
			) {

				if (!mesh) {
					return E_FAIL;
				}
				mesh_ = mesh;

				const auto hr = transform_buffers.create_constant_buffer_group(
					device_,
					allocator,
					index,
					transform_.get_matrix()
				);
				if (FAILED(hr)) {
					return hr;
				}
				register_index = register_;

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

				transform_buffers.get_current_instance()->set_constant_buffer(
					register_index, 
					list_
				);

				mesh_->draw(list_);
			}

			void update_mesh_object() {

				transform_buffers.update_buffer(transform_.get_matrix());
			}

			/// <summary>
			/// トランスフォームバッファグループ参照取得関数
			/// </summary>
			/// <returns>取得したトランスフォームバッファグループ参照</returns>
			[[nodiscard]] DescriptorGroup::ConstantBufferGroup<HandyItems::Math::Matrix>& get_constant_buffer_group() {
				return transform_buffers;
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
			DrawObjectBase* mesh_{};

			/// <summary>
			/// トランスフォームバッファ
			/// </summary>
			DescriptorGroup::ConstantBufferGroup<HandyItems::Math::Matrix> transform_buffers{};

			/// <summary>
			/// コンスタントバッファレジスターインデックス
			/// </summary>
			UINT register_index{};

			UINT current_index{};

		};
	}
}