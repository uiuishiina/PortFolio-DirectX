#pragma once

/* ========== Includeファイル ========== */

#include"../DescriptorGroup/ConstantBufferGroup.h"
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

		namespace DescriptorGroup {

			/// <summary>
			/// カメラオブジェクト
			/// </summary>
			class CameraObject : protected ConstantBufferGroup<CameraData>
			{
				using Transform = HandyItems::Math::Transform;
				using Matrix = HandyItems::Math::Matrix;
			public:
				/* ========== Publicメンバー関数 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				CameraObject() = default;

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
					DescriptorHeapAllocator* allocator,
					D3D12_VIEWPORT view_,
					D3D12_RECT rect_
				) {
					
					const auto hr = create_constant_buffer_group(
						device_,
						allocator,
						CameraData{}
					);
					if (FAILED(hr)) {
						return hr;
					}

					update_view_port(view_, rect_);

					return hr;
				}

				/* ===== 実行関数 ===== */

				void update_camera_object() {
					update_index();

					auto view = view_.get_matrix().inverse();

					update_buffer(
						CameraData{
							view.has_value() ? view.value().transpose() : Matrix{},
							projection_.transpose()
						});
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

					projection_ = HandyItems::Math::MathF::perspective(
						HandyItems::Math::MathF::deg_to_rad(60),
						view_port.Width / view_port.Height,
						0.1f,
						1000
					);
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

					get_current_instance()->set_constant_buffer(
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

				[[nodiscard]] Transform& get_camera_transform() {
					return view_;
				}
				[[nodiscard]] Matrix& get_camera_projection() {
					return projection_;
				}
			private:  
				/* ========== Privateメンバー変数 ========== */

				Transform view_{};
				Matrix projection_{};

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
}