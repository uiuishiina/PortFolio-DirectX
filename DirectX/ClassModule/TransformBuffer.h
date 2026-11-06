 #pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Math/BaseStruct/Transform.h"

//	DirectX
#include"../ClassObject/GPUResource/ConstantBuffer.h"


#include<memory>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// オブジェクト機能統合名前空間
	/// </summary>
	namespace ClassModule {

		/// <summary>
		/// トランスフォームバッファクラス
		/// </summary>
		class TransformBuffer final : public HandyItems::others::NonCopyableBase
		{
			using Transform = HandyItems::Math::Transform;
			using Matrix = HandyItems::Math::Matrix;
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			TransformBuffer() :
				constant_buffer{ std::make_unique<ClassObject::ConstantBuffer<Matrix>>() } {}

			/* ===== 初期化関数 ===== */

			/// <summary>
			/// トランスフォームバッファ作成関数
			/// </summary>
			/// <param name="device_">Device参照</param>
			/// <param name="handles">ディスクリプターハンドル補助構造体</param>
			/// <returns>作成の成否</returns>
			[[nodiscard]] HRESULT create_transform_buffer(
				ID3D12Device* device_,
				Helper::DescriptorHeapHandles handles
			) {

				return constant_buffer->create_constant_buffer(
					device_, 
					handles, 
					Matrix{}
				);
			}

			/* ===== 実行関数 ===== */

			/// <summary>
			/// トランスフォームアップロード関数
			/// </summary>
			bool update_buffer(const Transform& transform) {

				return constant_buffer->upload_buffer(
					transform.get_matrix()
				);
			}

			/// <summary>
			/// コンスタントバッファ設定関数
			/// </summary>
			/// <param name="register_index">Register番号</param>
			/// <param name="list_">コマンドリスト参照</param>
			void set_buffer(
				UINT register_index,
				ID3D12GraphicsCommandList* list_
			) {

				constant_buffer->set_constant_buffer(
					register_index,
					list_
				);
			}

			/* ===== 取得関数 ===== */

			/// <summary>
			/// コンスタントバッファ取得関数
			/// </summary>
			/// <returns></returns>
			[[nodiscard]] ClassObject::ConstantBuffer<Matrix>* get_buffer() const noexcept {

				return constant_buffer.get();
			}

		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			/// ConstantBufferインスタンス
			/// </summary>
			std::unique_ptr<
				ClassObject::ConstantBuffer<Matrix>
			> constant_buffer{};

		};
	}
}