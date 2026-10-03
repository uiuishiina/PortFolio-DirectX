#pragma once

/* ========== Includeファイル ========== */

#include"../Helpers/MeshResourceDesc.h"

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

			namespace Mesh {

				template<typename T>
				[[nodiscard]] std::unique_ptr<MeshCreateDescBase> make_create_mesh_desc(
					const ClassModule::desc::MeshDesc<T>& desc
				) {
					return std::make_unique<MeshCreateDesc<T>>(std::move(desc));
				}

				struct UV {
					float uv_[2] = {};
				};

				struct NVer {
					float pos[3] = {};
				};

				inline MeshResourceDesc Test{
					"TestMesh",
					make_create_mesh_desc<NVer>({
						.vertex_ = {
							{	-1,	-1, 0},
							{	 0,	 1, 0},
							{	 1,	-1, 0}
						},
						.index_ = {
							0,1,2
						}
					})

				};

			}

		}
	}



}