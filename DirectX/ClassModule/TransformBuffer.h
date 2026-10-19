#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../ClassObject/GPUResource/ConstantBuffer.h"

//	HandyItems
#include"../../HandyItems/Math/BaseStruct/Transform.h"

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
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			TransformBuffer() = default;

			/// <summary>
			/// 引数付きコンストラクタ
			/// </summary>
			/// <param name="trans">初期設定するトランスフォーム</param>
			TransformBuffer(
				HandyItems::Math::Transform trans
			) :
				transform_{ trans } {}

			/// <summary>
			/// デストラクタ
			/// </summary>
			~TransformBuffer() = default;

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
					transform_
				);
			}

			/* ===== 実行関数 ===== */

			/// <summary>
			/// トランスフォームアップロード関数
			/// </summary>
			void update_buffer() {

				constant_buffer->upload_buffer(transform_);
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
			/// Transform参照取得関数
			/// </summary>
			/// <returns>取得したTransform参照</returns>
			[[nodiscard]] HandyItems::Math::Transform& get_transform() noexcept {

				return transform_;
			}

			/// <summary>
			/// コンスタントバッファ作成関数
			/// </summary>
			/// <returns></returns>
			[[nodiscard]] ClassObject::ConstantBuffer<
				HandyItems::Math::Transform
			>* get_buffer()const noexcept {

				return constant_buffer.get();
			}

		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			/// TransForm変数
			/// </summary>
			HandyItems::Math::Transform transform_{};

			/// <summary>
			/// ConstantBufferインスタンス
			/// </summary>
			std::unique_ptr<
				ClassObject::ConstantBuffer<HandyItems::Math::Transform>
			> constant_buffer{};

		};
	}
}