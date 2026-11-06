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

				struct CVer {
					float pos[3] = {};
					float color[4] = {};
				};

				inline MeshResourceDesc NormalMesh{
					"NormalMesh",
					make_create_mesh_desc<NVer>({
						.vertex_ = {
							{	-0.5f,	-0.5f,	0.0f},
							{		0,	 0.5f,	0.0f},
							{	 0.5f,	-0.5f,	0.0f}
						},
						.index_ = {
							0,1,2
						}
					})

				};
				inline MeshResourceDesc NormalBox{
					"NormalBox",
					make_create_mesh_desc<NVer>({
						.vertex_ = {
							{	-0.5f,	-0.5f,	-0.5f},
							{	-0.5f,	 0.5f,	-0.5f},
							{	 0.5f,	 0.5f,	-0.5f},
							{	 0.5f,	-0.5f,	-0.5f},

							{	-0.5f,	-0.5f,	 0.5f},
							{	-0.5f,	 0.5f,	 0.5f},

							{	 0.5f,	-0.5f,	 0.5f},
							{	 0.5f,	 0.5f,	 0.5f}
						},
						.index_ = {
							0,1,2,0,2,3,	//正面
							4,5,1,4,1,0,	//左面
							6,7,5,6,5,4,	//後面
							3,2,7,3,7,6,	//右面
							1,5,7,1,7,2,	//上面
							3,6,4,3,4,0,	//下面
						}
					})

				};

				inline MeshResourceDesc ColorMesh{
					"ColorMesh",
					make_create_mesh_desc<CVer>({
						.vertex_ = {
							{{	 0.5f,		0,	1.0f},{	1,	0,	0,	1}},
							{{		0,	-0.5f,	1.0f},{	0,	1,	0,	1}},
							{{	-0.5f,		0,	1.0f},{	0,	0,	1,	1}}
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