#pragma once

/* ========== Includeファイル ========== */

//	DirectX
#include"../ClassModule/DrawObject/Mesh.h"

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


				struct MeshCreateDescBase {
				protected:
					using Resource = Microsoft::WRL::ComPtr<ID3D12Resource>;
				public:

					MeshCreateDescBase() = default;
					virtual ~MeshCreateDescBase() = default;

					[[nodiscard]] virtual std::unique_ptr<ClassModule::DrawObjectBase> make_mesh_object(
						ID3D12Device* device_,
						ID3D12GraphicsCommandList* list_,
						std::span<std::reference_wrapper<Resource>> upload_resources
					) {

						return nullptr;
					};
				};

				template<typename T>
				struct MeshCreateDesc : public MeshCreateDescBase {

					MeshCreateDesc() = delete;
					MeshCreateDesc(ClassModule::desc::MeshDesc<T> desc) :
						desc_{ std::move(desc)} { }

					~MeshCreateDesc() = default;

					ClassModule::desc::MeshDesc<T> desc_{};

					[[nodiscard]] std::unique_ptr<ClassModule::DrawObjectBase> make_mesh_object(
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