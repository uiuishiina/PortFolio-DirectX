#pragma once

/* ========== Includeファイル ========== */

#include"../../ClassObject/GPUResource/ConstantBuffer.h"
#include"Math/Function/MathFMatrix.h"

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
		/// カメラデータ構造体
		/// </summary>
		struct CameraData {

			/// <summary>
			/// ビュー行列
			/// </summary>
			HandyItems::Math::Matrix view_{};

			/// <summary>
			/// プロジェクション行列
			/// </summary>
			HandyItems::Math::Matrix projection_{};

		};

		/// <summary>
		/// カメラオブジェクト
		/// </summary>
		class CameraObject : HandyItems::others::NonCopyableBase
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			CameraObject() {
				camera_buffer = std::make_unique<ClassObject::ConstantBuffer<CameraData>>();
			}

			/// <summary>
			/// デストラクタ
			/// </summary>
			~CameraObject() = default;

			/* ===== 初期化関数 ===== */

			/// <summary>
			/// カメラオブジェクト作成関数
			/// </summary>
			/// <param name="device_">Device参照</param>
			/// <param name="handles">ディスクリプターハンドル補助構造体</param>
			/// <param name="index">レジスターインデックス</param>
			/// <param name="view_">ビューポート設定</param>
			/// <param name="rect_">シザー短径設定</param>
			/// <returns>作成の成否</returns>
			[[nodiscard]] HRESULT create_camera_object(
				ID3D12Device* device_,
				Helper::DescriptorHeapHandles handles,
				UINT index,
				D3D12_VIEWPORT view_,
				D3D12_RECT rect_
			) {

				const auto hr = camera_buffer->create_constant_buffer(
					device_,
					handles,
					data_
				);
				if (FAILED(hr)) {
					return hr;
				}

				register_index = index;

				view_port = view_;
				scissor_rect = rect_;

				return hr;
			}

			/* ===== 実行関数 ===== */

			/// <summary>
			/// トランスフォームアップロード関数
			/// </summary>
			void update_buffer() {

				camera_buffer->upload_buffer(data_);
			}

			/// <summary>
			/// ビューポートアップロード関数
			/// </summary>
			/// <param name="view_">ビューポート設定</param>
			/// <param name="rect_">シザー短径設定</param>
			void update_view_port(
				D3D12_VIEWPORT view_,
				D3D12_RECT rect_
			) noexcept {

				view_port = view_;
				scissor_rect = rect_;
			}

			/// <summary>
			/// カメラバッファ設定関数
			/// </summary>
			/// <param name="register_index">Register番号</param>
			/// <param name="list_">コマンドリスト参照</param>
			void set_buffer(
				UINT register_index,
				ID3D12GraphicsCommandList* list_
			) {

				camera_buffer->set_constant_buffer(
					register_index,
					list_
				);
			}

			/// <summary>
			/// ビューポート設定関数
			/// </summary>
			/// <param name="list_">コマンドリスト参照</param>
			void set_view_port(
				ID3D12GraphicsCommandList* list_
			) const noexcept {

				list_->RSSetViewports(1, &view_port);
				list_->RSSetScissorRects(1, &scissor_rect);
			}

			/* ===== 取得関数 ===== */

			/// <summary>
			/// CameraData参照取得関数
			/// </summary>
			/// <returns>取得したCameraData参照</returns>
			[[nodiscard]] CameraData& get_camera_data() noexcept {

				return data_;
			}

			/// <summary>
			/// カメラバッファ参照取得関数
			/// </summary>
			/// <returns>取得したカメラバッファ参照</returns>
			[[nodiscard]] ClassObject::ConstantBuffer<CameraData>* get_camera_buffer() const noexcept {
				return camera_buffer.get();
			}

		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			/// カメラデータ
			/// </summary>
			CameraData data_{};

			/// <summary>
			/// カメラコンスタントバッファ
			/// </summary>
			std::unique_ptr<ClassObject::ConstantBuffer<CameraData>> camera_buffer{};

			/// <summary>
			/// コンスタントバッファレジスターインデックス
			/// </summary>
			UINT register_index{};

			/// <summary>
			/// ビューポート設定
			/// </summary>
			D3D12_VIEWPORT view_port{};

			/// <summary>
			/// シザー短径設定
			/// </summary>
			D3D12_RECT scissor_rect{};

		};
	}
}