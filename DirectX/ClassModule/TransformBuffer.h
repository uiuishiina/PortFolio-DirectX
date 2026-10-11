#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../ClassObject/GPUResource/ConstantBuffer.h"

//	HandyItems
#include"Math/BaseStruct/Transform.h"

#include<memory>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// オブジェクト機能統合名前空間
	/// </summary>
	namespace ClassModule {


		class TransformBuffer final : public HandyItems::others::NonCopyableBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */


			[[nodiscard]] HRESULT create_transform_buffer(
				ID3D12Device* device_,
				Helper::DescriptorHeapHandles handles
			) {

				return constant_buffer->create_constant_buffer(
					device_, 
					handles, 
					transform_
				);
			}

			void update_buffer() {

				constant_buffer->upload_buffer(transform_);
			}

			void set_buffer(
				ID3D12GraphicsCommandList* list_
			) {


			}

			/// <summary>
			/// Transform参照取得関数
			/// </summary>
			/// <returns>取得したTransform参照</returns>
			[[nodiscard]] HandyItems::Math::Transform& get_transform() noexcept {

				return transform_;
			}

			[[nodiscard]] ClassObject::ConstantBuffer<
				HandyItems::Math::Transform
			>* get_buffer()const noexcept {

				return constant_buffer.get();
			}

		private:
			/* ========== Privateメンバー変数 ========== */

			HandyItems::Math::Transform transform_{};

			std::unique_ptr<
				ClassObject::ConstantBuffer<HandyItems::Math::Transform>
			> constant_buffer{};

		};
	}
}