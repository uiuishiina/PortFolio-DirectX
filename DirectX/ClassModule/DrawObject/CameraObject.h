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
					UINT index,
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

					view_port = view_;
					scissor_rect = rect_;

					return hr;
				}

				/* ===== 実行関数 ===== */

				using ConstantBufferGroup<CameraData>::update_index;

				/// <summary>
				/// トランスフォームアップロード関数
				/// </summary>
				void update_buffer(CameraData data) {

					get_current_instance()->upload_buffer(data);
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

			private:
				/* ========== Privateメンバー変数 ========== */

				/// <summary>
				/// カメラデータ
				/// </summary>
				CameraData data_{};

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