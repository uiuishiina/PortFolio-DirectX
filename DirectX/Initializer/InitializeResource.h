#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Debug/DebugLogSystem.h"

//	DirectX
#include"../DirectXContext.h"
#include"../Helpers/MeshResourceDesc.h"

//	その他
#include<vector>
#include<utility>
#include<string>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// 初期化名前空間
	/// </summary>
	namespace Initialize {

		/// <summary>
		/// 設定名前空間
		/// </summary>
		namespace desc {

			struct ResourceDesc {

				/* ========== Publicメンバー変数 ========== */

				std::vector<Resource::DrawObject::Mesh::MeshResourceDesc> mesh_desc{};


				/* ========== Publicメンバー関数 ========== */

				void emplace_mesh_desc(
					std::string name,
					std::unique_ptr<Resource::DrawObject::Mesh::MeshCreateDescBase> desc
				) {

					mesh_desc.emplace_back(
						std::make_tuple(
							std::move(name), 
							std::move(desc)
						));
				}
				void emplace_mesh_desc(
					const Resource::DrawObject::Mesh::MeshResourceDesc& desc
				) {

					mesh_desc.emplace_back(desc);
				}

			};
		}

		class InitializeResource
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/* ===== 初期化関数 ===== */

			[[nodiscard]] static HRESULT initialize_resource(
				DirectXContext* context
			) {



			}


		private:
			/* ========== Privateメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			InitializeResource() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~InitializeResource() = default;

		};
	}
}