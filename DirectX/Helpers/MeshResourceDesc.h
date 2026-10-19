#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../ClassModule/DrawObject/Mesh.h"
#include"../ClassModule/DrawObject/MeshObject.h"

#include<string>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// リソース名前空間
	/// </summary>
	namespace Resource {

		/// <summary>
		/// 描画オブジェクト名前空間
		/// </summary>
		namespace DrawObject {

			/// <summary>
			/// メッシュ名前空間
			/// </summary>
			namespace Mesh {

				/// <summary>
				/// メッシュ作成補助基底構造体
				/// </summary>
				struct MeshCreateDescBase {
				protected:
					using Resource = Microsoft::WRL::ComPtr<ID3D12Resource>;
				public:
					/* ========== Publicメンバー関数 ========== */

					/// <summary>
					/// コンストラクタ
					/// </summary>
					MeshCreateDescBase() = default;

					/// <summary>
					/// デストラクタ
					/// </summary>
					virtual ~MeshCreateDescBase() = default;

					/* ===== 実行関数 ===== */

					/// <summary>
					/// メッシュ作成仮想関数
					/// </summary>
					/// <param name="device_">Device参照</param>
					/// <param name="list_">コマンドリスト参照</param>
					/// <param name="upload_resources">Upload用Resource参照配列</param>
					/// <returns>作成したメッシュ</returns>
					[[nodiscard]] virtual std::unique_ptr<ClassModule::DrawObjectBase> make_mesh(
						ID3D12Device* device_,
						ID3D12GraphicsCommandList* list_,
						std::span<std::reference_wrapper<Resource>> upload_resources
					) {

						return nullptr;
					};

					/// <summary>
					/// メッシュ作成仮想関数
					/// </summary>
					/// <param name="device_">Device参照</param>
					/// <param name="list_">コマンドリスト参照</param>
					/// <param name="upload_resources">Upload用Resource参照配列</param>
					/// <returns>作成したメッシュ</returns>
					[[nodiscard]] virtual std::unique_ptr<ClassModule::DrawObjectBase> make_mesh_object(
						ID3D12Device* device_,
						ID3D12GraphicsCommandList* list_,
						std::span<std::reference_wrapper<Resource>> upload_resources
					) {

						return nullptr;
					};
				};

				/// <summary>
				/// メッシュ作成補助型派生構造体
				/// </summary>
				/// <typeparam name="T">派生型</typeparam>
				template<typename T>
				struct MeshCreateDesc : public MeshCreateDescBase {

					/* ========== Publicメンバー変数 ========== */

					ClassModule::desc::MeshDesc<T> desc_{};

					/* ========== Publicメンバー関数 ========== */

					//	コンストラクタ削除
					MeshCreateDesc() = delete;

					/// <summary>
					/// 引数付きコンストラクタ
					/// </summary>
					/// <param name="desc">メッシュ設定構造体</param>
					MeshCreateDesc(
						ClassModule::desc::MeshDesc<T> desc
					) :
						desc_{ std::move(desc)} { }

					/// <summary>
					/// デストラクタ
					/// </summary>
					~MeshCreateDesc() = default;


					/* ===== 実行関数 ===== */

					/// <summary>
					/// メッシュ作成関数
					/// </summary>
					/// <param name="device_">Device参照</param>
					/// <param name="list_">コマンドリスト参照</param>
					/// <param name="upload_resources">Upload用Resource参照配列</param>
					/// <returns>作成したメッシュ</returns>
					[[nodiscard]] std::unique_ptr<ClassModule::DrawObjectBase> make_mesh(
						ID3D12Device* device_,
						ID3D12GraphicsCommandList* list_,
						std::span<std::reference_wrapper<Resource>> upload_resources
					) override {

						auto mesh = std::make_unique<ClassModule::Mesh>();

						const auto hr = mesh->create_mesh(
							device_,
							list_,
							upload_resources,
							desc_
						);

						if (FAILED(hr)) {
							return nullptr;
						}

						return mesh;
					}


					/// <summary>
					/// メッシュオブジェクト作成関数
					/// </summary>
					/// <param name="device_">Device参照</param>
					/// <param name="list_">コマンドリスト参照</param>
					/// <param name="upload_resources">Upload用Resource参照配列</param>
					/// <returns>作成したメッシュオブジェクト</returns>
					[[nodiscard]] virtual std::unique_ptr<ClassModule::DrawObjectBase> make_mesh_object(
						ID3D12Device* device_,
						ID3D12GraphicsCommandList* list_,
						Helper::DescriptorHeapHandles handles,
						UINT index,
						std::span<std::reference_wrapper<Resource>> upload_resources
					) {

						auto mesh = std::make_unique<ClassModule::MeshObject>();

						const auto hr = mesh->create_mesh_object(
							device_,
							list_,
							handles,
							index,
							upload_resources,
							desc_
						);

						if (FAILED(hr)) {
							return nullptr;
						}

						return mesh;
					};
				};

				/// <summary>
				/// メッシュ設定定義
				/// </summary>
				using MeshResourceDesc = std::tuple<
					std::string,
					std::unique_ptr<MeshCreateDescBase>
				>;
			}
		}
	}
}